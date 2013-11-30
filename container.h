#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "field.h"

/********************************
*		klasa kontenera 		*
*	   (przechowuje grafiki)	*
*********************************/

class container
{
protected:
	field **fTab;			//tablica elementów podstawowych mapy ("klocki" :P)
	sf::Image uiBg;				//t³o gry
	sf::Sprite sUiBg;
	sf::Image EagleProtection;	//os³ona or³a
	sf::Sprite sEagleProtection;
	sf::Image EndScreen;		//ekran koñcowy
	sf::Sprite sEndScreen;
	sf::Image smallTank;		//ma³y czo³g przeciwnika w panelu informacyjnym
	sf::Sprite smallTanks[20];	//plansza 20 takich czo³gów
public:
	container(std::string);	//k-tor
	~container();	//d-tor
};


#endif