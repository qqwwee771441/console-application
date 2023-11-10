#define UNICODE
#define _UNICODE
// WIN64
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#define BUF_SIZE 1024

int CommToClient(HANDLE);

/******************** Main ********************/
int wmain(int argc, wchar_t* argv[]);
int main() { _tmain(0, NULL); return 0; }
int _tmain(int argc, TCHAR* argv[]) {
	_fputts(_T("Named Pipe Server Main\n"), stdout);
	
	/******************** TODO ********************/
	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;
	while(true) {
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUF_SIZE,
			BUF_SIZE,
			20000,
			NULL
		);
		if(hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(_T("Create Pipe Failed\n"));
			return -1;
		}
		
		if(ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError()==ERROR_PIPE_CONNECTED)) {
			CommToClient(hPipe);
		} else {
			CloseHandle(hPipe);
		}
	}
	
	return 1;
}

/******************** Comm To Client ********************/
int CommToClient(HANDLE hPipe) {
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];
	
	/******************** Read Pipe ********************/
	DWORD fileNameSize;
	BOOL isSuccess = ReadFile(
		hPipe,
		fileName,
		MAX_PATH*sizeof(TCHAR),
		&fileNameSize,
		NULL
	);
	if(!isSuccess || fileNameSize==0) {
		_tprintf(_T("Pipe Read Failed\n"));
		return -1;
	}
	
	/******************** File ********************/
	FILE* file = _tfopen(fileName, _T("r"));
	if(file == NULL) {
		_tprintf(_T("File Open Failed\n"));
		return -1;
	}
	
	/******************** TODO ********************/
	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;
	
	while(!feof(file)) {
		bytesRead = fread(dataBuf, 1, BUF_SIZE, file);
		
		WriteFile(
			hPipe,
			dataBuf,
			bytesRead,
			&bytesWritten,
			NULL
		);
		
		if(bytesRead != bytesWritten) {
			_tprintf(_T("Write Pipe Failed\n"));
			break;
		}
	}
	
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	
	return 1;
}

