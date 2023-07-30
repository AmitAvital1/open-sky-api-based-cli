#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

extern const char* flightServicePath;
extern const char* dbServicePath;

const int GET_ALL_ARRIVALS_CHOICE = 1;
const int GET_FULL_SCHEDULE_CHOICE = 2;
const int GET_AIRPLANE_FLIGHTS_CHOICE = 3;
const int FETCH_DB_CHOICE = 4;
const int ZIP_DB_CHOICE = 5;
const int EXIT_CHOICE = 6;

bool getInputsAndWriteToPipe(int numStrings, int pipe_out, int choice);
void checkNumStringsInput(int& numStrings);
void printMenu();
bool readWithCheckErrno(int fd, void* elem, size_t n);
bool writeWithCheckErrno(int fd, const void* elem, size_t n);
bool readWithCheckErrno(int fd, void* elem, size_t n,int* numBytes);
void printdbNotAvailable(int dbFd,int flightFd);
bool myMkFifo(const char* path);
bool readChoice(int* pchoice);
bool sendInputs(int choice, int flightsService);
bool readOutput(int dbService, std::string& outputDest);
void cleanBuffer();
std::vector<std::string> getInputs(int numStrings);
#endif
