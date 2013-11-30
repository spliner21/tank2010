#include "main.h"

int main()
{
	sf::RenderWindow Window;	//okno
	Window.Create(sf::VideoMode(800, 600, 32), "Tank 2010 v1.0");	//ustawienia okna
	Window.SetPosition(0,0);
	int level = 0, mode = 0;	//opcje gry
	int p1l = 3, p2l = 3, p1p = 0, p2p = 0; //punkty i zycia graczy.
	bool isMenu = true, notexit = true;	//zmienne w zale¿noœci od których dzia³a gra
	while(notexit)	//g³ówna pêtla gry
	{
		if(isMenu)
		{	//czêœæ odpowiedzialna za menu
			menu mainmenu("gfx",Window,isMenu);
			notexit = mainmenu.initMenu(level,mode);
		}
		else
		{	//czêœæ odpowiedzialna za grê
			if(++level > 9)	//dopóki nie dojdziemy do planszy 9 mo¿emy awansowaæ
			{
				isMenu = true;
				break;
			}
			else
			{
				gameplay Game("gfx",level,mode,Window,(p1l==0)?1:p1l,p1p,(p2l==0)?1:p2l,p2p);
				notexit = Game.Game(isMenu,p1l,p1p,p2l,p2p);
			}
		}
	}
	return 0;
}