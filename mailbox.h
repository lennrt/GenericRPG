#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct Box {
	string User;
	int BoxNumber;
};

struct Message {
	string User;
	string Message;
};
	

class Mailbox{
    public:
	vector <Box> Boxes;
	vector <Message> Messages;
	    
        Mailbox();
        ~Mailbox();
	
	void CheckForNewUsers();
	void CloseUserBox();
	void CheckMessages();
	string GetNextMessage();
	void SendMessageToUser(string Message, string User);

    private:
	//shared Memory ID and pointer for control segment.
	int controlID;
	char* controlPointer;

	//Randomly generated key value for shared memory: 920004285
	key_t controlKey = 920004285;
	
	//The shared memory contains 1024 segments of 8192 bytes (8KB) in length.
	size_t controlSize = 8388608;
	
	//Size of message boxes
	int boxSize = 32768;
};
