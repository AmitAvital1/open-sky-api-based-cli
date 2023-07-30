
#include "header.h"

//read inputs from the client flights service.
// returns a vector of the inputs.
std::vector<std::string> readInputs(int fd){
    int numStrings = 0;
    
    int res;
    res = read(fd, &numStrings, sizeof(numStrings));

    if(errno == EPIPE && res == -1)
        return std::vector<std::string>();

    std::vector<std::string> strings(numStrings);
    for (int i = 0; i < numStrings; ++i) {
        char buffer[256];
        int sizeOfInput;
        res = read(fd, &sizeOfInput, sizeof(int));
        res = read(fd, buffer, sizeOfInput + 1);

        if(errno == EPIPE && res == -1)
            return std::vector<std::string>();

        strings[i] = buffer;
    }
    return strings;
}

// zips the db to the current directory.
bool zipDB(){
    bool res = true;

    const string libraryPath = "./flightDB/";
    const string zipFilename = "DB.zip";

    if (!(std::filesystem::exists(libraryPath) && std::filesystem::is_directory(libraryPath))) {
        return false;
    } 

    int error;
    zip* archive = zip_open(zipFilename.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &error);
    if (!archive) {
        //std::cerr << "Failed to create ZIP archive: " << zip_strerror(archive) << std::endl;
        return false;
    }
    filesystem::path libraryDirectory(libraryPath);
    if (filesystem::exists(libraryDirectory) && filesystem::is_directory(libraryDirectory)) {
        addDirectoryToZip(archive, libraryDirectory, filesystem::path(""));
    } else {
        cerr << "Invalid library path: " << libraryPath << endl;
        zip_close(archive);
        return 1;
    }

    if (zip_close(archive) == -1) {
        //std::cerr << "Failed to close ZIP archive: " << zip_strerror(archive) << std::endl;
        return false;
    }
    return res;
}
void addFileToZip(zip* archive, const filesystem::path& filePath, const filesystem::path& relativePath) {
    std::string fileStr = filePath.string();

    zip_source* source = zip_source_file(archive, fileStr.c_str(), 0, -1);
    if (!source) {
        std::cerr << "Failed to add file to ZIP archive: " << zip_strerror(archive) << std::endl;
        return;
    }

    std::string relativePathStr = relativePath.string();
    zip_int64_t index = zip_file_add(archive, relativePathStr.c_str(), source, ZIP_FL_OVERWRITE);
    if (index == -1) {
        //std::cerr << "Failed to add file to ZIP archive: " << zip_strerror(archive) << std::endl;
        zip_source_free(source);
        return;
    }
}

void addDirectoryToZip(zip* archive, const filesystem::path& directoryPath, const filesystem::path& relativePath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        const auto& path = entry.path();
        const auto& relativeSubPath = relativePath / path.filename();

        if (filesystem::is_directory(path)) {
            addDirectoryToZip(archive, path, relativeSubPath);
        } else if (filesystem::is_regular_file(path)) {
            addFileToZip(archive, path, relativeSubPath);
        }
    }
}

// writes to fd and checks if failed because of broken pipe.
bool writeWithCheckErrno(int fd, const void* elem, size_t n){
    int res = write(fd, elem, n);
    if(res <= 0)
        return false;
    return true;
}
// reads from fd and checks if failed because of broken pipe.
bool readWithCheckErrno(int fd, void* elem, size_t n){
    int res = read(fd, elem, n);
    if(res <= 0){
        sleep(6);
        return false;
    }
    return true;
}

// create fifo in path. if fails, returns false, not including the scenario of existence of the fifo.
bool myMkFifo(const char* path){
    if(mkfifo(path,0666) == -1){
        if(errno != EEXIST){
             return false;
        }
    }
    return true;
}

// writes into strings the inputs the is read from fd.
// returns false if no input was read.
bool getInputsToVector(int fd, std::vector<std::string>& strings){
    strings = readInputs(fd);
    if(strings.size() == 0)
        return false;
    return true;
}

// takes the choice and inserts into result the output, based on choice.
bool createOutput(int choice, string& result, execution& db, int flights_service){
    std::vector<std::string> strings;
    if(choice != ZIP_DB_CHOICE)
    {
        if(getInputsToVector(flights_service, strings)){
            switch(choice){
                case GET_ALL_ARRIVALS_CHOICE:
                {
                    result = db.getAllArrivalFlightsDetails(strings);
                    return true;
                }
                case GET_FULL_SCHEDULE_CHOICE:
                {
                    result = db.getFullSchedule(strings);
                    return true;
                }
                case GET_AIRPLANE_FLIGHTS_CHOICE:
                {
                    result = db.getAirplaneFlight(strings[0]);
                    return true;
                }
                case FETCH_DB_CHOICE:
                {
                    result = db.fetchDB(strings);
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        bool isZipped = db.zipDB();
        if(isZipped)
            result = "Data Base ZIP archive created successfully";
        else
            result = "Data Base ZIP archive not created due error while zipping the files";
    }
    return true;
}

// writes back to the client the result of the operation.
bool sendOutput(std::string& result, int db_service){
    int sizeOfResult = result.size() + 1;
    if(!writeWithCheckErrno(db_service, &sizeOfResult, sizeof(int))){
        return false;
    }
    if(!writeWithCheckErrno(db_service, result.c_str(), result.size() + 1)){
        return false;
    }
    return true;
}