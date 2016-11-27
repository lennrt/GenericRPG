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

using namespace std;

Mailbox::Mailbox (){
	bool Success = true;
	
	//Attempt to create a new memory segment.
	controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR | IPC_CREAT);
	
	if (controlID == -1) {
		//Fatal error.  Unknown error with shmget.
		Success = false;
	}
		
	//Attach to the memory segment.
	controlPointer = (char*)shmat(controlID, NULL, 0);
	
	//Create the Inbox semaphore
	semID = sem_open (semName.c_str(), O_CREAT | O_EXCL, 0644, 1);
	
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

void Mailbox::CheckMessages(){
	LockInbox();
	for (int i = 1; i < inboxCount;i++){
		if (CheckSlot(0,i)){
			Inbox.push_back(GetMessage(0,i));
			ClearSlot(0,i);
		} else {
			break;
		}
	}	
	UnlockInbox();	
}

void Mailbox::LockInbox(){
// 	//Attempt to lock Inbox.  Success = Inbox was not locked.
// 	char* LockLocation = controlPointer + InboxLock;
// 	bool Success = false;
// 	
// 	sem_wait(semID);
// 	if (*LockLocation == 0x0){
// 		*LockLocation = 0x1;
// 		Success = true;
// 	}
// 	sem_post(semID);
// 	return (Success);
	sem_wait(semID);
}

void Mailbox::UnlockInbox(){
// 	char* LockLocation = controlPointer + InboxLock;
// 	*LockLocation = 0x0;
	sem_post(semID);
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
	*(MemLoc + MessageSetFlag) = 0x1;
	int MemSize = Message.size();
	if (MemSize > slotSize - FlagSetSize) { MemSize = slotSize - FlagSetSize;}
	memcpy ( MemLoc + FlagSetSize, Message.c_str(), MemSize); 
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
	
