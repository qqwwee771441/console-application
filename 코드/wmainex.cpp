#define UNICODE
#define _UNICODE

#include <stdio.h>   // wprintf wscanf fputws fgetws
#include <string.h>  // wcslen wcscpy wcsncpy wcscat wcsncat wcscmp wcsncmp
#include <locale.h>  // _wsetlocale(LC_ALL, L"korean");
#include <windows.h> // windows.h -> windef.h -> winnt.h
/*
 * CONST
 * CHAR WCHAR LPSTR LPCSTP LPWSTR LPCWSTP
 */
#include <tchar.h>   // TCHAR LPTSTR LPCTSTR _T("") _TEXT("") __T("")

int wmain(int argc, wchar_t* argv[]) {
	TCHAR str[] = _T("1234567");
	int size = sizeof(str);
	printf("%d\n", size);

	return 0;
}
