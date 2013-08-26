#include "stdafx.h"
#include "GTank.h"


GTank::GTank(short _x, short _y, short _type, short _direction, short _speed)
	:MoveableBlock(_x, _y, _type, _speed, _direction),frame(0)
{
	bullet_real_num = 0;
	real_x = BLOCK_WIDTH * x+4;
	real_y = BLOCK_WIDTH * y+4;
	top = _y * BLOCK_WIDTH+4;
	left = _x * BLOCK_WIDTH+4;
	bottom = top + BLOCK_WIDTH-4;
	right = left + BLOCK_WIDTH-4;
	TCHAR imageName[30];
	wsprintf(imageName,_T(".\\res\\image\\T%d.png"),type);
	blockImage.Load(imageName);
	TransparentPNG(&blockImage);
}


GTank::~GTank(void)
{
	for(list<Bullet*>::iterator i=player_bullet.begin();i!=player_bullet.end();++i)
		delete *i;
}

void GTank::Draw(HDC &hdc)
{
	blockImage.Draw(hdc, real_x, real_y, TANK_BLOCK_WIDTH, TANK_BLOCK_WIDTH, direction * blockImage.GetWidth()/4, 
		frame*blockImage.GetHeight()/2, blockImage.GetWidth()/4, blockImage.GetHeight()/2);
	//MessageBox(NULL,_T(""),_T(""),MB_OK);
}

void GTank::Move(short _direction)
{
	direction = _direction;
	frame++;
	if(frame == 2) frame=0;
	if(willHitMap() == true) return;
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

void GTank::Fire()
{
	if(bullet_real_num < BULLET_NUM)
		{
			int bullet_x=real_x+(BLOCK_WIDTH- Bullet::BULLET_WIDTH)/2;
			int bullet_y=real_y+(BLOCK_WIDTH- Bullet::BULLET_WIDTH)/2;
			switch(direction)
			{
				case DOWN:
					bullet_y+=BLOCK_WIDTH/2;
					break;
				case LEFT:
					bullet_x-=BLOCK_WIDTH/2;
					break;
				case UP:
					bullet_y-=BLOCK_WIDTH/2;
					break;
				case RIGHT:
					bullet_x+=BLOCK_WIDTH/2;

			}
			player_bullet.push_back(new Bullet(bullet_x, bullet_y,direction));
			bullet_real_num++;
			//MessageBox(NULL,_T(""),_T(""),MB_OK);
		}
}

bool GTank::willHitMap()
{
	extern MapBlock* map[GAME_WINDOW_BLOCK][GAME_WINDOW_BLOCK];
	short des_x1,des_y1,des_x2,des_y2;
	switch (direction)
	{
	case DOWN:
		{
			
			des_x1 = left / BLOCK_WIDTH;
			des_y1 = (bottom+speed) / BLOCK_WIDTH;
			des_x2 = (left +TANK_BLOCK_WIDTH-1)/BLOCK_WIDTH;
			des_y2 = des_y1;
			break;
		}
	case LEFT:
		{
			if((left - speed)<=0) return true;
			des_x1 = (left-speed) / BLOCK_WIDTH;
			des_y1 = top / BLOCK_WIDTH;
			des_x2 = des_x1;
			des_y2 = (top + TANK_BLOCK_WIDTH-1)/BLOCK_WIDTH;
			break;
		}
	case UP:
		{
			if((top - speed)<=0) return true;
			des_x1 = left / BLOCK_WIDTH;
			des_y1 = (top-speed) / BLOCK_WIDTH;
			des_x2 = (left + TANK_BLOCK_WIDTH-1)/BLOCK_WIDTH;
			des_y2 = des_y1;
			break;
		}
	case RIGHT:
		{
			des_x1 = (right+speed) / BLOCK_WIDTH;
			des_y1 = top / BLOCK_WIDTH;
			des_x2 = des_x1;
			des_y2 = (top + TANK_BLOCK_WIDTH-1)/BLOCK_WIDTH;
			break;
		}
	default:
		break;
	}
	if(des_x1 >14 || des_x1 <0 || des_x2 >14 || des_x2 <0 || des_y1 >14 || des_y1 <0 
		|| des_y2 >14 || des_y2 <0)
		return true;
	if(((map[des_x1][des_y1] == NULL) || (map[des_x1][des_y1]->type == 1)) 
				&& ((map[des_x2][des_y2] == NULL) || (map[des_x2][des_y2]->type == 1))) 
				return false;
	return true;
}

void GTank::DrawAndDealBullet(HDC &hDC)
{
	for(list<Bullet*>::iterator iter_bullet=player_bullet.begin(); iter_bullet!=player_bullet.end(); )
	{
		Bullet& bullet=**iter_bullet;
		if(bullet.hitAll() != true)
		{
			bullet.Move();
			(*(iter_bullet++))->Draw(hDC);
		}
		else
		{
			delete *iter_bullet;
			iter_bullet=player_bullet.erase(iter_bullet);
			bullet_real_num--;
		}
	}
}