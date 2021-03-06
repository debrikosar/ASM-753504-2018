// WindowsProject2.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

void Paint(HDC, int, int);                        //Функция рисования
int xCoordinates = 0, yCoordinates = 0;         //Пользовательские Переменные      
bool Mode = false;
char colorMode = '0';

// Отправить объявления функций, включенных в этот модуль кода:
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

	// TODO: разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;

	// Цикл основного сообщения:
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



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:                      //Создание кнопки очистки
	{
		hWnd = CreateWindowEx(NULL, L"BUTTON", L"Clear", WS_CHILD,
			       350, 10, 250, 50, hWnd, HMENU(100), hInst, NULL); //Дескриптор 100
		ShowWindow(hWnd, SW_SHOWNORMAL);

		break;
	}
	case WM_LBUTTONDOWN:                 //Нажатие на левую клавишу мыши 
	{
		Mode = true;
		xCoordinates = LOWORD(lParam);
		yCoordinates = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, false); //Перерисовать окно
		break;
	}
	case WM_RBUTTONDOWN:                 //Нажатие на правую клавишу мыши 
	{
		Mode = true;
		xCoordinates = LOWORD(lParam);
		yCoordinates = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, false);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case 100:                                //Обработка сообщения кнопки
		{
			Mode = false;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Paint(hdc, xCoordinates, yCoordinates);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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

void Paint(HDC hdc, int xCoordinates, int yCoordinates)
{
	if (Mode)
	{
		HPEN hBlackPen;
		hBlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		SelectObject(hdc, hBlackPen);                            //Выбираем нужно перо 
		HBRUSH hSmileBrush, hWhiteBrush, hBlackBrush;        
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
		switch (colorMode)
		{
		case '0':
			hSmileBrush = CreateSolidBrush(RGB(0, 255, 0));
			colorMode++;
			break;
		case '1':
			hSmileBrush = CreateSolidBrush(RGB(0, 0, 255));
			colorMode++;
			break;
		case '2':
			hSmileBrush = CreateSolidBrush(RGB(255, 0, 0));
			colorMode++;
			break;
		case '3':
			hSmileBrush = CreateSolidBrush(RGB(255, 215, 0));
			colorMode++;
			break;
		default:
			hSmileBrush = CreateSolidBrush(RGB(255, 255, 0));
			colorMode = '0';
			break;
		}
		SelectObject(hdc, hSmileBrush);
		Ellipse(hdc, xCoordinates - 75, yCoordinates - 75, xCoordinates + 75, yCoordinates + 75);
		SelectObject(hdc, hWhiteBrush);
		Ellipse(hdc, xCoordinates - 45, yCoordinates - 45, xCoordinates - 25, yCoordinates - 25);
		Ellipse(hdc, xCoordinates + 45, yCoordinates - 45, xCoordinates + 25, yCoordinates - 25);
		SelectObject(hdc, hBlackBrush);
		Ellipse(hdc, xCoordinates - 40, yCoordinates - 40, xCoordinates - 30, yCoordinates - 30);
		Ellipse(hdc, xCoordinates + 40, yCoordinates - 40, xCoordinates + 30, yCoordinates - 30);
		Arc(hdc,xCoordinates-35,yCoordinates-5,xCoordinates+35,yCoordinates+35,xCoordinates+35,yCoordinates+15,xCoordinates-35,yCoordinates+15);
	}
}