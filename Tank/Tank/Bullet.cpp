#include "stdafx.h"
#include "Bullet.h"
#include <list>
using namespace std;


Bullet::Bullet(int _real_x, int _real_y, short _direction,  short _speed, short _type)
	:MoveableBlock(_real_x/BLOCK_WIDTH, _real_y/BLOCK_WIDTH, _type, _speed, _direction)
{
	real_x = _real_x;//放这里定义以免和Block里的数据冲突
	real_y = _real_y;
	blockImage.Load(_T(".\\res\\image\\bullet.png"));
	TransparentPNG(&blockImage);
	left = real_x;
	top = real_y;
	right = left + BULLET_WIDTH/2;
	bottom = top + BULLET_WIDTH/2;
	bullet_enable = true;
}

Bullet::~Bullet(void)
{
}

void Bullet::Move()
{
	switch (direction)
	{
	case DOWN:
		UpdataDataFromY(speed);
		break;
	case LEFT:
		UpdataDataFromX(-1 * speed);
		break;
	case UP:
		UpdataDataFromY(-1 * speed);
		break;
	case RIGHT:
		UpdataDataFromX(speed);
		break;
	default:
		break;
	}
}

void Bullet::Draw(HDC &hdc)
{
	blockImage.Draw(hdc, real_x, real_y, BULLET_WIDTH, BULLET_WIDTH, direction * blockImage.GetWidth()/4, 
		0, blockImage.GetWidth()/4, blockImage.GetHeight());
}

bool Bullet::hitMap()
{
		//撞地图
		extern MapBlock* map[GAME_WINDOW_BLOCK][GAME_WINDOW_BLOCK];
		short des_x1,des_y1,des_x2,des_y2;
		switch (direction)
		{
		case DOWN:
			{
			
				des_x1 = left / BLOCK_WIDTH;
				des_y1 = (bottom+speed) / BLOCK_WIDTH;
				des_x2 = (left +BULLET_WIDTH-1)/BLOCK_WIDTH;
				des_y2 = des_y1;
				break;
			}
		case LEFT:
			{
				if((left - speed)<=0) return true;
				des_x1 = (left-speed) / BLOCK_WIDTH;
				des_y1 = top / BLOCK_WIDTH;
				des_x2 = des_x1;
				des_y2 = (top + BULLET_WIDTH-1)/BLOCK_WIDTH;
				break;
			}
		case UP:
			{
				if((top - speed)<=0) return true;
				des_x1 = left / BLOCK_WIDTH;
				des_y1 = (top-speed) / BLOCK_WIDTH;
				des_x2 = (left + BULLET_WIDTH-1)/BLOCK_WIDTH;
				des_y2 = des_y1;
				break;
			}
		case RIGHT:
			{
				des_x1 = (right+speed) / BLOCK_WIDTH;
				des_y1 = top / BLOCK_WIDTH;
				des_x2 = des_x1;
				des_y2 = (top + BULLET_WIDTH-1)/BLOCK_WIDTH;
				break;
			}
		default:
			break;
		}
		if(des_x1 >14 || des_x1 <0 || des_x2 >14 || des_x2 <0 || des_y1 >14 || des_y1 <0 
			|| des_y2 >14 || des_y2 <0)
		{
			int a = right+speed;
			bullet_enable = false;
			return true;
		}
		if(map[des_x1][des_y1] != NULL && (map[des_x1][des_y1]->type == 3 || map[des_x1][des_y1]->type == 4 ||map[des_x1][des_y1]->type == 5)) 
		{
			map[des_x1][des_y1]->Explode();
			bullet_enable = false;
		}
		if(map[des_x2][des_y2] != NULL && (map[des_x2][des_y2]->type == 3 || map[des_x2][des_y2]->type == 4 ||map[des_x2][des_y2]->type == 5)) 
		{
			map[des_x2][des_y2]->Explode();
			bullet_enable = false;
		}

		if(!bullet_enable) return true;

		return false;
}