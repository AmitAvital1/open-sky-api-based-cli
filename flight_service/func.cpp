
#include "header.h"
using namespace std;

// reads num of strings from user and writes it to the db service server.
// if the write was succesful, returns true.
bool getInputsAndWriteToPipe(int numStrings, int pipe_out, int choice){
    vector<string> inputs = getInputs(numStrings);
    if(!writeWithCheckErrno(pipe_out, &choice, sizeof(int)) && choice != 6){ 
        return false;
    }
    if(!writeWithCheckErrno(pipe_out, &numStrings, sizeof(int))){
        return false;
    }
    for(string input:inputs){
        int sizeOfInput = (int)input.size();
        writeWithCheckErrno(pipe_out, &sizeOfInput, sizeof(int));
        if(errno == EPIPE){
            return false;
        }
        writeWithCheckErrno(pipe_out, input.c_str(), sizeOfInput + 1);
        if(errno == EPIPE){
            return false;
        }
    }
    return true;
}

vector<string> getInputs(int numStrings){
    vector<string> inputs;
    std::cin.ignore(); // Ignore the newline character from previous input
    for (int i = 0; i < numStrings; ++i) {
        string input;
        std::cout << "Enter input " << i + 1 << ": ";
        std::getline(std::cin, input);
        inputs.push_back(input);
    }
    return inputs;
}

void checkNumStringsInput(int& numStrings){
    while(numStrings <= 0){
        cout << "Invalid input, please try again enter positive number: " << endl;
        cin >> numStrings;
    }
}
void printMenu(){
    std::cout << "Menu:\n";
        std::cout << "1. Fetch airports incoming flights.\n";
        std::cout << "2. Fetch airports full flights schedule.\n";
        std::cout << "3. Fetch aircraft full flights schedule.\n";
        std::cout << "4. Fetch DB\n";
        std::cout << "5. Zip DB files\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
}

bool readChoice(int* pchoice){
    int choice;
    std::cin >> choice;
    
    if(choice < 1 || choice > 6){
        return false;
    }
    *pchoice = choice;
    return true;
}


void printdbNotAvailable(int dbFd,int flightFd){
    cout<<"DB is not available. try again later"<<endl;
    fsync(dbFd);
    fsync(flightFd);
}
// a function that writes to the fd. if it cannot read  and the the reason is a broken pipe, returns false.
bool writeWithCheckErrno(int fd, const void* elem, size_t n){
    int res = write(fd, elem, n);
    if(errno == EPIPE && res == -1)
        return false;
    return true;
}
// same as write but for read.
bool readWithCheckErrno(int fd, void* elem, size_t n){
    int res =read(fd, elem, n);
    if(errno == EPIPE && res == -1){
        return false;
    }
    return true;
}
// read withe check, gets also a pointer to int to store the num of bytes that was read
bool readWithCheckErrno(int fd, void* elem, size_t n,int* numBytes){
    *numBytes = read(fd, elem, n);
    if(errno == EPIPE && *numBytes == -1)
        return false;
    return true;
}

// creates a fifo in the path. return false if cannot create the fifo, exludes the option that it it
// already exist.
bool myMkFifo(const char* path){
    if(mkfifo(path,0666) == -1){
        if(errno != EEXIST){
             return false;
        }
    }
    return true;
}

// a function to send input to the server, using the flightService named pipe.
// gets the choice and the fd of flightsService pipe
// get input from user and sends it to the db server.
// returns true if the sending was succesfull.
bool sendInputs(int choice, int flightsService){

    int numStrings;
    string input;
    string userString;
    switch(choice)
    {
        case GET_AIRPLANE_FLIGHTS_CHOICE:
        {
            cout<<"Enter the name of airplane you want get details: "<<endl;
            numStrings = 1;
            break;
        }
        case FETCH_DB_CHOICE:
        case GET_ALL_ARRIVALS_CHOICE:
        case GET_FULL_SCHEDULE_CHOICE:
        {
            cout<<"Enter the number of airports you want get details: "<<endl;
            std::cin >> numStrings;
            checkNumStringsInput(numStrings);
            break;
        }
        case ZIP_DB_CHOICE:
        {
            if(!writeWithCheckErrno(flightsService, &choice, sizeof(int))){
                return false;
            }
            return true;
        }
        case EXIT_CHOICE:
        {
            write(flightsService, &choice, sizeof(int));
            return true;
        }
    }
    if(!getInputsAndWriteToPipe(numStrings, flightsService, choice)){
        return false;
    }
    return true;
}


// read the output from the db server.
// gets the db service named pipe's fd, and a reference to a string.
// stores the output inside outputDest.
bool readOutput(int dbService, string& outputDest){

    vector<string> bufferVector;
    int sizeOfResult;
    if(!readWithCheckErrno(dbService, &sizeOfResult, sizeof(sizeOfResult))){
        return false;
    }
    bool flag = false;
    while(sizeOfResult > 0 && !flag){
        char buffer[1200000];
        int bytesRead;
        if((!readWithCheckErrno(dbService, buffer, sizeof(buffer), &bytesRead))){
            flag = true;
            break;
        }
        bufferVector.push_back(buffer);
        sizeOfResult -= bytesRead;
    }
    if(flag){
        return false;
    }
    for(string& str:bufferVector){
        outputDest += str;
    }
    outputDest += "\n";
    return true;
}