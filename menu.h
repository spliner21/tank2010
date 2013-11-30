#ifndef _UI_H_
#define _UI_H_
#include "includes.h"

class menu
{
private:
	sf::RenderWindow &Window;	//referencja do okna
	sf::Image bgimg;		//t³o
	sf::Sprite background;	//t³o
	sf::Font TextFont;		//czcionka tekstu
	sf::Text Option1;		//tekst "1 gracz"
	sf::Text Option2;		//text "2 graczy"
	sf::Text Level;			//text "Poziom: "
	sf::Text LevelId;		//text numeru poziomu
	bool &isMenu;

public:
	menu(std::string, sf::RenderWindow &, bool &ismenu);	//k-tor
	bool initMenu(int &level, int &mode);
	~menu()	//d-tor
	{
	}
};
#endif