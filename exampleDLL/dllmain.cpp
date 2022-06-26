#include <Windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>


//basic logger, can be removed
//#include "logger.h"


DWORD WINAPI MainFunc(HMODULE hModule)
{
    //your code goes here
    
    while (true) {
        if (GetAsyncKeyState(VK_F6) & 1) {
            MessageBoxA(NULL, "You pressed F6!", "Injector", MB_OK);
        }
        else if (GetAsyncKeyState(VK_END) & 1) {
            MessageBoxA(NULL, "Goodbye World!", "Injector", MB_OK);
            break;
        }
        Sleep(100);
    }
    //code is over, eject the DLL
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD   ul_reason_for_call,
                       LPVOID  lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            //load MainFunc and execute it
            CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainFunc, hModule, 0, NULL));
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return true;
}