#include <iostream>
#include <locale>

int main()
{
    std::wcout.imbue( std::locale("kor") ); // locale ¼³Á¤.
    std::wcout << L'\xBDC1';

    return 0;
}

