// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

extern void InstallHooks();

void PatchGame()
{
    // Don't do anything until the game reports it has loaded to a certain stage //
    while (*(int*)0xC8D4C0 < 9)
        Sleep(10);

    InstallHooks();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PatchGame, NULL, 0, 0);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

