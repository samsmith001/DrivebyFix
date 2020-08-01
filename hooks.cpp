#include "pch.h"

#define HOOKPOS_CTask_PlayerTarget_Driveby 0x621A57

extern BOOL HookInstall(DWORD dwInstallAddress, DWORD dwHookHandler, int iJmpCodeSize);

char pGunDirection;
DWORD pProcessPed;

VOID _declspec(naked) CTask_PlayerTarget_Driveby()
{
	_asm
	{
		mov     pGunDirection, al
		mov     pProcessPed, edi
		pushad
	}

	// pProcessPed is the ped aiming during a driveby. //
	// 0x58c is the current vehicle of the player (we're making sure it exists). //
	// 0x1c & 1 is the collision flag. We set this to true, but also set 0x128 to the current vehicle so it is ignored. //
	if (pProcessPed && (pProcessPed + 0x58c) && (pProcessPed + 0x1c & 1) == 0)
	{	
		*(DWORD*)(pProcessPed + 0x1c) = *(DWORD*)(pProcessPed + 0x1c) | 1;
		*(DWORD*)(pProcessPed + 0x128) = *(DWORD*)(pProcessPed + 0x58c);
	}
	
	_asm
	{
		popad
		movsx   eax, pGunDirection

		mov     edx, HOOKPOS_CTask_PlayerTarget_Driveby
		add     edx, 6
		cmp     eax, 3
		jmp     edx

	}
}

void InstallHooks()
{
	HookInstall(HOOKPOS_CTask_PlayerTarget_Driveby, (DWORD)CTask_PlayerTarget_Driveby, 6);
}