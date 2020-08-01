#include "pch.h"

/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        multiplayer_sa/multiplayer_hooksystem.cpp
 *  PURPOSE:     Multiplayer module hook system methods
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#define MAX_JUMPCODE_SIZE 50

////////////////////////////////////////////////////////////////////

template <class T, class U>
void MemPutFast(U ptr, const T value)
{
    *(T*)ptr = value;
}

////////////////////////////////////////////////////////////////////

BYTE* CreateJump(DWORD dwFrom, DWORD dwTo, BYTE* ByteArray)
{
    ByteArray[0] = 0xE9;
    MemPutFast<DWORD>(&ByteArray[1], dwTo - (dwFrom + 5));
    return ByteArray;
}

////////////////////////////////////////////////////////////////////

BOOL HookInstall(DWORD dwInstallAddress, DWORD dwHookHandler, int iJmpCodeSize)
{
    BYTE JumpBytes[MAX_JUMPCODE_SIZE];
    memset(JumpBytes, 0x90, MAX_JUMPCODE_SIZE);
    if (CreateJump(dwInstallAddress, dwHookHandler, JumpBytes))
    {  
        memcpy((PVOID)dwInstallAddress, JumpBytes, iJmpCodeSize);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}