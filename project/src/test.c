#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h> 
#include "test.h"

static int comm_ComOpen(HANDLE *pHndl);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow)
{
//    MessageBox(NULL, "Hello world.", "message", MB_OK);

	HANDLE	handleComm;
	/* Open */
	int ret = comm_ComOpen(&handleComm);
	if(0 != ret){
        printf("fail COM open\n");
		return ret;
	}

    printf("succeed COM open\n");

	return 0;   /* 正常終了 */
}


static int comm_ComOpen(HANDLE *pHndl)
{
	HANDLE hndlComm = CreateFile(_T("\\\\.\\COM6"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if(hndlComm == INVALID_HANDLE_VALUE ) {		/* (-1) */
		*pHndl = NULL;
		return (-1);	/* err */
	}

	DCB dcb;
	GetCommState(hndlComm, &dcb);
	dcb.BaudRate		 = 9600;
	dcb.ByteSize		 = 8;
	dcb.Parity			 = NOPARITY;
	dcb.StopBits		 = ONESTOPBIT;
	SetCommState(hndlComm, &dcb);

	*pHndl = hndlComm;

	return (0);
}
