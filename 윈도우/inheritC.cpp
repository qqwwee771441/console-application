#define UNICODE
#define _UNICODE
// WIN64
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int wmain(int argc, wchar_t* argv[]);
int main() { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {
	_fputts(_T("Inherit Child Main\n"), stdout);
	
	/******************** Get Environment Variable ********************/
	TCHAR value[100];
	if(GetEnvironmentVariable(_T("KEY"), value, 100)) {
		_tprintf(_T("value: %s\n"), value);
	}
	
	/******************** Scan Handle from File ********************/
	HANDLE hMailSlot;
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	_ftscanf(file, _T("%d"), &hMailSlot);
	fclose(file);
	_tprintf(_T("Handle: %d\n"), hMailSlot);
	
	/******************** Send Message ********************/
	TCHAR message[100];
	DWORD bytes;
	while(true) {
		_fputts(_T("message>> "), stdout);
		_fgetts(message, sizeof(message)/sizeof(TCHAR), stdin);
		
		if(!WriteFile(hMailSlot, message,  // Write Message
					  _tcslen(message)*sizeof(TCHAR),
					  &bytes, NULL
		)) {
			_fputts(_T("Write Failed\n"), stdout);
			_gettchar();
			CloseHandle(hMailSlot);
			return 1;
		}
		
		if(!_tcscmp(message, _T("exit"))) {  // if "exit" : break
			_fputts(_T("Exit\n"), stdout);
			break;
		}
	}
	
	/******************** Close Handle ********************/
	CloseHandle(hMailSlot);
	
	return 0;
}

