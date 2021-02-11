// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <string.h>
#include "main.h"



int WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    
    std::cout << "Starting Routine..." << std::endl;

    uintptr_t socialClubPtr = (uintptr_t)GetModuleHandle(L"socialclub.dll");
    HWND hWindow = *(HWND*)(socialClubPtr + 0x9BEAE0); // socialclub.dll+9BEAE0 - pointer to window handle

    std::cout << "[!] hWnd: 0x" << std::hex << hWindow << std::endl;

    RenderHandler::Initialize(hModule, hWindow);
    
    while (true)
    {
        if (GetAsyncKeyState(VK_HOME)) {
            std::cout << "Starting Ejection.." << std::endl;
            RenderHandler::Shutdown();
            break;
        }
        Sleep(10);
    }

    
    CloseHandle(hModule);
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

