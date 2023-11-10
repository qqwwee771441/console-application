#define UNICODE
#define _UNICODE
// WIN64

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
/*
 * CreateMailSlot
 */

int wmain(int argc, wchar_t* argv[]);
int main() { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {
	_tprintf(_T("Mail Slot Main \n"));
	
	/******************** Create MailSlot ********************/
	HANDLE hMailSlot = CreateMailslot(
		_T("\\\\.\\mailslot\\mailbox"),
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL
	);
	if(hMailSlot == INVALID_HANDLE_VALUE) {
		_tprintf(_T("Invalid Handle Value \n"));
		return 1;
	} else {
		_tprintf(_T("Create MailSlot Success \n"));
	}
	
	/******************** Read MailSlot ********************/
	TCHAR message[100];
	DWORD bytes;
	while(true) {
		if(!ReadFile(hMailSlot,
					 message,
					 sizeof(TCHAR)*100,
					 &bytes,
					 NULL
		)) {
			_tprintf(_T("Read File Unsuccess \n"));
			return 1;
		}
		if(!_tcsncmp(message, _T("exit"), 4)) {
			_tprintf(_T("Exit \n"));
			break;
		}
		
		/******************** Print Message ********************/
		message[bytes/sizeof(TCHAR)] = 0;
		_tprintf(_T("%s \n"), message);
	}
	
	/******************** Close MailSlot ********************/
	CloseHandle(hMailSlot);
	
	return 0;
}

