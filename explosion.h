#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "includes.h"

class explosion 
{
private:
	int ExpCounter;			//licznik klatki eksplozji
	sf::Image iExp[15];		//grafiki eksplozji (dzia³a na zasadzie 1,2,3,...,14,15,15,14,13,....,3,2,1)
	sf::Sprite sExp;		//sprite eksplozji

public:
	explosion()	//k-tor domyœlny
	{
	}
	explosion(std::string pathTo);	//k-tor w oparciu o œcie¿kê do katalogu grafik
	void SetPosition(sf::Vector2f sV)	//f-cja ustalaj¹ca miejsce eksplozji
	{
		sExp.SetPosition(sV);
	}
	bool display(sf::RenderWindow &Window);	//f-cja wyœwietlaj¹ca eksplozjê
};


#endif
