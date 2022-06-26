#include <iostream>
#include <Windows.h>

using std::cout;
using std::endl;
using std::cin;

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::system("cls");
    SetConsoleTextAttribute(hConsole, 11);
	cout << "\n" << 
"                                                |               " << "\n" <<
"                          ,------------=--------|___________|   " << "\n" <<
"   ";SetConsoleTextAttribute(hConsole, 10);cout<<"</>"; SetConsoleTextAttribute(hConsole, 4);cout <<
"   -=============";SetConsoleTextAttribute(hConsole, 11);cout<<"%%%|         |  |______|_|___________|   " << "\n" <<
"                          | | | | | | ||| | | | |___________|   " << "\n" <<
"                          `------------=--------|           |   " << "\n" <<
"                                                |               " << "\n\n" << endl;
    SetConsoleTextAttribute(hConsole, 2);

    LPCSTR DllPath = "main.dll"; // change to path of desired DLL

    int procID;
    cout << "Enter the procID of target process: ";
    cin >> procID;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1,
        MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath,
        strlen(DllPath) + 1, 0);
    HANDLE hLoadThread = CreateRemoteThread(hProcess, nullptr, 0,
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
        "LoadLibraryA"), pDllPath, 0, nullptr);
    if (hLoadThread != nullptr && hLoadThread != INVALID_HANDLE_VALUE) {
        cout << "Loaded remote thread" << endl;
    } else {
        cout << "Error loading thread: %x", GetLastError();
        CloseHandle(hLoadThread);
        exit(-1);
    }
    WaitForSingleObject(hLoadThread, INFINITE);
    cout << "DLL allocated at: %x" << std::hex << pDllPath << endl;
    VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);
    SetConsoleTextAttribute(hConsole, 7);
    CloseHandle(hLoadThread);
    CloseHandle(hProcess);
    CloseHandle(hConsole);
    return 0;
}