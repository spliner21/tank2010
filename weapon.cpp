#include "weapon.h"

int weapon::moveBullet(int TypeMap[52][52], int CollisionMap[52][52])
{	//f-cja przesuwaj¹ca pocisk
	int result = 0;
	int tmp;
	if(BulletCounter > 0)	//jeœli jest jeszcze pocisk do trafienia
	{
		tmp = BulletCounter;
		result = MyBullet.move(TypeMap,CollisionMap,MyWType,BulletCounter);
		if(BulletCounter < tmp)	
		{
			MyBullet.fill(CollisionMap, MyWType);
		}
		else if(result!=0)
		{	//dekrementacja podwójna - iloœæ pocisków = mocy/2
			--BulletCounter;
			if(BulletCounter>0)
				--BulletCounter;
		}

	}
	return result;		
}

void weapon::shot(float px, float py, float direction, int CollisionMap[52][52])
{
	int result = 1;
	if(BulletCounter == false)		//jeœli pocisk nie jest w locie (jest dostêpny do strza³u)
	{
		switch(int(direction))		//ustalenie pozycji i kierunku pocisku na podstawie pozycji i kierunku czo³gu
		{
		case 0:
			if((py-BULLETPOS)>MAPYPOS)
			{
				MyBullet.SetPosition(px,py-int(py)%10+5-BULLETPOS);
				if(CollisionMap[int(py-int(py)%10-BULLETPOS-MAPYPOS)/10][int(px-MAPXPOS)/10]==0)
					CollisionMap[int(py-int(py)%10-BULLETPOS-MAPYPOS)/10][int(px-MAPXPOS)/10]=MyWType;
			}
			else
				result = 0;
			break;
		case 270:
			if((px-BULLETPOS)>MAPXPOS)
			{
				MyBullet.SetPosition(px-int(px)%10+5-BULLETPOS,py);
				if(CollisionMap[int(py-MAPYPOS)/10][int(px-int(px)%10-BULLETPOS-MAPXPOS)/10]==0)
					CollisionMap[int(py-MAPYPOS)/10][int(px-int(px)%10-BULLETPOS-MAPXPOS)/10]=MyWType;
			}
			else
				result = 0;
			break;
		case 180:
			if((py+BULLETPOS)<560)
			{
				MyBullet.SetPosition(px,py-int(py)%10+BULLETPOS-5);
				if(CollisionMap[int(py-int(py)%10+BULLETPOS-MAPYPOS)/10-1][int(px-MAPXPOS)/10-1]==0)
					CollisionMap[int(py-int(py)%10+BULLETPOS-MAPYPOS)/10-1][int(px-MAPXPOS)/10-1]=MyWType;
			}
			else
				result = 0;
			break;
		case 90:
			if((px+BULLETPOS)<560)
			{
				MyBullet.SetPosition(px-int(px)%10+BULLETPOS-5,py);
				if(CollisionMap[int(py-MAPYPOS)/10-1][int(px-int(px)%10+BULLETPOS-MAPXPOS)/10-1]==0)
					CollisionMap[int(py-MAPYPOS)/10-1][int(px-int(px)%10+BULLETPOS-MAPXPOS)/10-1]=MyWType;
			}
			else
				result = 0;
			break;
		}
		if(result)
		{
			MyBullet.SetRotation(direction);
			BulletCounter = power;
		}
	}
}