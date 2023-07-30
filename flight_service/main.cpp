#include "header.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

int flightsService = -1;
int dbService = -1;
const char* flightServicePath = "./flights_pipes/flights_service";
const char* dbServicePath = "./flights_pipes/db_service";

void signalHandler(int signum){ //whenever the pipe gets broken, flush the fifo from un-important data
    if(signum == SIGPIPE){
        fsync(flightsService);
        fsync(dbService);
    }
}

int main() {
    signal(SIGPIPE, signalHandler);
    
    if(!myMkFifo(dbServicePath) || !myMkFifo(flightServicePath)){
        std::cerr << "Error creating flights_service fifo" << std::endl;
            return -1;
    }

    flightsService = open(flightServicePath, O_WRONLY);

    if (flightsService == -1) {
        std::cerr << "Error opening named pipe for writing." << std::endl;
        return -1;
    }

    dbService = open(dbServicePath, O_RDONLY);

    if (dbService == -1) {
        std::cerr << "Error opening named pipe for reading." << std::endl;
        return -1;
    }

    int choice;
    while (true) {
        printMenu();
        if(!readChoice(&choice)){
            cout << "Invalid choice, please try again." << endl;
            continue;
        }
        if(!sendInputs(choice, flightsService))
        {
            printdbNotAvailable(dbService, flightsService);
        }
        if(choice == EXIT_CHOICE){
            break;
        }
        string output;
        if(choice == FETCH_DB_CHOICE){
            cout<<"Fetching in progress..."<< endl;
        }
        if(!readOutput(dbService, output))
        {
            printdbNotAvailable(dbService, flightsService);
            continue;
        }
        cout<<output;
    }
    close(dbService);
    close(flightsService);
    return 0;
}