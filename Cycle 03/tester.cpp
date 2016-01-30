#include <stdio.h>
#include <iostream>
#include <windows.h>

class BaseClass {

public:
	virtual void PrintHello(void) { 
		puts("[*] BaseClass->PrintHello"); 
	}
};

class ChildClass : public BaseClass {

public:
	virtual void PrintHello(void) {
		puts("[*] ChildClass->PrintHello");
	}
};

void __fastcall Hooked(ChildClass* This, void* _EDX){
	puts("[:] Hooked!");
}

int main(void) {

	int choice = 0;

	puts("Enter a value:");
	scanf("%d",&choice);

	ChildClass *a = new ChildClass();

	DWORD protection = PAGE_READWRITE;
	DWORD oldProtections;

	DWORD * vTable = (DWORD*)*(DWORD*)a;
	MEMORY_BASIC_INFORMATION mbi;

	while(choice != 0)
	{
		switch(choice){
			case 1:

				printf("[!] Vtable:\t0x%08x\n",*a);
				printf("[!] Hooked:\t0x%08x\n",Hooked);
				a->PrintHello();
	
				VirtualQuery((LPCVOID)vTable, &mbi,sizeof(mbi));

				//VirtualProtectEx(process,&a,sizeof(int),protection, &oldProtections);

				__asm{ int 3 }

				VirtualProtect(mbi.BaseAddress,mbi.RegionSize, PAGE_READWRITE,&mbi.Protect);

				vTable[0] = (DWORD) Hooked;
				
				VirtualProtect(mbi.BaseAddress,mbi.RegionSize,mbi.Protect, &mbi.Protect);

				printf("[!] Vtable:\t0x%08x\n",*a);

				a->PrintHello();
				
			break;

			case 2:
				puts("[*] ChildClass");
				a->PrintHello();
			break;
		}

		scanf("%d",&choice);
	}

	delete(a);

	return 0;
}