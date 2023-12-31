#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>    /* _T */
#include <conio.h>    /* _kbhit  _getch */
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
    printf("\n-----------------------------------------------\n");

    int flg = 0;
    while(0==flg){
        while(1){
            char rdC;
            DWORD drSize = 0;
            BOOL res = ReadFile(handleComm,&rdC,1,&drSize,NULL);
            if( (TRUE == res)&&(1 == drSize) ){
                putchar(rdC);
            }else{
                break;
            }
        }

        DWORD dwSize;
        char wrC;
        if(0 != _kbhit()){
            wrC = _getch();
            if('!' == wrC){
                flg = 1;
            }else
            if(EOF != wrC){
                WriteFile(handleComm,&wrC,1,&dwSize,NULL);
            }else{}
        }
    }
    CloseHandle(handleComm);
    printf("\n-----------------------------------------------\n");

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
	timeout.WriteTotalTimeoutConstant	= 100;         	    /* 書き込みエラー検出用のタイムアウト時間		*/

/*	timeout.ReadIntervalTimeout			= 100;	*/	/* 文字読込時の２も時間の全体待ち時間（msec）	*/
/*	timeout.ReadTotalTimeoutMultiplier	= 5;	*/	/* 読込の１文字あたりの時間(for Win9x)			*/
/*	timeout.ReadTotalTimeoutConstant	= 5;	*/	/* 読込エラー検出用のタイムアウト時間			*/
/*	timeout.WriteTotalTimeoutMultiplier = 10;	*/	/* 書き込み１文字あたりの待ち時間(for Win9x)	*/
/*	timeout.WriteTotalTimeoutConstant	= 100;	*/	/* 書き込みエラー検出用のタイムアウト時間		*/
	SetCommTimeouts(hndlComm, &timeout);

	*pHndl = hndlComm;

	return (0);
}
