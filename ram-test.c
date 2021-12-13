/*

memtest - Test how much RAM usage until paging initiated, & test RAM is good or corrupted.

*****************************************

**Disable Paging:
System Properties > Advanced > Performance > Advanced > Virtual Memory (Change) > No paging file

** Build & Run:
build.bat

** Result:
- Windows 10 64-bit (8 GB RAM): 4.96 GB
- Windows 10 64-bit (24 GB RAM): 20 GB
- Windows 10 64-bit (32 GB RAM): 28 GB

** Conclusion:
Windows 10 64-bit need at least 3-4 GB RAM (2.6 GB for OS, the rest for paging).


*/


#include <stdio.h>
#include <malloc.h>
#include <windows.h>

int main () {
	float size = 28.0f;		// RAM size in GB
	UINT64 i;
	UINT64 count = 0;
	int sleep_time = 10;	// second
	
	UINT64 mem_allocation = (UINT64) size * 1E+9;
	UINT8 *b = malloc(mem_allocation);
	
	puts("memset 0xFF ...");
	memset(b, 0xFF, size * 1E+9);
	
	puts("memset 0x00 ...");
	memset(b, 0x00, size * 1E+9);
	
	puts("sleeping...");
	Sleep(sleep_time * 1000);
	
	for (i=0; i<mem_allocation; i++)
		count += b[i];
	
	if (count == 0)
		puts("RAM Ok!");
	else
		puts("RAM Corrupt!");
	
	
	puts("end");
	return 0;
}
