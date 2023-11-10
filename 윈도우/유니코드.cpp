#include <stdio.h>
/*
	wscanf
	wprintf swprintf
*/
#include <string.h>
/*
	wcslen
	wcscpy wcsncpy 
	wcscat wcsncat
	wcscmp wcsncmp
*/
#include <iostream>

using std::string;
using std::wstring;
using std::cout;
using std::wcout;
using std::endl;

int main() {
	string s("ABC");
	wstring ws(L"hmmm...");
	wchar_t str[100]; swprintf(str, L"%S", "æ»≥Á«œººø‰!!");
	wprintf(L"%s\n", str);
	
	cout << s << endl;
	wcout << ws << endl;
}

