// ´å³Ý MSDN
#define UNICODE
#define _UNICODE
// #define _WIN64
// stdafx.h -> stdio.h, tchar.h
// exit
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
 * HANDLE
 * HANDLE CreateFile(~);
 * CreateProcess(~); 
 * GetCurrentDirectory(~); SetCurrentDirectory(~); GetSystemDirectory(~); GetWindowsDirectory(~);
 * GetCurrentProcess(); GetLastError();
 * SetPriorityClass(~);
 * WaitForSingleObject(~);
 * GetExitCodeProcess(~);
 * CloseHandle(~);
 * ZeroMemory(~); Sleep
 * OpenProcess TerminateProcess
 * GetStdHandle(~)
 */
// #include <tlhelp32.h> // CreateToolhelp32Snapshot Process32First Process32Next
#include <tchar.h>   // TCHAR LPTSTR LPCTSTR _T("") _TEXT("") __T("")
/*
 * _tmain
 * _tprintf _tscanf _tputts _tgetts
 * _tcslen _tcscpy _tcsncpy _tcscat _tcsncat _tcscmp _tcsncmp
 * _tsetlocale(LC_ALL, _T("Korean"));
 * _tcstok _ttoi _gettchar
 */
#include <stdlib.h>

int wmain(int argc, wchar_t* argv[]);
int main(int argc, char* argv[]) { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {	
	/******************** TODO ********************/
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	if(!CreateProcess(
		_T("childprocess.exe"),
		_T("10 20"),
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
	)) {
		_tprintf(_T("CreateProcess failed : %d \n"), GetLastError());
		return 1;
	}
	
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
	SetPriorityClass(pi.hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	DWORD exitcode;
	if(!GetExitCodeProcess(pi.hProcess, &exitcode)) {
		_tprintf(_T("GetExitCodeProcess failed : %d \n"), GetLastError());
	} else {
		_tprintf(_T("ExitCode : %d \n"), exitcode);
	}
	
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	return 0;
}

