#include "background_process.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;


#ifdef _WIN32
    typedef PROCESS_INFORMATION ProcessInfoType;
#else
    typedef pid_t ProcessInfoType;
#endif

bool run(const std::string& executablePath, void* processInfo) {
#ifdef _WIN32
    auto info = reinterpret_cast<ProcessInfoType*>(processInfo);
    ZeroMemory(info, sizeof(*info));

    STARTUPINFO startupInfo{};
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    if (!CreateProcess(
            executablePath.c_str(),
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &startupInfo,
            info
        )) {
        DWORD lastError = GetLastError();
        cerr << "Error executing program: " << lastError << endl;
        return false;
    }

    return true;
#else
    auto pid = reinterpret_cast<ProcessInfoType*>(processInfo);
    *pid = fork();
    if (*pid == 0) {
        execl("/bin/sh", "sh", "-c", executablePath.c_str(), NULL);
    } else if (*pid < 0) {
        throw runtime_error("Could not create a child process.");
    }

    return true;
#endif
}


int wait(void* processInfo) {
#ifdef _WIN32
    auto info = reinterpret_cast<ProcessInfoType*>(processInfo);
    WaitForSingleObject(info->hProcess, INFINITE);
    DWORD exitCode;
    GetExitCodeProcess(info->hProcess, &exitCode);
    return static_cast<int>(exitCode);
#else
    auto pid = reinterpret_cast<ProcessInfoType*>(processInfo);
    int status;
    waitpid(*pid, &status, 0);
    return WEXITSTATUS(status);
#endif
}
