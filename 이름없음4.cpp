#include <iostream>
#include <locale>

int main()
{
    std::wcout.imbue( std::locale("kor") ); // locale ����.
    std::wcout << L'\xBDC1';

    return 0;
}

