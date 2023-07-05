#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,LPSTR lpszCmdLine, int nCmdShow)
{
    MessageBox(NULL, "Hello world.", "message", MB_OK);
	return 0;
}
