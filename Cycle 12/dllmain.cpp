// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "stdio.h"
#include "windows.h"

extern "C" __declspec(dllexport) void DummyFunc(void) {
	//do nothing
	return;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	FILE *fResults;
	fopen_s(&fResults, "C:\\Users\\Josh-DSU\\Desktop\\hook.txt", "a+");

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		fprintf(fResults, "DLL Attach Called\n");

		break;
	case DLL_THREAD_ATTACH:
		fprintf(fResults, "DLL Thread Attach Called\n");

		break;
	case DLL_THREAD_DETACH:
		fprintf(fResults, "DLL Thread Detach Called\n");

		break;

	case DLL_PROCESS_DETACH:

		fprintf(fResults, "DLL Detach Called\n");

		break;
	}

	fclose(fResults);

	return TRUE;
}

