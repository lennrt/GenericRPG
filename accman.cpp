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

using namespace std;

//Structure for HTTP form data
struct FormInfo{
	string Key;
	string Value;
};

//Vector to hold Key / Value pairs after processing
vector<FormInfo> FormData;

void setupMemory();
size_t getControlSize();
void getFormData();
string GetValueFromKey(string FindKey);
bool fileExists(const std::string& file);
string StringToHex(string Data);
string HexToString(string Data);
int HexToInt(char Convert);
string EnterGame();

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
					if (i == 0) {Response += "&ID" + to_string(j) + "=" + Temp;}
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

	//Character Login
	if (Op == "Play"){
// 		vector <string> Rebuild;
// 		string ID = GetValueFromKey("ID");
// 		
// 		if (fileExists ("u/" + u)){
// 			string PassTestIn(crypt(p.c_str(),"AB"));  //This is EXTREMELY insecure.  Use for student project only.
// 			string PassTestFile;
// 			
// 			//Verify password for action
// 			PWFile.open ("u/" + u + "/p", fstream::in);
// 			PWFile >> PassTestFile;
// 			PWFile.close();
// 			
// 			if (PassTestFile == PassTestIn){
// 				Response += EnterGame();
// 				cout << Response;
// 				exit(0);
// 			} else {
// 				Response += "&Status=Fail&Reason=Incorrect Password.";
// 				cout << Response;
// 				exit(0);	
// 			}
// 		} else {
// 			Response += "&Status=Fail&Reason=User does not exist.";
// 			cout << Response;
// 			exit(0);	
// 		}	
	}

	//Character Setup
	if (Op == "NewCharacter"){
		vector <string> Rebuild;


		string ID = GetValueFromKey("ID");
		
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
				
				//Write out list of characters removing the deleted character.
				UserFile.open ("u/" + u + "/u", fstream::out | fstream::trunc);
				for (int i = 0; i < Rebuild.size(); i++){
					UserFile << Rebuild[i] << endl;
				}
				UserFile << GetValueFromKey("ID") << endl;
				UserFile << GetValueFromKey("Name") << endl;
				UserFile << GetValueFromKey("Level") << endl;
				UserFile << GetValueFromKey("Race") << endl;
				UserFile << GetValueFromKey("Class") << endl;				
				UserFile.close();
				
				//Create the character information file for the character.
				CharFile.open ("u/" + u + "/" + ID, fstream::out);
				CharFile << "Name=" + GetValueFromKey("Name") << endl;
				CharFile << "Race=" + GetValueFromKey("Race") << endl;
				CharFile << "Class=" + GetValueFromKey("Class") << endl;
				CharFile << "Sex=" + GetValueFromKey("Sex") << endl;
				CharFile << "Level=" + GetValueFromKey("Level") << endl;				
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
		string ID = GetValueFromKey("ID");
			fstream PWFile;
		
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
				UserFile.open ("u/" + u + "/u", fstream::in);
				while ( UserFile >> Temp ){
					Rebuild.push_back(Temp);
				}
				UserFile.close();
				
				//Write out list of characters removing the deleted character.
				UserFile.open ("u/" + u + "/u", fstream::out | fstream::trunc);
				for (int i = 0; i < Rebuild.size(); i++){
					if (Rebuild[i] == ID){
						i += 4;
					} else {
						UserFile << Rebuild[i] << endl;
					}
				}
				UserFile.close();
				
				//Delete the character information file for the character.
				string Obj = "u/" + u + "/" + ID;
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
    
}

bool fileExists(const std::string& file) {
	struct stat buf;
	return (stat(file.c_str(), &buf) == 0);
}

string EnterGame(){
	string RetVal;	
	int tSlot = 0;
	int Slot = 0;
	struct timespec req, rem;
	req.tv_sec = 0;
	req.tv_nsec = 3000000L;
	bool Done = false;
		
	//shared Memory ID and pointer for control segment.
	int controlID;
	char* controlPointer;

	//Randomly generated key value for shared memory: 920004285
	key_t controlKey = 920004285;
	
	//The shared memory contains 1024 segments of 8192 bytes (8KB) in length.
	size_t controlSize = 8388608;
    	
	//Attempt to create a new memory segment.
	controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR);
	
	if (controlID == -1) {
		//Fatal error.  Unknown error with shmget.
		RetVal += "&Status=Fail&Reason=Unknown error with shmget on existing section of memory set aside for control.";
		return RetVal;
	}
		
	//Attach to the memory segment.
	controlPointer = (char*)shmat(controlID, NULL, 0);

	//Search for an empty comm slot.
	//Note, I use a simple locking mechanism here that will greatly reduce R/W collisions, but is not actually
	//completely thread-safe.  That's because between checking a zero bit and setting the bit to one, this process
	//can be made to sleep or another process on another CPU can intervene.  It's much better than nothing and is
	//simple enough for now.
	
	//Mailbox format:  Byte 0 = Taken/Free flag; Byte 1 = Message for server flag; Byte 2 = Message for client flag.  
	//Byte 3 + 4 = size of message.  Byte 5+ = message.
	//No thread issues since only one server-client per segment and always only read or write not both.
	
	for (int i = 1; i < 255; i++){ 
		
		tSlot = i * 32768;

		//The first byte in a segment indicates ownership.  Byte = One if claimed and Zero if unclaimed.
		if (controlPointer[tSlot] == 0x0){
			//Claim the slot.
			controlPointer[tSlot] = 0x1;
			
			string User = GetValueFromKey("u");
			
			//Message for Server Flag
			controlPointer[tSlot+1] = 0x1;
			//Size of Message = 1
			controlPointer[tSlot+4] = (unsigned char)User.size();
			//Message = ID of noew Box owner
			sprintf(controlPointer[tSlot+5], User.c_str());
		}
		
	}
	
	//Wait for a response from the game service.
	//Response will incluse a session ID, confirmed slot number for message exchange, starting position, 
	//full character stats, map, nearby enemies...
	

	
	RetVal += "&Slot=" + to_string(Slot);
	
	while (controlPointer[Slot * 32768 + 2] == 0x0){
		// Sleep for 3 microseconds and then check again.
		nanosleep (&req, &rem);	
	}
	
	size_t messageLen = (int)((unsigned char)controlPointer[3]) * 256 + (int)((unsigned char)controlPointer[4]);
	
	string Temp(reinterpret_cast<const char *>(controlPointer[5]), messageLen);
	RetVal += Temp;
	return RetVal;
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

