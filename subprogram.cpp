#include <iostream>

using namespace std;

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif 

static void sleep(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

int main() {
    cout << "Subprogram starts" << endl;
    sleep(5000);
    cout << "Subprogram ends" << endl;
    return 1;
}