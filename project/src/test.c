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
    DWORD dwSize;
    char wrData[16] = {0};
    wrData[0] = 0x1b; /* ESC */
     WriteFile(handleComm,&wrData[0],1,&dwSize,NULL);
    Sleep(10);
    printf("esc write\n");

    char rdData[4096] = {0};
    int rdLen = 0;
    int flg = 0;
    while(0==flg){
        char rdC;
        DWORD drSize = 0;
        BOOL res = ReadFile(handleComm,&rdC,1,&drSize,NULL);
        if( (TRUE == res)&&(1 == drSize) ){
            rdData[rdLen] = rdC;
            rdLen++;
        }else{
            flg = 1;
        }
    }

    printf("read\n");
    printf(rdData);

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

	COMMTIMEOUTS timeout;									/* COMMTIMEOUTS構造体の変数を宣言				*/
	timeout.ReadIntervalTimeout			= MAXDWORD;			/* 文字読込時の２も時間の全体待ち時間（msec）	*/
	timeout.ReadTotalTimeoutMultiplier	= 0;				/* 読込の１文字あたりの時間(for Win9x)			*/
	timeout.ReadTotalTimeoutConstant	= 0;				/* 読込エラー検出用のタイムアウト時間			*/
	timeout.WriteTotalTimeoutMultiplier = 0;				/* 書き込み１文字あたりの待ち時間(for Win9x)	*/
	timeout.WriteTotalTimeoutConstant	= 1000;         	/* 書き込みエラー検出用のタイムアウト時間		*/

/*	timeout.ReadIntervalTimeout			= 100;	*/	/* 文字読込時の２も時間の全体待ち時間（msec）	*/
/*	timeout.ReadTotalTimeoutMultiplier	= 5;	*/	/* 読込の１文字あたりの時間(for Win9x)			*/
/*	timeout.ReadTotalTimeoutConstant	= 5;	*/	/* 読込エラー検出用のタイムアウト時間			*/
/*	timeout.WriteTotalTimeoutMultiplier = 10;	*/	/* 書き込み１文字あたりの待ち時間(for Win9x)	*/
/*	timeout.WriteTotalTimeoutConstant	= 100;	*/	/* 書き込みエラー検出用のタイムアウト時間		*/
	SetCommTimeouts(hndlComm, &timeout);

	*pHndl = hndlComm;

	return (0);
}
