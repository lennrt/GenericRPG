#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>

using namespace std;

char * controlPointer;
int slotSize = 1024;
int boxSize = 8192;string GetMessage(int Box, int Slot);
void SetMessage(int Box, int Slot, string Message);
void ClearSlot (int Box, int Slot);

int main () {
	cout << "Content-type: text/plain\n\r\n\r";
	cout << "Test Successful!\n\r\n\r";
	
	controlPointer = (char *)malloc (8000000);
	string TestString;
	
	ClearSlot(3,3);
	ClearSlot(4,1);
	ClearSlot(5,2);
	
	TestString = "This is totally a test and shit";
	SetMessage(3,3, TestString);
	
	TestString = "Ok, now this is new.";
	SetMessage(4,1, TestString);
	
	TestString = "One last thing...";
	SetMessage(5,2, TestString);

	cout << "Now testing...\n";
	cout << "3,3:" << GetMessage(3,3) << "!!!" << endl;
	cout << "4,1:" <<  GetMessage(4,1) << "!!!"  << endl;	
	cout << "5,2:" <<  GetMessage(5,2) << "!!!"  << endl << flush;	

}


string GetMessage(int Box, int Slot){
	string RetVal;
	char Buffer[slotSize];
	char* MemLoc = controlPointer + (Box * boxSize) + (Slot * slotSize);
	memcpy ( &Buffer, MemLoc, slotSize); 
	return (string(Buffer));
}
void SetMessage(int Box, int Slot, string Message){
	char Buffer[slotSize];
	char* MemLoc = controlPointer + (Box * boxSize) + (Slot * slotSize);
	memcpy ( MemLoc, Message.c_str(), Message.size()); 
}
void ClearSlot (int Box, int Slot){	
	void* MemLoc = controlPointer + (Box * boxSize) + (Slot * slotSize);
	memset (MemLoc,'\0',slotSize);
}
