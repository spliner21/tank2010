#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "includes.h"
#include "bullet.h"
#include "explosion.h"

class weapon
{
private:
	int power;			//jak mocna jest broñ
	int MyWType;		//mój Typ broni
	bullet MyBullet;	//Pocisk
	int BulletCounter;	//Iloœæ pocisków
	bool isDestroyed;

public:
	weapon()		//k-tor
		:power(1),BulletCounter(0)
	{
	}
	weapon(int pwr, std::string PathToBullet, int Type)	//k-tor z wszystkimi parametrami
		:power(pwr), MyBullet(PathToBullet),BulletCounter(0), MyWType(Type), isDestroyed(false)
	{
	}
	sf::Sprite ReturnBullet()	//funkcja zwracaj¹ca sprite pocisku
	{
		return MyBullet.ReturnBullet();
	}
	int AmIarmed()	//zwraca true, jesli pocisk jest w locie
	{
		return BulletCounter;
	}
	int ReturnPwr()	//zwraca true, jesli pocisk jest w locie
	{
		return power;
	}
	void IncreasePower(int mode)
	{	//inkrementacja mocy - jeœli bonus gwiazdy to x2, jeœli bonus pistoletu to x4
		switch(mode)
		{
		case 0:
			power *= 2;
			break;
		case 1:
			power *= 4;
			break;
		}
	}
	void resetParams()
	{	//reset po œmierci
		power = 1;
	}
	int moveBullet(int TypeMap[52][52], int CollisionMap[52][52]);	//f-cja przesuwaj¹ca pocisk
	bool AmIDestroyed()		//zwraca true, jeœli czo³g jest zniszczony
	{
		return isDestroyed;
	}
	void destroy()
	{
		isDestroyed = true;
	}
	void undestroy()
	{
		isDestroyed = false;
	}
	void shot(float px, float py, float direction, int CollisionMap[52][52]);	//strza³
};
#endif