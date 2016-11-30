#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include "mailbox.h"
#include <iostream>

using namespace std;

Mailbox::Mailbox (){
	bool Success = true;
	
	//Attempt to create a new memory segment.
	controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR | IPC_CREAT | 0644);
	
	if (controlID == -1) {
		//Fatal error.  Unknown error with shmget.
		Success = false;
	}
		
	//Attach to the memory segment.
	controlPointer = (char*)shmat(controlID, NULL, 0);
	
	//Create the Inbox semaphore
	semID = sem_open ("/Inbox", O_CREAT, 0644, 1);
	
	if (semID == SEM_FAILED) {
		Success = false;
	}
	SetupOK = Success;
}

Mailbox::~Mailbox (){
	shmdt(controlPointer);
	shmctl(controlID, IPC_RMID, NULL);
	sem_destroy (semID);
}

void Mailbox::OpenUserBox(int Box){
	OpenBoxes.push_back(Box);
}

void Mailbox::CloseUserBox(int Box){
	for (int i = 0; i < OpenBoxes.size(); i++){
		if (OpenBoxes[i] == Box){
			OpenBoxes.erase(OpenBoxes.begin() + i);
			for (int j = 0; j < slotCount; j++){
				ClearSlot(Box, j);
			}
		}		
	}
}

bool Mailbox::SetupSuccessful(){
	return (SetupOK);
}

int Mailbox::BoxCount(){
	return (OpenBoxes.size());
}

int Mailbox::MessageCount(){
	return (Inbox.size());
}

void Mailbox::CheckMessages(){
	cout << "Locking\n";
	cout << "semID:" << semID << "\n";
	sem_wait(semID);		//Lock Inbox
	cout << "Locked\n";
	for (int i = 1; i < inboxCount;i++){
		if (!CheckSlot(0,i)){
			Inbox.push_back(GetMessage(0,i));
			ClearSlot(0,i);
		} else {
			break;
		}
	}	
	cout << "Unlocking\n";
	sem_post(semID);		//Unlock Inbox
	cout << "Unlocked\n";
}

string Mailbox::GetNextMessage(){
	string RetVal = "";
	
	CheckMessages();
	
	if (Inbox.size() > 0){
		RetVal = Inbox[0];
		Inbox.erase(Inbox.begin());
	} 
	return RetVal;
}
void Mailbox::BroadcastMessage(string Message){
	for (int i = 0; i < OpenBoxes.size(); i++){
		SendMessageToBox(Message, i);
	}
}

void Mailbox::SendMessageToBox(std::string Message, int Box){
	//Note: a full box results in a dropped message.
	for (int i = 1; i < slotCount; i++){
		if (CheckSlot(Box, i)){    
			ClearSlot(Box, i);
			SetMessage(Box, i, Message);
			break;
		}
	}
}

bool Mailbox::CheckSlot(int Box, int Slot){	
	// For future reference - this is not server-side thread-safe, modify if expanding use to other programs.
	//To be thread safe, atomically reserve while checking (as we do with locking the Inbox.)
	char* MemLoc;
	if (Box == 0 ){
		MemLoc = controlPointer + (Slot * slotSize);
	} else {
		MemLoc = controlPointer + inboxSize + (Box * boxSize) + (Slot * slotSize);
	}
	return (MemLoc[MessageSetFlag] == 0x0 || MemLoc[MessageReceivedFlag] == 0x1);
}

string Mailbox::GetMessage(int Box, int Slot){
	char Buffer[slotSize];
	char* MemLoc;
	if (Box == 0 ){
		MemLoc = controlPointer + (Slot * slotSize);
	} else {
		MemLoc = controlPointer + inboxSize + (Box * boxSize) + (Slot * slotSize);
	}
	memcpy (&Buffer, MemLoc + FlagSetSize, slotSize - FlagSetSize); 
	return (string(Buffer)); 
}

void Mailbox::SetMessage(int Box, int Slot, string Message){ 
	char Buffer[slotSize];
	char* MemLoc;
	if (Box == 0 ){
		MemLoc = controlPointer + (Slot * slotSize);
	} else {
		MemLoc = controlPointer + inboxSize + (Box * boxSize) + (Slot * slotSize);
	}
	int MemSize = Message.size();
	if (MemSize > slotSize - FlagSetSize - 1) { MemSize = slotSize - FlagSetSize - 1;}
	memcpy ( MemLoc + FlagSetSize, Message.c_str(), MemSize); 
	*(MemLoc + MessageSetFlag) = 0x1;
}

void Mailbox::ClearSlot (int Box, int Slot){	
	void* MemLoc;
	if (Box == 0 ){
		MemLoc = controlPointer + (Slot * slotSize);
	} else {
		MemLoc = controlPointer + inboxSize + (Box * boxSize) + (Slot * slotSize);
	}
	memset (MemLoc,'\0',slotSize);
}

int Mailbox::FindSlot(int Box){
	for (int i = 1; i < boxSize; i++){
		char* MemLoc = controlPointer + inboxSize + (Box * boxSize) + (i * slotSize);
		if (*(MemLoc + MessageSetFlag) == 0x0){
			*(MemLoc + MessageSetFlag) = 0x1;	
			return i;
		}
	}
	return 0;
}
	
