#define UNICODE
#define _UNICODE
// WIN64
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
/*
 * FILE
 * _tfopen _ftprintf fclose
 * DuplicateHandle
 * SetEnvironmentVariable
 * GetEnvironmentVariable
 */

int wmain(int argc, wchar_t* argv[]);
int main() { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {
	_fputts(_T("Parent Main\n"), stdout);
	
	/******************** Set Environment Variable ********************/
	SetEnvironmentVariable(_T("KEY"), _T("VALUE"));
	
	/******************** Duplication out of Pseudo ********************/
	HANDLE hProcess;
	if(!DuplicateHandle(GetCurrentProcess(),
						GetCurrentProcess(),
						GetCurrentProcess(),
						&hProcess, 0, TRUE, DUPLICATE_SAME_ACCESS
	)) {
		_fputts(_T("Duplicate Handle Failed\n"), stdout);
		return 1;
	}
	
	/******************** MailSlot Security ********************/
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	
	/******************** Connect MailSlot ********************/
	HANDLE hMailSlot = CreateFile(
		_T("\\\\*\\mailslot\\mailbox"),
		GENERIC_WRITE, FILE_SHARE_READ,
		&sa, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL
	);
	if(hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Invalid Handle Value\n"), stdout);
		return 1;
	}
	
	/******************** Write Handle on File ********************/
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%d"), hMailSlot);
	fclose(file);
	_tprintf(_T("Handle: %d\n"), hMailSlot);
	
	/******************** Create Child Process ********************/
	STARTUPINFO si = {0,};
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	
	if(!CreateProcess(_T("inheritC.exe"), NULL,
					  NULL, NULL,
					  TRUE, CREATE_NEW_CONSOLE|CREATE_UNICODE_ENVIRONMENT,
					  NULL, NULL,
					  &si, &pi
	)) {
		_fputts(_T("Create Process Failed\n"), stdout);
		return 1;
	}
	
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

