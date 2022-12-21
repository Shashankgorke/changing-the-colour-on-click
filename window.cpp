//header files
#include<windows.h>
#include"window.h"
//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations


//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdshow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	//CODE
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));


	//registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//creating the window
	hwnd=CreateWindow(
		szAppName,
		TEXT("SRG:Window"),
		WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//SHOW THE WINDOW
	ShowWindow(hwnd, iCmdshow);

	//update window

	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hbrush;
	static INT iPaintFlag = 0;
	

	//code

	switch (imsg)
	{
	case WM_LBUTTONDOWN:
		iPaintFlag++;
		if (iPaintFlag > 8)
			iPaintFlag = 0;//reset

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		if (iPaintFlag == 1)
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
		else if(iPaintFlag == 2)
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
		else if(iPaintFlag == 3)
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
		else if(iPaintFlag == 4)
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
		else if(iPaintFlag == 5)
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
		else if(iPaintFlag == 6)
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
		else if(iPaintFlag == 7)
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
		else if(iPaintFlag == 8)
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
		else
			hbrush = CreateSolidBrush(RGB(128, 128, 128));
		
		FillRect(hdc, &rc, hbrush);
		
		DeleteObject(hbrush);
		
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, imsg, wParam, lParam));

 }

