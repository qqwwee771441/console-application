// 닷넷 MSDN
#define UNICODE
#define _UNICODE
// stdafx.h -> stdio.h, tchar.h
#include <stdio.h>   // wprintf wscanf fputws fgetws
#include <string.h>  // wcslen wcscpy wcsncpy wcscat wcsncat wcscmp wcsncmp
#include <locale.h>  // _wsetlocale(LC_ALL, L"korean");
#include <windows.h> // windows.h -> windef.h -> winnt.h
/*
 * CONST MAX_PATH 
 * CHAR WCHAR LPSTR LPCSTP LPWSTR LPCWSTP
 * BOOL
 * DWORD DWORD32 INT INT32 LONG LONG32 UINT UNIT32 ULONG ULONG32
 * DWORD64 INT64 LONG64 UINT64 ULONG64
 * PINT PINT32 PLONG PLONG32 PUINT PUINT32 PULONG PULONG32
 * PINT64 PLONG64 PUINT64 PULONG64
 * LONG_PTR ULONG_PTR INT_PTR UINT_PTR (Polymorphic)
 * DWORD GetLastError(void);
 * HANDLE
 * HANDLE CreateFile(~);
 * CreateProcess(~); 
 */
#include <tchar.h>   // TCHAR LPTSTR LPCTSTR _T("") _TEXT("") __T("")
/*
 * _tmain
 * _tprintf _tscanf _tputts _tgetts
 * _tcslen _tcscpy _tcsncpy _tcscat _tcsncat _tcscmp _tcsncmp
 * _tsetlocale(LC_ALL, _T("Korean"));
 * _tcstok _ttoi _gettchar
 */
#include <stdlib.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

// TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다. \n");
TCHAR ERROR_CMD[] = _T("'%s' is not an available program to run. \n");

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

int wmain(int argc, wchar_t* argv[]);

int main() {
	_tmain(0, NULL);
	
	return 0;
}

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[]) {
	
	/******************** TODO ********************/
	
	STARTUPINFO si = {0,};
	PROCESS_INFORMATION pi;
	
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	si.lpTitle = _T("I am a boy!");
	
	TCHAR command[] = _T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;
	
	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);
	
	SetCurrentDirectory(_T("C:\\WinSystem"));
	
	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);
	
	state = CreateProcess(
		NULL,
		command,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi
	);
	
	if(state != 0)
		_fputts(_T("Creation OK! \n"), stdout);
	else
		_fputts(_T("Creation Error! \n"), stdout);
	
	/******************** ********************/
	
	_tsetlocale(LC_ALL, _T("Korean"));
	
	DWORD isExit;
	while(1) {
		isExit = CmdProcessing();
		
		if(isExit == TRUE) {
			// _fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
			_fputts(_T("Let it exit processing command. \n"), stdout);
			break;
		}
	}
	
	return 0;
}

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdProcessing(void) {
	_fputts(_T("Best command prompt>> "), stdout);
	_getts(cmdString);
	
	TCHAR* token = _tcstok(cmdString, seps);
	int tokenNum = 0;
	
	while(token != NULL) {
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}
	
	if(!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	// else if(!_tcscmp(cmdTokenList[0], _T("추가 되는 명령어 1"))) {
	else if(!_tcscmp(cmdTokenList[0], _T("Command to add 1"))) {
		
	}
	else if(!_tcscmp(cmdTokenList[0], _T("Command to add 2"))) {
	}
	else {
		STARTUPINFO si = {0,};
		PROCESS_INFORMATION pi;
		si.cb = sizeof(si);
		BOOL isRun = CreateProcess(
			NULL, cmdTokenList[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi
		);
		
		if(isRun == FALSE)
			_tprintf(ERROR_CMD, cmdTokenList[0]);
	}
	
	return 0;
}

TCHAR* StrLower(TCHAR* pStr) {
	TCHAR *ret = pStr;
	
	while(*pStr) {
		if(_istupper(*pStr))
			*pStr = _totlower(*pStr);
		pStr++;
	}
	
	return ret;
}

