#include "player.h"

std::string player::GetPoints(std::string id)
{		//funkcja zwracaj�ca ilo�� punkt�w w postaci ci�gu znak�w
	std::string temp, result;
	int n = points;
	result = id;		//dodanie identyfikatora gracza
	result += ": ";
	do	//p�tla dodaj�ca znaki (od prawej do lewej)
	{
		temp += n%10 + '0';
		n -= n%10;
	}
	while(n /= 10);
	for(int i = temp.size()-1; i >= 0; i--)	//p�tla przepisuj�ca znaki w odwrotnej kolejno�ci
		result += temp[i];
	return result;
}

std::string player::GetLifes(std::string id)
{		//funkcja zwracaj�ca ilo�� punkt�w w postaci ci�gu znak�w
	std::string temp, result;
	int n = lifes;
	result = id;		//dodanie identyfikatora gracza
	result += ": ";
	do	//p�tla dodaj�ca znaki (od prawej do lewej)
	{
		temp += n%10 + '0';
		n -= n%10;
	}
	while(n /= 10);
	for(int i = temp.size()-1; i >= 0; i--)	//p�tla przepisuj�ca znaki w odwrotnej kolejno�ci
		result += temp[i];
	return result;
}

void player::hit(int colmap[52][52])
{		//reakcja na trafienie
	fill(colmap,0);	//wype�nienie pozycji na mapie kolizji zerami
	if(tank::hit(1))
	{
		SetRotation(0);	//odwr�cenie czo�gu w odpowiednim kierunku
		--lifes;		//dekrementacja �y�
	}
}

void player::display(sf::RenderWindow &Window, int colmap[52][52])
{	//f-cja wy�wietlaj�ca czo�g lub eksplozj�
	bool temp;
	if(!AmIDestroyed() && displayable)	//je�li czo�g nie jest zniszczony
		vehicle::display(Window);	//to wy�wietlamy go
	else if(displayable)
	{	//w innym przypadku wy�wietlamy eksplozj� przez 30 klatek
		temp = explosion::display(Window);
		if(!temp)
		{
			if(lifes)
			{
				undestroy();
				health = stdHealth;
				respawn(colmap);
			}
			else displayable = false;
		}
	}
	if(isProtected > 0)	//dekrementacja znacznik�w bonusowych
	{
		--isProtected;
		displayAdd(Window);
	}
	if(isAmphibia > 0)
	{
		--isAmphibia;
		displayAdd(Window);
	}
}