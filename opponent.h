#ifndef _OPONNENT_H_
#define _OPONNENT_H_
#include "tank.h"

class opponent: public tank
{
private:	
	int points;
public:
	
	opponent(std::string pathTo, float px, float py, int life, int speed, int power, int points,int Type)
		:points(points), tank(pathTo,"\\opp-", px, py, life, speed, power,0,Type)
	{	//k-tor w oparciu o wszystkie potrzebne parametry
		SetRotation(180.f);
	}
	void respawn(int colmap[52][52])
	{
		pwrCounter = (++pwrCounter)%4;
		sTank.SetImage(iTank[pwrCounter]);
		sTank.SetPosition(startPos);
		fill(colmap,1);	//i wype³niamy nim w tym miejscu mapê kolizji
	}
	void move(int colmap[52][52], int typemap[52][52], int bonusmap[52][52]);		//funkcja losuj¹ca ruch
	int hit(int colmap[52][52],int power)
	{	//reakcja na trafienie
		fill(colmap,0);
		if(tank::hit(power))
			return points;
		else return 0;
	}
	void display(sf::RenderWindow &, int colmap[52][52], int &tanks);	//f-cja wyœwietlaj¹ca czo³g
}; 

#endif