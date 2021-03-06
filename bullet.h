#ifndef _BULLET_H_
#define _BULLET_H_
#include "includes.h"

class bullet
{
private:
	sf::Image iBullet;		//obrazek
	sf::Sprite sBullet;		//grafika
public:
	bullet(std::string PathToBullet)	//k-tory
	{
		iBullet.LoadFromFile(PathToBullet);
		sBullet.SetImage(iBullet);
		sBullet.SetOrigin(2,5);
	}
	bullet()
	{
	}
	~bullet()	//d-tor
	{
	}
	sf::Sprite ReturnBullet()	//funkcja zwracajaca sprite pocisku
	{
		return sBullet;
	}
	void SetPosition(float x, float y)	//funkcja ustalająca pozycję
	{
		sBullet.SetPosition(x,y);
	}
	void SetRotation(float r)	//funkcja obracająca pocisk
	{
		sBullet.SetRotation(r);
	}
	sf::Vector2f GetPosition()	//funkcja ustalająca pozycję
	{
		return sBullet.GetPosition();
	}
	float GetRotation()	//funkcja obracająca pocisk
	{
		return sBullet.GetRotation();
	}
	void fill(int collmap[52][52], int type);	//wypełnienie mapy kolizji przez pocisk
	int move(int TypeMap[52][52], int CollisionMap[52][52], int TypeId, int &BulletCounter);		//przesuwanie pocisku
};
#endif