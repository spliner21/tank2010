#include "main.h"

int main()
{
	sf::RenderWindow Window;	//okno
	Window.Create(sf::VideoMode(800, 600, 32), "Tank 2010 v1.0");	//ustawienia okna
	Window.SetPosition(0,0);
	int level = 0, mode = 0;	//opcje gry
	int p1l = 3, p2l = 3, p1p = 0, p2p = 0; //punkty i zycia graczy.
	bool isMenu = true, notexit = true;	//zmienne w zale�no�ci od kt�rych dzia�a gra
	while(notexit)	//g��wna p�tla gry
	{
		if(isMenu)
		{	//cz�� odpowiedzialna za menu
			menu mainmenu("gfx",Window,isMenu);
			notexit = mainmenu.initMenu(level,mode);
		}
		else
		{	//cz�� odpowiedzialna za gr�
			if(++level > 9)	//dop�ki nie dojdziemy do planszy 9 mo�emy awansowa�
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