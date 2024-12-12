#include "background_process.hpp"
#include <iostream>
#include <string>

using namespace std;

void start_background_process(const string &path)
{
    #ifdef _WIN32
        PROCESS_INFORMATION processInfo;
    #else
        pid_t processInfo;
    #endif

    try {
        if (!run(path, &processInfo)) {
            std::cerr << "Failed to start program." << std::endl;
        }

        int exitCode = wait(&processInfo);
        cout << "Program exited with code: " << exitCode << endl;
    } catch (exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}

int main()
{
    cout << "start main process" << endl;
    
    string path;

    #ifdef _WIN32
        path = ".\\Debug\\subprogram.exe";
    #else
        path = "./subprogram";
    #endif

    start_background_process(path);

    cout << "end main process" << endl;


    return 0;
}