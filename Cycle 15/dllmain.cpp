// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "stdio.h"
#include "windows.h"

extern "C" __declspec(dllexport) void DummyFunc(void) {
	//do nothing
	return;
}

void __declspec(naked) HookedMessageBoxW(void) {
	MessageBoxA(NULL, "HOOKED", "CAP", NULL);
}

char*msg = "Message";
char*cap = "Caption";
char*user = "user32.dll";
char*proc = "CreateFileW";
LPVOID hOrigCreateFile = 0;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{

	char op_jmp[1] = { '\xEB' };
	char short_jmp[1] = { '\xF9' };
	char long_jmp[1] = { '\xE9', };
	char target_addy[4] {0};
	char hookedFunc[4] = {'\xAA','\xBB','\xCC','\xDD'};

	//FILE *fResults;
	//fopen_s(&fResults, "C:\\Users\\Josh-DSU\\Desktop\\hook.txt", "a+");

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		__asm {
			int 3
		}

		//fprintf(fResults, "DLL Attach Called\n");
		DWORD oldProtect = 0;

		// Get Target Function Address
		DWORD hMBox = (DWORD)GetProcAddress(GetModuleHandle("user32.dll"), "MessageBoxW");

		if (hMBox == NULL){
			return;
		}

		//Hook Function
		/*HMODULE hHookedMBox = GetModuleHandle("helper.dll");

		if (hHookedMBox == NULL) {
			return;
		}


		//Meh
		/*target_addy[0] = hookedFunc >> 0;
		target_addy[1] = hookedFunc >> 8;
		target_addy[2] = hookedFunc >> 16;
		target_addy[3] = hookedFunc >> 24;*/

		/*if (hookedFunc == NULL) {
			return;
		}*/

		BYTE *pbTargetAddress = (BYTE *)hMBox;
		BYTE *pbHook = (BYTE *)HookedMessageBoxW;

		//Make the target function writeable
		VirtualProtect((LPVOID)hMBox, 20, PAGE_EXECUTE_READWRITE, &oldProtect);

		//Hook Function - create the short jump
		memcpy((void*)hMBox, op_jmp, 1);
		memcpy((void*)(hMBox + 1), short_jmp, 1);

		//create our long jump
		memcpy((void*)(hMBox - 5), long_jmp, 1);
		memcpy((void*)(hMBox - 4), pbHook, 4);
	}

		break;
	case DLL_THREAD_ATTACH:

		break;
	case DLL_THREAD_DETACH:

		break;

	case DLL_PROCESS_DETACH:

		break;
	}

	//fclose(fResults);

	return TRUE;
}



