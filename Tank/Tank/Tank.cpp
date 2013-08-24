// Tank.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Tank.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TANK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TANK));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TANK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   //��ȡ��Ļ��͸�
	int device_width = GetSystemMetrics(SM_CXSCREEN);
	int	device_height =	GetSystemMetrics(SM_CYSCREEN);
	int window_width = GAME_BLOCK_WIDTH * GAME_WINDOW_BLOCK+6;
	int window_height = window_width + 22;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
	   (device_width - window_width)/2, (device_height - window_height)/2, window_width,
	   window_height, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;

	switch (message)
	{
	//�����Ƿ񼤻�
	case WM_ACTIVATE://����ʱ����ѭ������Ϊ�õĶԻ�����ԣ��Ի������ô���ʧȥ���㣬�Ի�����ʧ�󴰿��ֻ��յ�WM_ACTIVATE
		if(wParam!=WA_INACTIVE)
			SetTimer(hWnd,TIMER_ID,TIMER_INTERVAL,TimerProc);
		else
			KillTimer(hWnd,TIMER_ID);
		break;
	//������С���ͻ�ԭ
	case WM_SIZE:
		if(wParam==SIZE_RESTORED)
			SetTimer(hWnd,TIMER_ID,TIMER_INTERVAL,TimerProc);
		else if(wParam==SIZE_MINIMIZED)
			KillTimer(hWnd,TIMER_ID);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd,&clientRect);
		Paint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd,TIMER_ID);
		lastClean();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
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

void Paint(HDC hdc)
{
	HDC screen = GetDC(NULL);
	HDC cachehDC = CreateCompatibleDC(screen);
	HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	SelectObject(cachehDC,hBitmap);
	CImage backgroundImage;//��������load��ʱ��CImage���������null
	backgroundImage.Load(_T(".\\res\\image\\background.bmp"));
	backgroundImage.Draw(cachehDC,0,0,clientRect.Width(),clientRect.Height());
	for(short y=0;y<GAME_WINDOW_BLOCK;y++)
	{
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			if(map[x][y] != NULL)
				{
					map[x][y]->Draw(cachehDC);
				}
		}
	}
	BitBlt(hdc,0,0,clientRect.Width(),clientRect.Height(),cachehDC,0,0,SRCCOPY);
	DeleteObject(hBitmap);
	DeleteDC(cachehDC);
	ReleaseDC(NULL, screen);
}

void InitializeMap(short level)
{
	TCHAR mapName[25];
	wsprintf(mapName,_T(".\\res\\map\\L%d.map"),level);
	ifstream in;
	in.open(mapName);
	for(short y=0, type=0;y<GAME_WINDOW_BLOCK;y++)//�������꣬yӦ��ѭ�����
	{
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			in>>type;
			//TCHAR TEMP[3];
			//wsprintf(TEMP,_T("%d"),type);
			//MessageBox(NULL,TEMP,_T(""),MB_OK);
			if(type != 0)
			{
				map[x][y] = new MapBlock(x,y,type);
			}
			else map[x][y] = NULL;
			
		}
	}
	in.close();
}

void lastClean()
{
	for(short y=0;y<GAME_WINDOW_BLOCK;y++)
	{
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			delete map[x][y];
		}
	}
}

void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	switch (game_state)
	{
	case GS_WAITING:
		InitializeMap(++game_level);
		game_state = GS_RUNNING;
		RedrawWindow(hwnd,NULL,NULL,RDW_INVALIDATE);
		break;
	case GS_RUNNING:
		
	default:
		break;
	}
}
