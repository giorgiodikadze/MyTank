#pragma once

#include "resource.h"
#include <fstream>
#include "MapBlock.h"
#include "GTank.h"
#include <list>
#include "Bullet.h"

using namespace std;

#define TIMER_ID 1
#define TIMER_INTERVAL 10

//按键映射,判断按键是否按下或者弹起的宏
#define KEYDOWN(key) GetAsyncKeyState(key)&0x8000
#define KEYUP(key) !(GetAsyncKeyState(key)&0x8000)

const short DOWN=0, LEFT=1, UP=2, RIGHT=3;

//常量定义
const int GAME_LEVEL_ALL = 3;
//const int GAME_WINDOW_BLOCK = 15;已经在stdafx.h中定义
const int GAME_BLOCK_WIDTH = 40;

const int GS_RUNNING = 0;
const int GS_PAUSE = 1;
const int GS_LOST = 2;
const int GS_WIN = 3;
const int GS_LOADING = 4;
const int GS_BEGIN =5;
const int GS_GAMEOVER = 6;

//游戏数据与状态定义
bool player_death;
short player_life;
int game_state = GS_BEGIN;
int game_level;
HDC screen = GetDC(NULL);
HDC cachehDC = CreateCompatibleDC(screen);
HWND hWindow;
list<Bullet*> player_bullet; //玩家子弹
list<GTank*> enemy_tank; //敌人坦克
list<list<Bullet*>*> enemy_bullet;//敌人炮弹容器

int enemy_num;
const int ENEMY_MAX_NOW=4;
const int ENEMY_MAX =20;

GTank player_tank(6,6,11,UP,2);

CRect clientRect;

MapBlock* map[GAME_WINDOW_BLOCK][GAME_WINDOW_BLOCK] = {NULL};

void lastClean();

void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);

void InitializeProgram();
void InitializeMap(short level);
void DrawGame();
void DrawBackground();
void DrawMapExceptTree();
void DrawMapTree();
void Print();
void Keydown();
void DrawAndDealBullet();