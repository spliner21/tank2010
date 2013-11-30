#ifndef _VEHICLE_H_
#define _VEHICLE_H_
#include "includes.h"

class vehicle
{
private:
	int speed;				//pr�dko�� pojazdu
	int myType;				//m�j Typ
	sf::Image iAdds[2];		//wska�nik na grafiki protekcji i amfibii
	sf::Sprite sAdd;		//parametry wizualne efektu
	int slider;				//po�lizg na lodzie
	bool gotBonus;			//natrafienie na bonus
protected:
	sf::Vector2f startPos;	//pozycja startowa
	sf::Image iTank[4];		//wska�nik na grafiki czo�g�w
	sf::Sprite sTank;		//parametry wizualne czo�gu
	int pwrCounter;
	int isProtected;		//czy jest os�ona
	int isAmphibia;			//czy jest amfibi� (os�ona jednorazowa + zdolno�� przep�ywania nad wod�)
public:
	vehicle()	//k-tory
	{
	}
	vehicle(std::string, float, float,int,int,int);
	~vehicle()	//d-tor
	{
	}
	bool checkBonus()
	{	//"z�apanie" bonusu
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
	int GetMyType()			//zwraca identyfikator czo�gu
	{
		return myType;
	}
	void SetRotation(float r)	//funkcje ustawiaj�ce
	{							//1 - obr�t
		sTank.SetRotation(r);
	}
	void SetPosition(const sf::Vector2f pV)
	{							//2 - pozycj�
		sTank.SetPosition(pV);
	}
	float GetRotation()		//funkcje zwracaj�ce parametry
	{						//1 - obr�t
		return sTank.GetRotation();
	}
	sf::Vector2f GetPosition()
	{						//2 - pozycj�
		return sTank.GetPosition();
	}
	float GetX()
	{						//3 - pozycj� x
		return sTank.GetPosition().x;
	}
	float GetY()
	{						//4 - pozycj� y
		return sTank.GetPosition().y;
	}
	void display(sf::RenderWindow &Window)	//f-cja wy�wietlaj�ca
	{
		Window.Draw(sTank);
	}
	void displayAdd(sf::RenderWindow &Window)	//f-cja wy�wietlaj�ca
	{
		Window.Draw(sAdd);
	}
	void fill(int colmap[52][52], int mode);		//wype�nienie mapy kolizji 
	void slide(int colmap[52][52], int typemap[52][52], int bonusmap[52][52]);
	int move(float, float, int colmap[52][52], int typemap[52][52], int bonusmap[52][52]);	
														//funkcja wykonuj�ca ruch
};
#endif