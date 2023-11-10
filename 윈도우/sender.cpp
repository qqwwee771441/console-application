#define UNICODE
#define _UNICODE
// WIN64

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
/*
 * CreateFile
 * WriteFile
 * ReadFile
 * CloseHandle
 */


int wmain(int argc, wchar_t* argv[]);
int main() { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {
	_tprintf(_T("Sender Main \n"));
	
	/******************** Create Child and Separate ********************/
	STARTUPINFO si = {0,};
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	
	if(!CreateProcess(  // Create Child Process
		_T("mailslot.exe"), NULL,
		NULL, NULL,
		TRUE, CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi
	)) {
		_tprintf(_T("Create Process Failed \n"));
		return 1;
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	Sleep(1000);  // to fix code!!!! Problemable ~
	
	/******************** Connect MailSlot ********************/
	HANDLE hMailSlot = CreateFile(
		_T("\\\\*\\mailslot\\mailbox"),
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if(hMailSlot == INVALID_HANDLE_VALUE) {
		_tprintf(_T("Invalid Handle Value \n"));
		return 1;
	}
	else {
		_tprintf(_T("Connect MailSlot Success \n"));
	}
	
	/******************** Write MailSlot ********************/
	TCHAR message[100];
	DWORD bytes;
	while(true) {
		_tprintf(_T("message>> "));
		_tscanf(_T("%s"), message);
		
		if(!WriteFile(hMailSlot,  // Write MailSlot
					  message,
					  _tcslen(message)*sizeof(TCHAR),
					  &bytes,
					  NULL
		)) {
			_tprintf(_T("Write File Failed \n"));
			CloseHandle(hMailSlot);
			return 1;
		}
		
		if(!_tcscmp(message, _T("exit"))) {
			_fputts(_T("Exit \n"), stdout);
			break;
		}
	}
	
	/******************** Close MailSlot ********************/
	CloseHandle(hMailSlot);
	
	return 0;
}

