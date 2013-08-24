#pragma once

#include "resource.h"

int GAME_WINDOW_BLOCK = 15;
int GAME_BLOCK_WIDTH = 40;

HDC hDC;
HDC cacheDC;
HDC backgroundDC;
HDC bulletDC;
HDC blockDC;
HDC fireDC;

CBitmap cacheCBitmap;
CImage backgroundImage;
