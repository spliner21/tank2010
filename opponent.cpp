#include "opponent.h"

void opponent::move(int colmap[52][52], int typemap[52][52], int bonusmap[52][52])		//funkcja losuj�ca ruch
{
	float random[2] = {-1,1};	//losowanie kierunku
	int typer = std::rand()%2;
	int r = int(GetRotation());	//pobranie aktualnego kierunku
	int result = 0;
	switch(r)
	{	//cztery analogiczne sytuacje
	case 0:
		result = vehicle::move(0,1,colmap,typemap,bonusmap);	//ruch w aktualnym kierunku
		if(result && rand()%4 == 3)	//zmiana kierunku z prawdopodobie�stwem 1/4
			vehicle::move(random[typer],0,colmap,typemap,bonusmap);	//pr�ba ruchu w lewo lub w prawo
		break;
	case 180:
		result = vehicle::move(0,-1,colmap,typemap,bonusmap);
		if(result && rand()%4 == 3)
			vehicle::move(random[typer],0,colmap,typemap,bonusmap);
		break;
	case 90:
		result = vehicle::move(1,0,colmap,typemap,bonusmap);
		if(result && rand()%4 == 3)
			vehicle::move(0,random[typer],colmap,typemap,bonusmap);
		break;
	case 270:
		result = vehicle::move(-1,0,colmap,typemap,bonusmap);
		if(result && rand()%4 == 3)
			vehicle::move(0,random[typer],colmap,typemap,bonusmap);
		break;
	}
}	

void opponent::display(sf::RenderWindow &Window, int colmap[52][52], int &tanks)
{	//f-cja wy�wietlaj�ca czo�g lub eksplozj�
	bool temp;
	if(!AmIDestroyed() && displayable)	//je�li czo�g nie jest zniszczony
		vehicle::display(Window);	//to wy�wietlamy go
	else
	{	//w innym przypadku wy�wietlamy eksplozj� przez 30 klatek
		if(tanks > 4)
		{ //po 30 klatkach resetujemy czo�g na pozycj� startow�
			temp = explosion::display(Window);
			if(!temp)
			{
				undestroy();
				health = stdHealth;
				respawn(colmap);
				--tanks;
			}
		}
		else 
		{	//je�li czo�g ju� nie ma si� ponownie pojawi�
			if(displayable)
			{	
				temp = explosion::display(Window);
				if(!temp)
				{
					--tanks;
					displayable = false;
				}
			}
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