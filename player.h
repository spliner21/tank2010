#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "tank.h"

class player: public tank
{
private:
	int lifes;		//iloœæ ¿yæ
	int points;		//liczba zdobytych punktów
public:
	player()	//k-tor domyœlny
		:points(0)
	{
	}
	player(std::string pathTo, float px, float py, int life, int speed, int power, int lifes, int Type, int pts)
		:lifes(lifes), points(pts), tank(pathTo,"\\tank-", px, py, life, speed, power,0,Type+10)
	{	//k-tor w oparciu o wszystkie potrzebne parametry
	}
	void respawn(int colmap[52][52])
	{
		if(pwrCounter > 0)
			--pwrCounter;
		else pwrCounter = 0;
		sTank.SetImage(iTank[pwrCounter]);
		sTank.SetPosition(startPos);
		fill(colmap,1);	//i wype³niamy nim w tym miejscu mapê kolizji
	}
	void incrementPower()
	{
		if(++pwrCounter < 4)
			sTank.SetImage(iTank[pwrCounter]);
	}
	int AmI()
	{
		return lifes;
	}
	int AddPoints(int pts)	//dodawanie pktów
	{
		return points+=pts;
	}
	void AddLife()	//dodawanie pktów
	{
		++lifes;
	}
	std::string GetPoints(std::string id);	//zwraca punkty w postaci ³ancucha znaków
	std::string GetLifes(std::string id);	//zwraca punkty w postaci ³ancucha znaków
	void hit(int colmap[52][52]);		//reakcja na bycie trafionym
	void display(sf::RenderWindow &, int colmap[52][52]);	//f-cja wyœwietlaj¹ca czo³g

};
#endif