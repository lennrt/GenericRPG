#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "mailbox.h"

Mailbox::Mailbox (){
	//Attempt to create a new memory segment.
	controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR | IPC_CREAT);
	
	if (controlID == -1) {
		//Fatal error.  Unknown error with shmget.
		exit(-1);
	}
		
	//Attach to the memory segment.
	controlPointer = (char*)shmat(controlID, NULL, 0);
}

Mailbox::~Mailbox (){
	shmdt(controlPointer);
	shmdctl(controlID, IPC_RMID);
}

void Mailbox::CheckForNewUsers(){
	//Search for an empty comm slot.
	//Note, I use a simple locking mechanism here that will greatly reduce R/W collisions, but is not actually
	//completely thread-safe.  That's because between checking a zero bit and setting the bit to one, this process
	//can be made to sleep or another process on another CPU can intervene.  It's much better than nothing and is
	//simple enough for now.
	
	int NumberofBoxes = controlSize / boxSize;
	
	for (int i = 1; i < NumberofBoxes; i++){ 
		
		tSlot = i * 32768;

		//The first byte in a segment indicates ownership.  Byte = One if claimed and Zero if unclaimed.
		if (controlPointer[tSlot] == 0x0){
			//Claim the slot.
			controlPointer[tSlot] = 0x1;
			
			//Register the slot location.  Wait until the byte-lock is off.
			while (!Done){
				if (controlPointer[0] == 0x0){
					controlPointer[0] = 0x1;
					Slot = i;
					Done = true;
					unsigned char Pos = (unsigned char)controlPointer[1];
					controlPointer[Pos + 2] = (unsigned char)Slot;
					Pos++;
					controlPointer[1] = Pos;
					controlPointer[0] = 0x0;
					i = 256;					
				} else {
					// Sleep for 3 microseconds and then check again.
					nanosleep (&req, &rem);
				}
			}
		}
		
	}
}

void Mailbox::CloseUserBox(){
}
void Mailbox::CheckMessages(){
}
string Mailbox::GetNextMessage(){
}



	
	//Wait for a response from the game service.
	//Response will incluse a session ID, confirmed slot number for message exchange, starting position, 
	//full character stats, map, nearby enemies...
	
	//Mailbox format:  Byte 0 = Taken/Free flag; Byte 1 = Message for server flag; Byte 2 = Message for client flag.  
	//Byte 3 + 4 = size of message.  Byte 5+ = message.
	//No thread issues since only one server-client per segment and always only read or write not both.
	
	RetVal += "&Slot=" + to_string(Slot);
	
	while (controlPointer[Slot * 32768 + 2] == 0x0){
		// Sleep for 3 microseconds and then check again.
		nanosleep (&req, &rem);	
	}
	
	size_t messageLen = (int)((unsigned char)controlPointer[3]) * 256 + (int)((unsigned char)controlPointer[4]);
	
	string Temp(reinterpret_cast<const char *>(controlPointer[5]), messageLen);
	RetVal += Temp;
	return RetVal;
