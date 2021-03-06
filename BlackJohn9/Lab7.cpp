#include "stdafx.h"
#include "LR7.h"
#include <Windows.h>
#include <windowsx.h>
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100
#define IDM_HOUSERBUTTON 1001
#define IDM_CLEARBUTTON 1004

// Global variables:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];                  // header text
WCHAR szWindowClass[MAX_LOADSTRING];            // name of the class

vector<pair<int, pair<int, int>>> points;
int drawFlag = 1;

// Send the definition of the functions included in the given module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Global strings initialization
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LR7, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Initialize the app:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR7));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

// Register window class
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;	// shows how message should be processed
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR7));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LR7);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

// Saves the marker and creates the main window
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	HWND hClearButton = CreateWindow(_T("BUTTON"), _T("CLEAR"), WS_CHILD | WS_VISIBLE, 1390, 720, 130, 50, hWnd, (HMENU)IDM_CLEARBUTTON, hInst, 0);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	return TRUE;
}


//  Process messages in the main window
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND: // processes app menu
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_CLEARBUTTON:
			points.clear();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: // draws the main window
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HPEN hBlackPen, hYellowPen, hOrangePen;
		hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hYellowPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		hOrangePen = CreatePen(PS_SOLID, 1, RGB(255, 200, 0));
		HBRUSH hBlackBrush, hYellowBrush, hOrangeBrush;
		hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
		hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
		hOrangeBrush = CreateSolidBrush(RGB(255, 200, 0));

		for (int i = 0; i < points.size(); i++)
		{
			int x = points[i].second.first - 75;
			int y = points[i].second.second - 80;

			SelectObject(hdc, hBlackBrush);
			SelectObject(hdc, hBlackPen);

			Rectangle(hdc, x + 90, y, x + 120, y + 10);
			Rectangle(hdc, x + 120, y + 10, x + 130, y + 20);
			Rectangle(hdc, x + 130, y + 20, x + 140, y + 40);
			Rectangle(hdc, x + 140, y + 40, x + 150, y + 50);
			Rectangle(hdc, x + 120, y + 50, x + 140, y + 60);
			Rectangle(hdc, x + 110, y + 60, x + 120, y + 80);
			Rectangle(hdc, x + 120, y + 80, x + 130, y + 90);
			Rectangle(hdc, x + 130, y + 90, x + 140, y + 120);
			Rectangle(hdc, x + 120, y + 120, x + 130, y + 140);
			Rectangle(hdc, x + 100, y + 140, x + 120, y + 150);
			Rectangle(hdc, x + 50, y + 150, x + 100, y + 160);
			Rectangle(hdc, x + 30, y + 140, x + 50, y + 150);
			Rectangle(hdc, x + 20, y + 120, x + 30, y + 140);
			Rectangle(hdc, x + 10, y + 100, x + 20, y + 120);
			Rectangle(hdc, x, y + 70, x + 10, y + 100);
			Rectangle(hdc, x + 10, y + 60, x + 20, y + 70);
			Rectangle(hdc, x + 20, y + 70, x + 30, y + 80);
			Rectangle(hdc, x + 30, y + 80, x + 70, y + 90);
			Rectangle(hdc, x + 70, y + 70, x + 90, y + 80);
			Rectangle(hdc, x + 90, y + 60, x + 100, y + 70);
			Rectangle(hdc, x + 80, y + 50, x + 90, y + 60);
			Rectangle(hdc, x + 70, y + 20, x + 80, y + 50);
			Rectangle(hdc, x + 80, y + 10, x + 90, y + 20);
			Rectangle(hdc, x + 80, y + 10, x + 90, y + 20);

			SelectObject(hdc, hYellowBrush);
			SelectObject(hdc, hYellowPen);

			Rectangle(hdc, x + 90, y + 10, x + 120, y + 60);
			Rectangle(hdc, x + 120, y + 20, x + 130, y + 50);
			Rectangle(hdc, x + 80, y + 20, x + 90, y + 50);

			Rectangle(hdc, x + 10, y + 70, x + 20, y + 100);
			Rectangle(hdc, x + 20, y + 80, x + 30, y + 120);
			Rectangle(hdc, x + 50, y + 140, x + 100, y + 150);
			Rectangle(hdc, x + 120, y + 90, x + 130, y + 120);
			Rectangle(hdc, x + 70, y + 80, x + 120, y + 90);
			Rectangle(hdc, x + 30, y + 90, x + 120, y + 140);
			Rectangle(hdc, x + 90, y + 70, x + 110, y + 80);
			Rectangle(hdc, x + 100, y + 60, x + 110, y + 70);

			SelectObject(hdc, hBlackBrush);
			SelectObject(hdc, hBlackPen);

			Rectangle(hdc, x + 110, y + 30, x + 120, y + 40);
			Rectangle(hdc, x + 90, y + 100, x + 100, y + 110);
			Rectangle(hdc, x + 40, y + 110, x + 50, y + 120);
			Rectangle(hdc, x + 80, y + 110, x + 90, y + 120);
			Rectangle(hdc, x + 50, y + 120, x + 80, y + 130);

			SelectObject(hdc, hOrangeBrush);
			SelectObject(hdc, hOrangePen);

			Rectangle(hdc, x + 120, y + 40, x + 140, y + 50);
		}

		DeleteObject(hBlackBrush);
		DeleteObject(hYellowBrush);
		DeleteObject(hOrangeBrush);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY: // sends exit message and return
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		if (drawFlag != 0)
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			points.push_back(pair<int, pair<int, int>>(drawFlag, pair<int, int>(xPos, yPos)));
			InvalidateRect(hWnd, 0, TRUE);
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for "About programm"
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
