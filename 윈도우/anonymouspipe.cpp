#define UNICODE
#define _UNICODE
// WIN64
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int wmain(int argc, wchar_t* argv[]);
int main() { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {
	_fputts(_T("Anonymous Pipe Main\n"), stdout);
	
	/******************** Create Anonymous Pipe ********************/
	HANDLE hReadPipe, hWritePipe;
	if(!CreatePipe(&hReadPipe, &hWritePipe, NULL, 0)) {
		_fputts(_T("Create Pipe Failed\n"), stdout);
		return 1;
	}
	
	/******************** Write on Pipe ********************/
	TCHAR message[] = _T("Message");
	DWORD bytes;
	if(!WriteFile(hWritePipe,
				  message,
				  lstrlen(message)*sizeof(TCHAR),
				  &bytes,
				  NULL
	)) {
		_fputts(_T("Write Failed\n"), stdout);
		return 1;
	}
	
	/******************** Read at Pipe ********************/
	TCHAR string[100];
	DWORD bytesRead;
	if(!ReadFile(hReadPipe, string,
				 bytes, &bytesRead, NULL
	)) {
		_fputts(_T("Read Failed\n"), stdout);
		return 1;
	}
	
	/******************** Print ********************/
	string[bytesRead/sizeof(TCHAR)] = 0;
	_tprintf(_T("read: %s\n"), string);
	
	/******************** Close Handle ********************/
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	
	return 0;
}

