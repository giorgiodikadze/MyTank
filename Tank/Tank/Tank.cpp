// Tank.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Tank.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
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

	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TANK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TANK));

	// 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
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
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   //获取屏幕宽和高
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

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	hWindow = hWnd;

	switch (message)
	{
	//窗口是否激活
	case WM_ACTIVATE://测试时不断循环是因为用的对话框测试，对话框能让窗口失去焦点，对话框消失后窗口又会收到WM_ACTIVATE
		if(wParam!=WA_INACTIVE)
		{
			SetTimer(hWnd,TIMER_ID,TIMER_INTERVAL,TimerProc);
		}
		else
			KillTimer(hWnd,TIMER_ID);
		break;
	//窗口最小化和还原
	case WM_SIZE:
		if(wParam==SIZE_RESTORED)
			SetTimer(hWnd,TIMER_ID,TIMER_INTERVAL,TimerProc);
		else if(wParam==SIZE_MINIMIZED)
			KillTimer(hWnd,TIMER_ID);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
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
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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
	case GS_BEGIN:
		InitializeProgram();
		game_state = GS_LOADING;
		break;
	case GS_LOADING:
		InitializeMap(++game_level);
		if(game_level == GAME_LEVEL_ALL) game_level = 0;
		DrawGame();
		game_state = GS_RUNNING;
		break;
	case GS_RUNNING:

		if(player_death==false) Keydown();

		DrawGame();
		
		//玩家死亡
		if(player_death==true)
		{
			if(--player_life>=0)
			{
				//玩家复活
				player_death=false;
				//player_tank=GTank(8,8,11,UP);
			}
			else game_state = GS_GAMEOVER;
		}
		break;
	case GS_GAMEOVER:
		game_state = GS_BEGIN;
		break;
	default:
		break;
	}
}

//初始化程序，在程序刚开始或者从头再来
void InitializeProgram()
{
	GetClientRect(hWindow,&clientRect);
	player_death = true;
	player_life = 3;
	game_level = 0;
	game_state = GS_LOADING;
}

//加载某一关地图
void InitializeMap(short level)
{
	TCHAR mapName[30];
	wsprintf(mapName,_T(".\\res\\map\\L%d.map"), level);
	ifstream in;
	in.open(mapName);
	for(short y=0, type=0;y<GAME_WINDOW_BLOCK;y++)//根据坐标，y应在循环外层
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

void DrawGame()
{
	screen = GetDC(NULL);
	cachehDC = CreateCompatibleDC(screen);

	DrawBackground();
	DrawMapExceptTree();

	DrawAndDealBullet();
	if(player_death==false)
	{
		player_tank.Draw(cachehDC);
	}



	DrawMapTree();

	Print();

	DeleteDC(cachehDC);
	ReleaseDC(NULL, screen);
}

void DrawBackground()
{
	CImage backgroundImage;
	backgroundImage.Load(_T(".\\res\\image\\background.png"));
	HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	SelectObject(cachehDC,hBitmap);
	backgroundImage.Draw(cachehDC,0,0,clientRect.Width(),clientRect.Height());
	DeleteObject(hBitmap);
}

void DrawMapExceptTree()
{
	for(short y=0;y<GAME_WINDOW_BLOCK;y++)
	{
		for(short x=0;x<GAME_WINDOW_BLOCK;x++)
		{
			if(map[x][y] != NULL && map[x][y]->type != 1)
			{
				if(map[x][y]->type == 3 && map[x][y]->state == 0)
				{
					delete map[x][y];
					map[x][y] = NULL;
					continue;
				}
				map[x][y]->Draw(cachehDC);
			}
		}
	}
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
	HDC hdc = GetDC(hWindow);
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
		if(player_tank.bullet_real_num < player_tank.BULLET_NUM)
		{
			int bullet_x=player_tank.real_x+(GAME_BLOCK_WIDTH- Bullet::BULLET_WIDTH)/2;
			int bullet_y=player_tank.real_y+(GAME_BLOCK_WIDTH- Bullet::BULLET_WIDTH)/2;
			switch(player_tank.direction)
			{
				case DOWN:
					bullet_y+=GAME_BLOCK_WIDTH/2;
					break;
				case LEFT:
					bullet_x-=GAME_BLOCK_WIDTH/2;
					break;
				case UP:
					bullet_y-=GAME_BLOCK_WIDTH/2;
					break;
				case RIGHT:
					bullet_x+=GAME_BLOCK_WIDTH/2;

			}
			player_bullet.push_back(new Bullet(bullet_x, bullet_y,player_tank.direction));
			player_tank.bullet_real_num++;
			//MessageBox(NULL,_T(""),_T(""),MB_OK);
		}
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

void DrawAndDealBullet()
{
	for(list<Bullet*>::iterator iter_bullet=player_bullet.begin(); iter_bullet!=player_bullet.end(); )
	{
		Bullet& bullet=**iter_bullet;
		if(bullet.hitAll() != true)
		{
			bullet.Move();
			(*(iter_bullet++))->Draw(cachehDC);
		}
		else
		{
			iter_bullet=player_bullet.erase(iter_bullet);
			player_tank.bullet_real_num--;
		}
	}
}