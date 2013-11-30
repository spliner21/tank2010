#include "vehicle.h"


vehicle::vehicle(std::string pathto, float px, float py, int speed, int direction, int Type)
	:speed(speed), myType(Type+10), startPos(px,py),pwrCounter(-1), slider(0), gotBonus(false), isProtected(false), isAmphibia(false)
	//k-tor w oparciu o wszystkie potrzebne parametry
{
	std::string tempgfx = pathto;
	for(int i =0; i<4; i++)
	{
		tempgfx += ((Type%10)%4)+'0';
		tempgfx += '-';
		tempgfx += i + '1';
		tempgfx += ".png";
		if(iTank[i].LoadFromFile(tempgfx))			//za³adowanie grafiki
		{
			iTank[i].SetSmooth(false);
		}
		tempgfx = pathto;
	}
	tempgfx = "gfx//protection.png";
	if(iAdds[0].LoadFromFile(tempgfx))			//za³adowanie grafiki
	{
		iAdds[0].SetSmooth(false);
	}
	tempgfx = "gfx//amphibia.png";
	if(iAdds[1].LoadFromFile(tempgfx))			//za³adowanie grafiki
	{
		iAdds[1].SetSmooth(false);
	}
	
	sTank.SetOrigin(20,20);		//przesuniêcie œrodka
	sAdd.SetOrigin(20,20);		//przesuniêcie œrodka
}

void vehicle::fill(int colmap[52][52], int mode)
{		//funkcja wype³niaj¹ca mapê kolizji zerami lub nr-em czo³gu
	int ax, ay, i, j;
	ax = int((GetX()-MAPXPOS)/10);	//skwantowanie pozycji do pól na mapie kolizji
	ay = int((GetY()-MAPYPOS)/10);	
	switch(mode)
	{
	case 0:		//wype³nienie zerem (kwadrat 8x8)
		for(i = -4; i<4; i++)
		{
			if((ax+i)<52 && (ax+i)>=0)
			{
				for(j =-4; j<4; j++)
					if((ay+j)<52 && (ay+j)>=0 && (colmap[ay+j][ax+i]==myType || colmap[ay+j][ax+i] >=100))
						colmap[ay+j][ax+i]=0;
			}
		}
		break;
	case 1:		//wype³nienie numerem czo³gu (kwadrat 4x4)
		for(i = -2; i<2; i++)
		{
			if((ax+i)<52 && (ax+i)>=0)
			{
				for(j =-2; j<2; j++)
				if((ay+j)<52 && (ay+j)>=0 && colmap[ay+j][ax+i] == 0)
					colmap[ay+j][ax+i]=myType;
			}
		}
		break;
	}
}


void vehicle::slide(int colmap[52][52], int typemap[52][52], int bonusmap[52][52])	//poœlizg na lodzie
{
	if(slider-- > 0)	//dekrementacja licznika
	{
		if(typemap[int(sTank.GetPosition().y-MAPYPOS)/10][int(sTank.GetPosition().x-MAPXPOS)/10] == 3)	//czy dalej na lodzie
		{
			switch(int(sTank.GetRotation()))	//w zale¿noœci od kierunku
			{
			case 0:
				move(0,1,colmap,typemap,bonusmap);
				break;
			case 180:
				move(0,-1,colmap,typemap,bonusmap);
				break;
			case 90:
				move(1,0,colmap,typemap,bonusmap);
				break;
			case 270:
				move(-1,0,colmap,typemap,bonusmap);
				break;
			}
		}
		else slider = 0;
	}
}

int vehicle::move(float x, float y, int colmap[52][52], int typemap[52][52], int bonusmap[52][52])
{	//ruch
	sf::Vector2f sV = sTank.GetPosition();	//pobranie aktualnej pozycji
	int ax, ay, i, tableEl;
	int test=0;
	fill(colmap, 0);	//wyczyszczenie aktualnej pozycji na mapie kolizji
	float r1 = sTank.GetRotation();
	if(x != 0)		//zoptymalizowano - by³o czytelniej, teraz jest optymalniej :D
		sTank.SetRotation(180.f-x*90.f);	//ustalenie obrotu
	else if(y != 0)
		sTank.SetRotation((1-y)*90.f);
	float r2 = sTank.GetRotation();	//pobranie nowego obrotu
	if(r1!=r2)
	{	//jeœli obrót siê zmieni³ to skwantowanie pozycji do siatki
		if(r1 == 0 && int(r2)%180 == 90)
		{
			if(int(sV.y)%20 < 10)
				sTank.SetPosition(sV.x,sV.y - int(sV.y)%20);
			else
				sTank.SetPosition(sV.x,sV.y + 20 - int(sV.y)%20);
		}
		else if(r1 == 180 && int(r2)%180 == 90)
		{
			if(int(sV.y)%20 < 10 && int(sV.y)%20 > 5)
				sTank.SetPosition(sV.x,sV.y + 20 - int(sV.y)%20);
			else
				sTank.SetPosition(sV.x,sV.y - int(sV.y)%20);
		}
		else if(r1 == 270 && int(r2)%180 == 0)
		{
			if(int(sV.x)%20 < 10)
				sTank.SetPosition(sV.x - int(sV.x)%20,sV.y);
			else
				sTank.SetPosition(sV.x + 20 - int(sV.x)%20,sV.y);
		}
		else if(r1 == 90 && int(r2)%180 == 0)
		{
			if(int(sV.x)%20 < 10 && int(sV.x)%20 > 5)
				sTank.SetPosition(sV.x + 20 - int(sV.x)%20,sV.y);
			else
				sTank.SetPosition(sV.x - int(sV.x)%20,sV.y);
		}
		sV = sTank.GetPosition();	//pobranie nowej pozycji
		sAdd.SetPosition(sV);		//ustawienie pozycji dodatków
	}
	else if(sV.x+x*speed >= 20+MAPXPOS && sV.x+x*speed <= 500+MAPXPOS && sV.y-y*speed >= 20+MAPYPOS && sV.y-y*speed <= 500+MAPYPOS)
	{	//sprawdzenie ruchu na mapie kolizji
		switch(int(r2))
		{	//cztery analogiczne sytuacje zale¿ne od obrotu
		case 0:
			ax = int((sV.x-MAPXPOS)/10);
			ay = int((sV.y-speed-MAPYPOS)/10);	//obliczenie skwantowanej pozycji na siatce kolizji
			for(i=-2;((ax+i)<52 && i<2);i++)
			{
				tableEl = colmap[ay-2][ax+i]; 
				if(tableEl == 1 || tableEl == 2 || (tableEl == 5 && !isAmphibia) || (tableEl >=6  && tableEl != myType))
					test = 1;	//jeœli napotkamy mur, skrzynie, wodê, or³a lub inny czo³g to zg³aszamy kolizjê
				else if(typemap[ay-2][ax+i] == 3 && slider < 1)
					++slider;
				if(bonusmap[ay-2][ax+i])
					gotBonus = true;
			}
			break;
		case 270:
			ax = int((sV.x-speed-MAPXPOS)/10);
			ay = int((sV.y-MAPYPOS)/10);
			for(i=-2;((ay+i)<52 && i<2);i++)
			{
				tableEl = colmap[ay+i][ax-2];
				if(tableEl == 1 || tableEl == 2 || (tableEl == 5 && !isAmphibia) || (tableEl >=6  && tableEl != myType))
					test = 1;
				else if(typemap[ay+i][ax-2] == 3 && slider < 1)
					++slider;
				if(bonusmap[ay+i][ax-2])
					gotBonus = true;
			}
			break;
		case 180:
			ax = int((sV.x-MAPXPOS)/10);
			ay = int((sV.y-MAPYPOS)/10);
			for(i=-2;((ax+i)<52 && i<2);i++)
			{
				tableEl = colmap[ay+2][ax+i];
				if(tableEl == 1 || tableEl == 2 || (tableEl == 5 && !isAmphibia) || (tableEl >=6  && tableEl != myType))
					test = 1;
				else if(typemap[ay+2][ax+i] == 3 && slider < 1)
					++slider;
				if(bonusmap[ay+2][ax+i])
					gotBonus = true;
			}
			break;
		case 90:
			ax = int((sV.x-MAPXPOS)/10);
			ay = int((sV.y-MAPYPOS)/10);
			for(i=-2;((ay+i)<52 && i<2);i++)
			{
				tableEl = colmap[ay+i][ax+2];
				if(tableEl == 1 || tableEl == 2 || (tableEl == 5 && !isAmphibia) || (tableEl >=6  && tableEl != myType))
					test = 1;
				else if(typemap[ay+i][ax+2] == 3 && slider < 1)
					++slider;
				if(bonusmap[ay+i][ax+2])
					gotBonus = true;
			}
			break;
		}
		if(!test)
		{
			sTank.Move(x*speed,-y*speed);	//jeœli nie napotkaliœmy kolizji to przesuwamy czo³g
			sAdd.SetPosition(sTank.GetPosition());
		}
	}
	else
		test = 1;
	fill(colmap, 1);	//wype³niamy siatkê swoim numerem
	return test;
}