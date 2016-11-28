#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <atomic>
#include <semaphore.h>
#include <fcntl.h>

#ifndef MAILBOX_H
#define MAILBOX_H

class Mailbox{
    public:
        Mailbox();
        ~Mailbox();
	
	void OpenUserBox(int Box);
	void CloseUserBox(int Box);
	std::string GetNextMessage();
	void SendMessageToBox(std::string Message, int Box);
	void BroadcastMessage(std::string Message);
	bool SetupSuccessful();

    private:
	std::vector <std::string> Inbox;
	std::vector <int> OpenBoxes;
	
	void CheckMessages();
	void LockInbox();
	void UnlockInbox();
	std::string GetMessage(int Box, int Slot);
	void SetMessage(int Box, int Slot, std::string Message);
	void ClearSlot (int Box,int Slot);	
	bool CheckSlot(int Box, int Slot);
	int FindSlot(int Box);
	
	//Indicates OS operations have been successfully performed (SHM and SEM)
	bool SetupOK = false;
	
	//shared Memory and semaphore ID and pointer for control segment.
	int controlID;
	char* controlPointer;
	sem_t* semID;

	//Randomly generated key value for shared memory: 920004285
	key_t controlKey = 920004285;
	
	//The shared memory contains 256 segments of 32768 bytes (32KB) in length.
	size_t controlSize = 8388608;
	
	//Size of message boxes
	int boxSize = 32768;
	int boxCount = 192;
	
	//Size of messages
	int slotSize = 1024;
	int slotCount = 32;
	
	//Size of Inbox
	int inboxSize = 2097152;
	int inboxCount = 2048;
	
	//Location of thread lock and inbox controls
	int InboxLock = 0;
	int BoxClaimedFlag = 0;
	int MessageSetFlag = 0;
	int MessageReceivedFlag = 1;
	int FlagSetSize = 2;
	int SessionIDLocation = 3;
	int SessionIDSize = 8;
	
};

#endif
