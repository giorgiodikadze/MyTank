/*
#	Copyright © 2013 Shaw 499012219@qq.com
#   This file is part of Tank.

#    Tank is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    Tank is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

// Tank.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Tank.h"
#include <list>
using namespace std;

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


//==================================


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//检查内存泄露的代码
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

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
   
	//获取DC==================================
	//screen = GetDC(NULL);
	//cachehDC = CreateCompatibleDC(screen);
	//HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	//SelectObject(cachehDC,hBitmap);
	//DeleteObject(hBitmap);

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
	PAINTSTRUCT ps;
	HDC hdc;

	//在这里干一些事情========================
	hWindow = hWnd;
	srand((unsigned)time(NULL));

	//鼠标单击事件大集合
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
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWindow,WM_DESTROY,NULL,NULL);
			break;
		case 88:
			for(list<GTank*>::iterator iter_etank = enemy_tank.begin(); iter_etank!=enemy_tank.end() ; )
			{
				GTank& etank = **iter_etank;
				delete *iter_etank;
				iter_etank = enemy_tank.erase(iter_etank);
				if(etank.type == 21) score++;
				else if(etank.type == 22) score += 2;
				else score += 3;
				enemy_num_now--;
			}
			break;
		}
		break;
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
	for(list<Bullet*>::iterator iter_bullet = player_tank.player_bullet.begin(); iter_bullet!=player_tank.player_bullet.end();)
	{
		delete *iter_bullet;
		iter_bullet = player_tank.player_bullet.erase(iter_bullet); 
		player_tank.bullet_real_num--;
	}
	
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
		enemy_rest = game_level*5;
		if(game_level == GAME_LEVEL_ALL) game_level = 0;
		enemy_num_now =0;
		come_time = 1;
		game_state = GS_RUNNING;
		break;
	case GS_RUNNING:
		//=====================================
		//game_state = GS_WIN;//测试代码,直接过关
		//=====================================
		if(player_death==false) Keydown();

		DrawGame();
		
		//玩家死亡
		if(player_death==true)
		{
			if(--player_life>=0)
			{
				//玩家复活
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
		loadAnImageToCache(cachehDC,_T(".\\res\\image\\fail.png"), 0, 0);
		loadIntToCache(168, 259, score);
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
		loadAnImageToCache(cachehDC,_T(".\\res\\image\\pass.png"), 0, 0);
		loadIntToCache(56, 212, score);
		if(mouse_x > 406 && mouse_x < 592 && mouse_y > 406 && mouse_y < 448)
		{
			loadAnImageToCache(cachehDC,_T(".\\res\\image\\nextlevel.png"), 406, 406);
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

//进入前的准备
void Prepare()
{
	GetClientRect(hWindow,&clientRect);
	HBITMAP hBitmap = CreateCompatibleBitmap(screen,clientRect.Width(),clientRect.Height());
	HFONT myFont = CreateFont(50,30,0,0,FW_THIN, false, false, false, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,
						 CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN,_T("Brush Script MT"));
	SelectObject(cachehDC,hBitmap);
	SelectObject(cachehDC, myFont);
	DeleteObject(hBitmap);
	DeleteObject(myFont);
}

//初始化程序，游戏开始
void InitializeProgram()
{
	score = 0;
	player_death = true;
	player_life = 3;
	game_level = 0;
	game_state = GS_LOADING;
}

//加载某一关地图
void InitializeMap(short level)
{
	int a=level;
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
	HDC hdc = GetDC(hWindow); //hWindow是我定义的客户区的句柄
	SetTextColor(cachehDC, RGB(255,0,0)) ; 
	SetBkMode(cachehDC, TRANSPARENT); //透明背景 
	BitBlt(hdc,0,0,clientRect.Width(),clientRect.Height(),cachehDC,0,0,SRCCOPY);
	ReleaseDC(hWindow,hdc);
}

void Keydown()
{
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
	//少于屏幕最大敌人数并且剩余敌人数大于零添加敌人
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

void DrawEnemy()//没有RTE
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

void loadIntToCache(int x, int y, int score)
{
	TCHAR score_str[10];
	wsprintf(score_str,_T("%d00"),score);
	TextOut(cachehDC, x, y, score_str, _tcslen(score_str));
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