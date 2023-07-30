#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include "execution.h"
#include <string.h>
#include <sys/stat.h>

const int GET_ALL_ARRIVALS_CHOICE = 1;
const int GET_FULL_SCHEDULE_CHOICE = 2;
const int GET_AIRPLANE_FLIGHTS_CHOICE = 3;
const int FETCH_DB_CHOICE = 4;
const int ZIP_DB_CHOICE = 5;
const int EXIT_CHOICE = 6;

extern const char* flightServicePath;
extern const char* dbServicePath;

void parentProccess(int* parentToChild,  int* childToParent, pid_t& pid);
void childProccess(int* parentToChild,  int* childToParent);
std::vector<std::string> readInputs(int pipeReadEnd);
bool zipDB();
void addFileToZip(zip* archive, const filesystem::path& filePath, const filesystem::path& relativePath);
void addDirectoryToZip(zip* archive, const filesystem::path& directoryPath, const filesystem::path& relativePath);
bool writeWithCheckErrno(int fd, const void* elem, size_t n);
bool readWithCheckErrno(int fd, void* elem, size_t n);
bool myMkFifo(const char* path);
bool createOutput(int choice, std::string& result, execution& db, int flights_service);
bool sendOutput(std::string& result, int db_service);
#endif