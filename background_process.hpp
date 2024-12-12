#ifndef BACKGROUND_PROCESS
#define BACKGROUND_PROCESS

#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/wait.h>
    #include <unistd.h>
#endif

using namespace std;

bool run(const std::string& executablePath, void* processInfo);

int wait(void* processInfo);

#endif