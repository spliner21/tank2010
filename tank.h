#ifndef _TANK_H_
#define _TANK_H_
#include "vehicle.h"
#include "weapon.h"

class tank: public vehicle, public weapon, public explosion
{
protected:
	int health;				//za ka¿dym trafieniem dekrementujemy, gdy 0 to niszczymy
	int stdHealth;			//zapamiêtana wartoœæ
	bool displayable;		//zezwolenie na wyœwietlenie
public:
	tank();		//k-tory
	tank(std::string, std::string, float, float, int, int, int, int,int);
	bool AmIDisplayable()
	{
		return displayable;
	}
	int hit(int power);				//trafiony pociskiem
};
#endif