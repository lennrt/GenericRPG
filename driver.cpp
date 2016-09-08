#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>


//Structure for HTTP form data
struct FormInfo{
    string Key;
    string Value;
};

//Vector to hold Key / Value pairs after processing
vector<FormInfo> FormData;


int main(){
    
    //Redirect Error messages to stdout - This will cause them to appear on the web page
    dup2(STDOUT_FILENO, STDERR_FILENO);
    
    //Set HTTP Header
    cout << "Content-type: text/plain\n\r\n\r";
    
    //Process incoming POST data
    GetFormData();
    
    //Load system state from shared memory
    
    //Check action based on POST:
      
    //User login
    
    //User setup
    
    //Character login
    
    //Character setup
    
    //Game in progress action
    
    //Perform a character action
    
    //Perform an inventory action
    
    //Perform a world action
    
    //Perform targetting action
    
    //Perform update action only
    
    
}

void GetFormData(){
    int EnvLen = atoi(getenv("CONTENT_LENGTH"));
    int Start = 0;
    int Mid = 0;
    FormInfo NewData;
    string Env;

    //cin can technically recieve more than CONTENT_LENGTH.
    //We'll use EnvLen to restrict what we read.
    cin >> Env;

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
            NewData.Value = HexToString(Env.substr(Mid, i - Mid));
            FormData.push_back(NewData);
            Start = i + 1;
        }
    }
}
