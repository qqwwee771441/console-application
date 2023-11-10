#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	for(int i=0; i<argc; i++) {
		printf("Child Process : %s \n", argv[i]);
	}
	Sleep(1000);
	
	return 0;
}

