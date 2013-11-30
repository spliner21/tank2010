#ifndef _BONUS_H_
#define _BONUS_H_

#include "includes.h"

class bonus
{
private:
	sf::Image iBonus[8];	//grafiki bonusów
	sf::Sprite sBonus;
	int posId[2];			//wspó³rzêdne aktualnej pozycji
	int bonusCounter;		//odliczanie czasu trwania bonusu
protected:
	int BonusMap[52][52];		//mapa bonusów - wype³niona zerami, chyba, ¿e jest bonus, wtedy jedynki w kwadracie z bonusami
	int bonusType;				//Czo³g – 1, He³m – 2, Granat – 3, Gwiazda – 4, Zegar – 5, £opata - 6, Pistolet - 7, Statek - 8.
public:
	bonus(std::string path);	//konstruktor w oparciu o œcie¿kê do katalogu grafik
	bool isBonus()
	{
		if(bonusType>0)
			return true;
		return false;
	}
	void displayBonus(sf::RenderWindow &Window)	//wyœwietlanie bonusu
	{
		Window.Draw(sBonus);
		--bonusCounter;
		if(bonusCounter == 0)
			clear();
	}
	void clear();	//wyczyszczenie mapy z bonusu
	void GenerateBonus();	//losowanie bonusu
};

#endif