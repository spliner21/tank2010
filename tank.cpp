#include "tank.h"

tank::tank()		//k-tor domyœlny
	:displayable(true)
{
}
tank::tank(std::string pathTo,std::string fnamepfx, float px, float py, int life, int speed, int power, int dir,int Type)
	:vehicle(pathTo+fnamepfx,px,py,speed,dir,Type), weapon(power,pathTo+"\\bullet.png",Type+100), 
	health(life), stdHealth(life), explosion(pathTo), displayable(true)
{	//k-tor w oparciu o wszystkie potrzebne parametry
}
int tank::hit(int power)				//trafiony pociskiem
{	//trafienie pociskiem
	if(!isProtected && !isAmphibia)
	{
		health -= power;
		if(health <= 0)
		{
			destroy();	//oznaczenie, ¿e czo³g zostal zniszczony
			explosion::SetPosition(GetPosition());	//ustawienie eksplozji w miejscu czo³gu
			resetParams();
			return true;
		}
	}
	else if(isAmphibia)
		isAmphibia = 0;
	return false;
}
