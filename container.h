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
	field **fTab;			//tablica element�w podstawowych mapy ("klocki" :P)
	sf::Image uiBg;				//t�o gry
	sf::Sprite sUiBg;
	sf::Image EagleProtection;	//os�ona or�a
	sf::Sprite sEagleProtection;
	sf::Image EndScreen;		//ekran ko�cowy
	sf::Sprite sEndScreen;
	sf::Image smallTank;		//ma�y czo�g przeciwnika w panelu informacyjnym
	sf::Sprite smallTanks[20];	//plansza 20 takich czo�g�w
public:
	container(std::string);	//k-tor
	~container();	//d-tor
};


#endif