#include "opponent.h"

void opponent::move(int colmap[52][52], int typemap[52][52], int bonusmap[52][52])		//funkcja losuj¹ca ruch
{
	float random[2] = {-1,1};	//losowanie kierunku
	int typer = std::rand()%2;
	int r = int(GetRotation());	//pobranie aktualnego kierunku
	int result = 0;
	switch(r)
	{	//cztery analogiczne sytuacje
	case 0:
		result = vehicle::move(0,1,colmap,typemap,bonusmap);	//ruch w aktualnym kierunku
		if(result && rand()%4 == 3)	//zmiana kierunku z prawdopodobieñstwem 1/4
			vehicle::move(random[typer],0,colmap,typemap,bonusmap);	//próba ruchu w lewo lub w prawo
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
{	//f-cja wyœwietlaj¹ca czo³g lub eksplozjê
	bool temp;
	if(!AmIDestroyed() && displayable)	//jeœli czo³g nie jest zniszczony
		vehicle::display(Window);	//to wyœwietlamy go
	else
	{	//w innym przypadku wyœwietlamy eksplozjê przez 30 klatek
		if(tanks > 4)
		{ //po 30 klatkach resetujemy czo³g na pozycjê startow¹
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
		{	//jeœli czo³g ju¿ nie ma siê ponownie pojawiæ
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