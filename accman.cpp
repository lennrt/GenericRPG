#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

//Variables and constants for handling shared memory and semaphore.

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

//Structure for HTTP form data
struct FormInfo{
	string Key;
	string Value;
};

//Vector to hold Key / Value pairs after processing
vector<FormInfo> FormData;
string SerialFormData;

bool fileExists(const std::string& file);
bool VerifySession();
string ConnectToGameService();
void DisconnectFromGameService();
string EnterGame();
void LockInbox();
void UnlockInbox();
void SendMessageToBox(std::string Message, int Box);
bool CheckSlot(int Box, int Slot);
string GetMessage(int Box, int Slot);
void SetMessage(int Box, int Slot, string Message);
string GetValueFromKey(string FindKey);
void getFormData();

int main(){
	string Op;
	string Response;
	fstream PWFile;
	fstream UserFile;
	fstream CharFile;
	
	//Set HTTP Header
	cout << "Content-type: text/plain\n\r\n\r";
	
	//Process incoming POST data
	getFormData();
	
	//Check action based on POST:
	
	// This login is insecure because the password is not encrypted in transit from the browser and because the crypt function
	// is used which isn't secure.  But it's a decent student project concept of including security elements in a product.
	Op = GetValueFromKey("Op");		
	string u = GetValueFromKey("u");
	string p = GetValueFromKey("p");
	
	//User Login
	if (Op == "Login"){
		if (fileExists ("u/" + u)){
			string PassTestIn(crypt(p.c_str(),"AB"));  //This is EXTREMELY insecure.  Use for student project only.
			string PassTestFile;
			string Temp;
			int i, j;
			
			PWFile.open ("u/" + u + "/p", fstream::in);
			PWFile >> PassTestFile;
			PWFile.close();
			
			if (PassTestFile == PassTestIn){
				Response += "&Status=Success";
				
				i=0;
				j=1;
				
				UserFile.open ("u/" + u + "/u", fstream::in);
				while ( UserFile >> Temp ){
					if (i == 0) {Response += "&c" + to_string(j) + "=" + Temp;}
					if (i == 1) {Response += "&Name" + to_string(j) + "=" + Temp;}
					if (i == 2) {Response += "&Level" + to_string(j) + "=" + Temp;}
					if (i == 3) {Response += "&Race" + to_string(j) + "=" + Temp;}
					if (i == 4) {Response += "&Class" + to_string(j) + "=" + Temp;}
					i++;
					if (i > 4) {
						i = 0;
						j++;
					}
				}
				UserFile.close();
				cout << Response;
				exit(0);
			} else {
				Response += "&Status=Fail&Reason=Incorrect Password.";
				cout << Response;
				exit(0);	
			}
		} else {
			Response += "&Status=Fail&Reason=User does not exist.";
			cout << Response;
			exit(0);	
		}
	}

	//User Setup
	if (Op == "New"){
		//Check if a directory exists for the supplied username.  If so, the user exists.  Fail and exit.
		if (fileExists ("u/" + u)){
			Response += "&Status=Fail&Reason=User already exists.";
			cout << Response;
			exit(0);
		}
		string Dir = "u/" + u;
		mkdir(Dir.c_str(), 755);
		
		PWFile.open ("u/" + u + "/p", fstream::out);
		PWFile << crypt(p.c_str(),"AB");  //This is EXTREMELY insecure.  Use for student project only.
		PWFile.close();
		
		UserFile.open ("u/" + u + "/u", fstream::out);
		UserFile.close();
		
		Response += "&Status=Success";
		cout << Response;
		exit(0);
	}

	//Character Setup
	if (Op == "NewCharacter"){
		vector <string> Rebuild;


		string charID = GetValueFromKey("c");
		
		if (fileExists ("u/" + u)){
			string PassTestIn(crypt(p.c_str(),"AB"));  //This is EXTREMELY insecure.  Use for student project only.
			string PassTestFile;
			string Temp;
			
			//Verify password for action
			PWFile.open ("u/" + u + "/p", fstream::in);
			PWFile >> PassTestFile;
			PWFile.close();
			


			if (PassTestFile == PassTestIn){
				Response += "&Status=Success";
				
				//Read in list of current characters
				fstream UserFile;
				UserFile.open ("u/" + u + "/u", fstream::in);
				while ( UserFile >> Temp ){
					Rebuild.push_back(Temp);
				}


				UserFile.close();
				
				//Write out list of characters.
				UserFile.open ("u/" + u + "/u", fstream::out | fstream::trunc);
				for (int i = 0; i < Rebuild.size(); i++){
					UserFile << Rebuild[i] << endl;
				}
				UserFile << GetValueFromKey("c") << endl;
				UserFile << GetValueFromKey("Name") << endl;
				UserFile << GetValueFromKey("Level") << endl;
				UserFile << GetValueFromKey("Race") << endl;
				UserFile << GetValueFromKey("Class") << endl;				
				UserFile.close();
				
				//Create the character information file for the character.
				CharFile.open ("u/" + u + "/" + charID, fstream::out);
				CharFile << "Name=" + GetValueFromKey("Name") << endl;
				CharFile << "Race=" + GetValueFromKey("Race") << endl;
				CharFile << "Class=" + GetValueFromKey("Class") << endl;
				CharFile << "Sex=" + GetValueFromKey("Sex") << endl;
				CharFile << "Exp=0" << endl;		
				CharFile << "Gold=250" << endl;
				CharFile << "Int=" + GetValueFromKey("Int") << endl;
				CharFile << "Str=" + GetValueFromKey("Str") << endl;
				CharFile << "Agi=" + GetValueFromKey("Agi") << endl;
				CharFile << "Con=" + GetValueFromKey("Con") << endl;
				CharFile << "Spd=" + GetValueFromKey("Spd") << endl;
				CharFile << "Cha=" + GetValueFromKey("Cha") << endl;
				CharFile << "End=" + GetValueFromKey("End") << endl;
				CharFile.close();
				
				cout << Response;
				exit(0);
			} else {
				Response += "&Status=Fail&Reason=Incorrect Password.";
				cout << Response;
				exit(0);	
			}
		} else {
			Response += "&Status=Fail&Reason=User does not exist.";
			cout << Response;
			exit(0);	
		}	
	}
	
	//Character Delete
	if (Op == "DeleteCharacter"){
		vector <string> Rebuild;
		string u = GetValueFromKey("u");
		string p = GetValueFromKey("p");
		string charID = GetValueFromKey("c");
			fstream PWFile;
		
		if (fileExists ("u/" + u)){
			string PassTestIn(crypt(p.c_str(),"AB"));  //This is extremely insecure.  Use for student project only.
			string PassTestFile;
			string Temp;
			
			//Verify password for action
			PWFile.open ("u/" + u + "/p", fstream::in);
			PWFile >> PassTestFile;
			PWFile.close();
			
			if (PassTestFile == PassTestIn){
				Response += "&Status=Success";
				
				//Read in list of current characters
				UserFile.open ("u/" + u + "/u", fstream::in);
				while ( UserFile >> Temp ){
					Rebuild.push_back(Temp);
				}
				UserFile.close();
				
				//Write out list of characters removing the deleted character.
				UserFile.open ("u/" + u + "/u", fstream::out | fstream::trunc);
				for (int i = 0; i < Rebuild.size(); i++){
					if (Rebuild[i] == charID){
						i += 4;
					} else {
						UserFile << Rebuild[i] << endl;
					}
				}
				UserFile.close();
				
				//Delete the character information file for the character.
				string Obj = "u/" + u + "/" + charID;
				remove(Obj.c_str());
				cout << Response;
				exit(0);
			} else {
				Response += "&Status=Fail&Reason=Incorrect Password.";
				cout << Response;
				exit(0);	
			}
		} else {
			Response += "&Status=Fail&Reason=User does not exist.";
			cout << Response;
			exit(0);	
		}	
	}   

	//Character Login
	if (Op == "EnterGame"){			
		if (fileExists ("u/" + u)){
			string PassTestIn(crypt(p.c_str(),"AB"));  //This is EXTREMELY insecure.  Use for student project only.
			string PassTestFile;
			
			//Verify password for action
			PWFile.open ("u/" + u + "/p", fstream::in);
			PWFile >> PassTestFile;
			PWFile.close();
			
			if (PassTestFile == PassTestIn){
				string TryConnect = ConnectToGameService();
				if (TryConnect == ""){	
					Response += EnterGame();
				} else {
					Response += TryConnect;
				}
				cout << Response;
				DisconnectFromGameService();
				exit(0);
			} else {
				Response += "&Status=Fail&Reason=Incorrect Password.";
				cout << Response;
				exit(0);	
			}
		} else {
			Response += "&Status=Fail&Reason=User does not exist.";
			cout << Response;
			exit(0);	
		}	
	}
	
	//Make an in-game action (send message to service)
	if (Op == "Play"){	
		//Connect to game service
		ConnectToGameService();
		
		//VerifySession
		if (VerifySession()){
			//Send Message
			SendMessageToBox(SerialFormData,0);			
		} else {
			Response += "&Status=Fail&Reason=Session credentials do not match.";
			cout << Response;
		}
		
		//Close Session
		DisconnectFromGameService();
		exit(0);	
	}
	
	//Update information from game service
	if (Op == "Update"){			
		fstream LogFile;
		LogFile.open ("Log", fstream::out);
		int Box = stoi(GetValueFromKey("b"));
		string RetVal;
		
		//Connect to game service
			LogFile << "ConnectToGameService\n" << flush;
		ConnectToGameService();
		
		//VerifySession
		if (VerifySession()){
			//Get Messages
			for (int i = 1; i < slotCount; i++){
				
					LogFile << "Checkslot\n" << flush;
				if (CheckSlot(Box, i)){
					//Host interprets ^ as message dilineator.
					RetVal += "^" + GetMessage(Box, i);
				}
			}			
		} else {
			Response += "&Status=Fail&Reason=Session credentials do not match.";
			cout << Response;
		}
		
		//Close Session
				
				LogFile << "DisconnectFromGameService\n" << flush;
		DisconnectFromGameService();
		exit(0);	
	}    
}

bool fileExists(const std::string& file) {
	struct stat buf;
	return (stat(file.c_str(), &buf) == 0);
}

bool VerifySession(){
}

string ConnectToGameService(){
	string RetVal = "";	
	int NewBox = 0;
	char* MemLoc;
	char Temp;
	string BoxClaimMessage;
    	
	//Attempt to create a new connection to the shared memory segment.
	controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR);
	
	if (controlID == -1) {
		//Fatal error.  Unknown error with shmget.
		RetVal += "&Status=Fail&Reason=Unknown error with shmget on existing section of memory set aside for control.";
		return RetVal;
	}
		
	//Attach to the memory segment.
	controlPointer = (char*)shmat(controlID, NULL, 0);
	
	//Access semaphore	
	semID = sem_open ("/Inbox", 0);
	
	if (semID == SEM_FAILED) {
		//Fatal error.  Unknown error with sem_open.
		RetVal += "&Status=Fail&Reason=Unknown error with sem_open.";
		return RetVal;
	}
}

void DisconnectFromGameService(){
	shmdt(controlPointer);
}

string EnterGame(){
	string RetVal;	
	int NewBox = 0;
	char* MemLoc;
	char Temp;
	string BoxClaimMessage;
    	
	//Search for an empty communication box.
	
	for (int i = 1; i < boxCount; i++){
		MemLoc = controlPointer + inboxSize + (i * boxSize);
		Temp = MemLoc[BoxClaimedFlag];
		MemLoc[BoxClaimedFlag] = 0x1;
		if (Temp == 0x0){
			NewBox = i;
			break;
		}		
	}
	
	//No box found.  This means all boxes are in use.  Fail because too many players.
	
	if (NewBox == 0){
		RetVal += "&Status=Fail&Reason=Session full. Too many players.";
		return RetVal;		
	}
	
	//Box found.  Inform the game server that a box is reserved, and initiate a game session.
	
	BoxClaimMessage = "&u=" + GetValueFromKey("u") + "&c=" + GetValueFromKey("c") + "&s=" + GetValueFromKey("s") + "&Box=" + to_string(NewBox) + "&Action=EnterGame";
	
	LockInbox();
	SendMessageToBox(BoxClaimMessage, 0);
	UnlockInbox();

	RetVal += "&Status=Success&Box=" + to_string(NewBox);

	return RetVal;
}

void LockInbox(){
	sem_wait(semID);
}

void UnlockInbox(){
	sem_post(semID);
}

void SendMessageToBox(std::string Message, int Box){
	//Note: a full box results in a dropped message.
	for (int i = 1; i < slotCount; i++){
		if (CheckSlot(Box, i)){               
			SetMessage(Box, i, Message);
			break;
		}
	}
}

bool CheckSlot(int Box, int Slot){	
	// For future reference - this is not server-side thread-safe, modify if expanding use to other programs.
	//To be thread safe, atomically reserve while checking (as we do with locking the Inbox.)
	char* MemLoc;
	bool RetVal;
	
	if (Box == 0 ){
		MemLoc = controlPointer + (Slot * slotSize);
		RetVal = MemLoc[MessageSetFlag] == 0x0;
	} else {
		MemLoc = controlPointer + inboxSize + (Box * boxSize) + (Slot * slotSize);
		RetVal = (MemLoc[MessageSetFlag] == 0x1 && MemLoc[MessageReceivedFlag] == 0x0);
	}
	return (RetVal);
}

string GetMessage(int Box, int Slot){
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

void SetMessage(int Box, int Slot, string Message){ 
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

string GetValueFromKey(string FindKey){
	for (int i = 0; i < FormData.size(); i++){
		if (!FormData[i].Key.compare(FindKey)){ return FormData[i].Value; }
	}	
	return "";
}

void getFormData(){
	int EnvLen;	
	int Start = 1;
	int Mid = 0;
	FormInfo NewData;
	string Env;
	
	
	if (getenv("CONTENT_LENGTH") != NULL){
		EnvLen = atoi(getenv("CONTENT_LENGTH"));
	 	cin >> Env;
	} else {
		string TEMPstr = "?u=test&p=test&Op=New";
		EnvLen = TEMPstr.size();
		Env = TEMPstr;
	}
	
	SerialFormData = Env.substr(0,EnvLen);
	
	//cin can technically recieve more than CONTENT_LENGTH.
	//We'll use EnvLen to restrict what we read.

	if (EnvLen == 0){
		//Improper header
		cout << "Data not received";
		exit(-1);
	}

	//Split Key-Value pairs and place in the FormData structure.
	for (int i = 1; i < EnvLen; i++){
	if (Env[i] == '='){Mid = i + 1;}
		if (Env[i] == '&' || i == EnvLen - 1){
			if (i == EnvLen - 1) i++;  //Get last character
			NewData.Key = Env.substr(Start,Mid-Start-1);
			NewData.Value = Env.substr(Mid, i - Mid);
			FormData.push_back(NewData);
			Start = i + 1;
		}
	}
}

