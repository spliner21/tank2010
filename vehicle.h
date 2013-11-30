#ifndef _VEHICLE_H_
#define _VEHICLE_H_
#include "includes.h"

class vehicle
{
private:
	int speed;				//prêdkoœæ pojazdu
	int myType;				//mój Typ
	sf::Image iAdds[2];		//wskaŸnik na grafiki protekcji i amfibii
	sf::Sprite sAdd;		//parametry wizualne efektu
	int slider;				//poœlizg na lodzie
	bool gotBonus;			//natrafienie na bonus
protected:
	sf::Vector2f startPos;	//pozycja startowa
	sf::Image iTank[4];		//wskaŸnik na grafiki czo³gów
	sf::Sprite sTank;		//parametry wizualne czo³gu
	int pwrCounter;
	int isProtected;		//czy jest os³ona
	int isAmphibia;			//czy jest amfibi¹ (os³ona jednorazowa + zdolnoœæ przep³ywania nad wod¹)
public:
	vehicle()	//k-tory
	{
	}
	vehicle(std::string, float, float,int,int,int);
	~vehicle()	//d-tor
	{
	}
	bool checkBonus()
	{	//"z³apanie" bonusu
		if(gotBonus)
		{
			gotBonus = false;
			return true;
		}
		return false;
	}
	void Protect()
	{
		isProtected = 450;	//15 sekund ochrony
		sAdd.SetImage(iAdds[0]);
	}
	void MakeAmphibia()
	{
		isAmphibia = 450;	//15 sekund ochrony
		sAdd.SetImage(iAdds[1]);
	}
	int GetMyType()			//zwraca identyfikator czo³gu
	{
		return myType;
	}
	void SetRotation(float r)	//funkcje ustawiaj¹ce
	{							//1 - obrót
		sTank.SetRotation(r);
	}
	void SetPosition(const sf::Vector2f pV)
	{							//2 - pozycjê
		sTank.SetPosition(pV);
	}
	float GetRotation()		//funkcje zwracaj¹ce parametry
	{						//1 - obrót
		return sTank.GetRotation();
	}
	sf::Vector2f GetPosition()
	{						//2 - pozycjê
		return sTank.GetPosition();
	}
	float GetX()
	{						//3 - pozycjê x
		return sTank.GetPosition().x;
	}
	float GetY()
	{						//4 - pozycjê y
		return sTank.GetPosition().y;
	}
	void display(sf::RenderWindow &Window)	//f-cja wyœwietlaj¹ca
	{
		Window.Draw(sTank);
	}
	void displayAdd(sf::RenderWindow &Window)	//f-cja wyœwietlaj¹ca
	{
		Window.Draw(sAdd);
	}
	void fill(int colmap[52][52], int mode);		//wype³nienie mapy kolizji 
	void slide(int colmap[52][52], int typemap[52][52], int bonusmap[52][52]);
	int move(float, float, int colmap[52][52], int typemap[52][52], int bonusmap[52][52]);	
														//funkcja wykonuj¹ca ruch
};
#endif