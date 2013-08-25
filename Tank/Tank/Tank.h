#pragma once

#include "resource.h"
#include "MapBlock.h"
#include <fstream>
using namespace std;

#define TIMER_ID 1
#define TIMER_INTERVAL 10

const short DOWN=0, LEFT=1, UP=2, RIGHT=3;

HDC hdc;

const int GAME_LEVEL_ALL = 3;
const int GAME_WINDOW_BLOCK = 15;
const int GAME_BLOCK_WIDTH = 40;

const int GS_RUNNING = 0;
const int GS_PAUSE = 1;
const int GS_LOST = 2;
const int GS_WIN = 3;
const int GS_WAITING = 4;

int game_state = GS_WAITING;
int game_level = 0;

CRect clientRect;

MapBlock* map[GAME_WINDOW_BLOCK][GAME_WINDOW_BLOCK] = {NULL};

void Paint(HDC hdc);
void lastClean();

void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);
