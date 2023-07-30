#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "header.h"


int flights_service = -1;
int db_service = -1;
const char* flightServicePath = "./flights_pipes/flights_service";
const char* dbServicePath = "./flights_pipes/db_service";

void signalHandler(int signum){
    if(signum == SIGPIPE){
        fsync(flights_service);
        fsync(db_service);
    }
}

int main(){
    signal(SIGPIPE, signalHandler);

    if(!myMkFifo(dbServicePath) || !myMkFifo(flightServicePath)){
        std::cerr << "Error creating flights_service fifo" << std::endl;
            return -1;
    }

    flights_service = open(flightServicePath, O_RDONLY);

    if (flights_service == -1) {
        std::cerr << "Error opening named pipe for reading." << std::endl;
        return -1;
    }

    db_service = open(dbServicePath, O_WRONLY);

    if (db_service == -1) {
        std::cerr << "Error opening named pipe for writing." << std::endl;
        return -1;
    }

    execution db;

    int choice;
    string result;

    while(true){
        if(!readWithCheckErrno(flights_service, &choice, sizeof(int))){
            continue;
        }
        if(choice == EXIT_CHOICE){
            break;
        }
        if(!createOutput(choice, result, db, flights_service)){
            continue;
        }
        if(!sendOutput(result, db_service)){
            continue;
        }
    }
    close(db_service);
    close(flights_service);
    return 0;
}





