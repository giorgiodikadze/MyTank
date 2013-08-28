// Tank.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Tank.h"
#include <list>
using namespace std;

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


//==================================


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//����ڴ�й¶�Ĵ���
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

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
	int window_width = GAME_BLOCK_WIDTH * GAME_WINDOW_BLOCK+16;
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
   
	//��ȡDC==================================
	//screen = GetDC(NULL);
	//cachehDC = CreateCompatibleDC(screen);
	//HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	//SelectObject(cachehDC,hBitmap);
	//DeleteObject(hBitmap);

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
	HDC hdc;

	//�������һЩ����========================
	hWindow = hWnd;
	srand((unsigned)time(NULL));

	//��굥���¼��󼯺�
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			int mouse_x=LOWORD(lParam);
			int mouse_y=HIWORD(lParam);
			switch(game_state)
			{
			case GS_PREFACE:
				if (mouse_x > 60 && mouse_x < 269 && mouse_y > 296 && mouse_y < 346)
				{
					PlaySound(_T(".\\res\\wav\\bang.wav"),NULL,SND_FILENAME | SND_ASYNC);
					game_state = GS_BEGIN;
				}
				break;
			case GS_GAMEOVER:
				if (mouse_x > 24 && mouse_x < 210 && mouse_y > 447 && mouse_y < 489)
				{
					PlaySound(_T(".\\res\\wav\\bang.wav"),NULL,SND_FILENAME | SND_ASYNC);
					game_state = GS_PREPARE;
				}
				if(mouse_x > 454 && mouse_x < 581 && mouse_y > 447 && mouse_y < 489)
				{
					PlaySound(_T(".\\res\\wav\\bang.wav"),NULL,SND_FILENAME | SND_ASYNC);
					game_state = GS_BEGIN;
				}
				break;
			case GS_WIN:
				if (mouse_x > 406 && mouse_x < 592 && mouse_y > 419 && mouse_y < 448)
				{
					PlaySound(_T(".\\res\\wav\\bang.wav"),NULL,SND_FILENAME | SND_ASYNC);
					game_state = GS_LOADING;
				}
				if (mouse_x > 406 && mouse_x < 592 && mouse_y > 448 && mouse_y < 490)
				{
					PlaySound(_T(".\\res\\wav\\bang.wav"),NULL,SND_FILENAME | SND_ASYNC);
					game_state = GS_PREPARE;
				}
				break;
			}
		}
	//�����Ƿ񼤻�
	case WM_ACTIVATE://����ʱ����ѭ������Ϊ�õĶԻ�����ԣ��Ի������ô���ʧȥ���㣬�Ի�����ʧ�󴰿��ֻ��յ�WM_ACTIVATE
		if(wParam!=WA_INACTIVE)
		{
			SetTimer(hWnd,TIMER_ID,TIMER_INTERVAL,TimerProc);
		}
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
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd,TIMER_ID);
		lastClean();
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		mouse_x=LOWORD(lParam);
		mouse_y=HIWORD(lParam);
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

void lastClean()
{
	for(list<GTank*>::iterator iter_etank = enemy_tank.begin(); iter_etank!=enemy_tank.end() ; )
	{
		delete *iter_etank;
		iter_etank = enemy_tank.erase(iter_etank); 
	}
	for(short y=0;y<GAME_WINDOW_BLOCK;y++)
	{
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			delete map[x][y];
			map[x][y] = NULL;
		}
	}
}

void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	switch (game_state)
	{
	case GS_PREFACE:
		{
			loadAnImageToCache(cachehDC,_T(".\\res\\image\\preface.png"), 0, 100);
			if(mouse_x > 60 && mouse_x < 269 && mouse_y > 296 && mouse_y < 346)
			{
				loadAnImageToCache(cachehDC,_T(".\\res\\image\\fire.png"), 60 , 296);
			}
			if(mouse_x > 106 && mouse_x < 532 && mouse_y > 346 && mouse_y < 403)
			{
				loadAnImageToCache(cachehDC,_T(".\\res\\image\\direction.png"), 106 , 346); 
				loadAnImageToCache(cachehDC,_T(".\\res\\image\\control.png"), 136 , 404);
			}
			Print();
			//game_state = GS_BEGIN;
			break;
		}
	case GS_BEGIN:
		lastClean();
		InitializeProgram();
		game_state = GS_LOADING;
		break;
	case GS_LOADING:
		lastClean();
		player_tank.Reset(5, 14, UP);
		InitializeMap(++game_level);
		if(game_level == GAME_LEVEL_ALL) game_level = 0;
		enemy_num_now =0;
		come_time = 1;
		enemy_rest = ENEMY_MAX;
		game_state = GS_RUNNING;
		break;
	case GS_RUNNING:

		//=====================================
		//game_state = GS_WIN;//���Դ���
		//=====================================
		if(player_death==false) Keydown();

		DrawGame();
		
		//�������
		if(player_death==true)
		{
			if(--player_life>=0)
			{
				//��Ҹ���
				player_death=false;
				player_tank.Reset(5, 14, UP);
			}
			else game_state = GS_GAMEOVER;
		}
		if(map[7][14]->state == 0) game_state = GS_GAMEOVER;
		if(enemy_rest == 0 && enemy_num_now ==0) game_state = GS_WIN;
		break;
	case GS_GAMEOVER:
		lastClean();
		loadAnImageToCache(cachehDC,_T(".\\res\\image\\fail.png"), 0, 100);
		if(mouse_x > 24 && mouse_x < 210 && mouse_y > 447 && mouse_y < 489)
		{
			loadAnImageToCache(cachehDC,_T(".\\res\\image\\fail_homepage.png"), 24, 447);
		}
		if(mouse_x > 454 && mouse_x < 581 && mouse_y > 447 && mouse_y < 489)
		{
			loadAnImageToCache(cachehDC,_T(".\\res\\image\\tryagain.png"), 454, 447);
		}
		Print();
		break;
	case GS_WIN:
		lastClean();
		loadAnImageToCache(cachehDC,_T(".\\res\\image\\pass.png"), 0, 100);
		if(mouse_x > 406 && mouse_x < 592 && mouse_y > 419 && mouse_y < 448)
		{
			loadAnImageToCache(cachehDC,_T(".\\res\\image\\nextlevel.png"), 406, 419);
		}
		if(mouse_x > 406 && mouse_x < 592 && mouse_y > 448 && mouse_y < 490)
		{
			loadAnImageToCache(cachehDC,_T(".\\res\\image\\homepage.png"), 406, 448);
		}
		Print();
		//game_state = GS_LOADING;
		break;
	case GS_PREPARE:
		Prepare();
		game_state = GS_PREFACE;
		break;
	default:
		break;
	}
}

//����ǰ��׼��
void Prepare()
{
	GetClientRect(hWindow,&clientRect);
	HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	SelectObject(cachehDC,hBitmap);
	DeleteObject(hBitmap);
}

//��ʼ��������Ϸ��ʼ
void InitializeProgram()
{
	score = 0;
	player_death = true;
	player_life = 3;
	game_level = 0;
	game_state = GS_LOADING;
}

//����ĳһ�ص�ͼ
void InitializeMap(short level)
{
	TCHAR mapName[30];
	wsprintf(mapName,_T(".\\res\\map\\L%d.map"), level);
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

void DrawBackground()
{
	CImage backgroundImage;
	backgroundImage.Load(_T(".\\res\\image\\background.png"));
	//HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	//SelectObject(cachehDC,hBitmap);
	backgroundImage.Draw(cachehDC,0,0,clientRect.Width(),clientRect.Height());
	//DeleteObject(hBitmap);
}

void DrawMapExceptTree()
{
	//OutputDebugString(_T("Yѭ��\n"));
	for(short y=0;y<GAME_WINDOW_BLOCK;y++)
	{
		//OutputDebugString(_T("Xѭ��\n"));
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			//OutputDebugString(_T("��һ���ж�\n"));
			if(map[x][y] != NULL && map[x][y]->type != 1)
			{
				//OutputDebugString(_T("�ڶ����ж�\n"));
				if(map[x][y]->type == 3 && map[x][y]->state == 0)
				{
					//OutputDebugString(_T("delete\n"));
					delete map[x][y];
					//OutputDebugString(_T("NULL\n"));
					map[x][y] = NULL;
					//OutputDebugString(_T("continue\n"));
					continue;
				}
				//OutputDebugString(_T("������\n"));
				map[x][y]->Draw(cachehDC);
				//OutputDebugString(_T("�ڶ����жϽ���\n"));
			}
			//OutputDebugString(_T("��һ���жϽ���\n"));
		}
		//OutputDebugString(_T("Xѭ������\n"));
	}
	//OutputDebugString(_T("Yѭ�����������̽���\n"));
}

void DrawMapTree()
{
	for(short y=0;y<GAME_WINDOW_BLOCK;y++)
	{
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			if(map[x][y] != NULL && map[x][y]->type == 1)
			{
				map[x][y]->Draw(cachehDC);
			}
		}
	}
}

void Print()
{
	HDC hdc = GetDC(hWindow); //hWindow���Ҷ���Ŀͻ����ľ��
	BitBlt(hdc,0,0,clientRect.Width(),clientRect.Height(),cachehDC,0,0,SRCCOPY);
	ReleaseDC(hWindow,hdc);
}

void Keydown()
{
	if(KEYDOWN(VK_ESCAPE))
	{
		SendMessage(hWindow,WM_DESTROY,NULL,NULL);
	}
	if(KEYDOWN(VK_SPACE))
	{
		player_tank.Fire();
	}

	if(KEYDOWN(VK_DOWN))
	{
		player_tank.Move(DOWN);
	}
	else if(KEYDOWN(VK_LEFT))
	{
		player_tank.Move(LEFT);
	}
	else if(KEYDOWN(VK_UP))
	{
		player_tank.Move(UP);
	}
	else if(KEYDOWN(VK_RIGHT))
	{
		player_tank.Move(RIGHT);
	}
}

void EnemyCome()
{
	static short x = -1;
	if(enemy_num_now<ENEMY_MAX_MOMENT && come_time==0 && enemy_rest>0)
	{
		come_time=COME_TIME_INTERVAL;
	}
	//������Ļ������������ʣ���������������ӵ���
	if(come_time>0)		
	{
		come_time--;
		if(come_time == 0)
		{
			if(enemy_num_now < ENEMY_MAX_MOMENT && come_time == 0 && enemy_rest > 0)
			{
				enemy_num_now++;
				enemy_rest--;
				int r=rand()%8;
				if(r == 0) enemy_tank.push_back(new GTank(++x%3*7, 0, 23, DOWN, 3));
				else if(r == 1 || r==2) enemy_tank.push_back(new GTank(++x%3*7, 0, 22, DOWN, 3));
				else enemy_tank.push_back(new GTank(++x%3*7, 0, 21, DOWN, 2));

			}
		}
	}
}

void EnemyBehave()
{
	list<GTank*>::iterator iter_tank;
	for(iter_tank=enemy_tank.begin(); iter_tank!=enemy_tank.end(); iter_tank++)
	{
		GTank& etank = **iter_tank;
		short direction = etank.direction;
		if(rand()%25 == 0)
		{
			etank.Fire();
		}
		if(direction == DOWN && etank.y == 14 || direction == LEFT  && etank.x == 0  
			|| direction == UP && etank.y == 0 || direction == RIGHT && etank.x == 14 || rand()%20 ==0 )
		{
			etank.Move(rand()%4);
		}
		etank.Move();
	}
}

void DrawEnemy()//û��RTE
{
	list<GTank*>::iterator iter_tank;
	for(iter_tank=enemy_tank.begin(); iter_tank!=enemy_tank.end(); iter_tank++)
	{
		GTank& etank = **iter_tank;
		etank.Draw(cachehDC);
	}
}

void DrawAllBullet(HDC &hDC)
{
	player_tank.DrawAndDealBullet(hDC);
 	list<GTank*>::iterator iter_tank;
	for(iter_tank=enemy_tank.begin(); iter_tank!=enemy_tank.end(); iter_tank++)
	{
		GTank& etank = **iter_tank;
		etank.DrawAndDealBullet(hDC);
	}
}

void loadAnImageToCache(HDC &hDC, LPCWSTR path, int _real_x, int _real_y)
{
	CImage image;
	image.Load(path);
	Block::TransparentPNG(&image);
	image.Draw(hDC, _real_x, _real_y);
}

void DrawGame()
{
	//screen = GetDC(NULL);
	//cachehDC = CreateCompatibleDC(screen);

	DrawBackground();
	DrawMapExceptTree();
	if(player_death==false)
	{
		player_tank.Draw(cachehDC);
	}
	EnemyCome();
	EnemyBehave();
	DrawAllBullet(cachehDC);
	DrawEnemy();
	DrawMapTree();

	Print();

	//DeleteDC(cachehDC);
	//ReleaseDC(NULL, screen);

}