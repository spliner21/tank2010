#include "player.h"

std::string player::GetPoints(std::string id)
{		//funkcja zwracaj¹ca iloœæ punktów w postaci ci¹gu znaków
	std::string temp, result;
	int n = points;
	result = id;		//dodanie identyfikatora gracza
	result += ": ";
	do	//pêtla dodaj¹ca znaki (od prawej do lewej)
	{
		temp += n%10 + '0';
		n -= n%10;
	}
	while(n /= 10);
	for(int i = temp.size()-1; i >= 0; i--)	//pêtla przepisuj¹ca znaki w odwrotnej kolejnoœci
		result += temp[i];
	return result;
}

std::string player::GetLifes(std::string id)
{		//funkcja zwracaj¹ca iloœæ punktów w postaci ci¹gu znaków
	std::string temp, result;
	int n = lifes;
	result = id;		//dodanie identyfikatora gracza
	result += ": ";
	do	//pêtla dodaj¹ca znaki (od prawej do lewej)
	{
		temp += n%10 + '0';
		n -= n%10;
	}
	while(n /= 10);
	for(int i = temp.size()-1; i >= 0; i--)	//pêtla przepisuj¹ca znaki w odwrotnej kolejnoœci
		result += temp[i];
	return result;
}

void player::hit(int colmap[52][52])
{		//reakcja na trafienie
	fill(colmap,0);	//wype³nienie pozycji na mapie kolizji zerami
	if(tank::hit(1))
	{
		SetRotation(0);	//odwrócenie czo³gu w odpowiednim kierunku
		--lifes;		//dekrementacja ¿yæ
	}
}

void player::display(sf::RenderWindow &Window, int colmap[52][52])
{	//f-cja wyœwietlaj¹ca czo³g lub eksplozjê
	bool temp;
	if(!AmIDestroyed() && displayable)	//jeœli czo³g nie jest zniszczony
		vehicle::display(Window);	//to wyœwietlamy go
	else if(displayable)
	{	//w innym przypadku wyœwietlamy eksplozjê przez 30 klatek
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
	if(isProtected > 0)	//dekrementacja znaczników bonusowych
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