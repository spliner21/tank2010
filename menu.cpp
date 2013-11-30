#include "menu.h"

menu::menu(std::string path, sf::RenderWindow &WindowRef, bool &ismenu)
	:Window(WindowRef), isMenu(ismenu)
{
	TextFont.LoadFromFile("font.ttf");		//tworzenie teksów
	
	bgimg.LoadFromFile("gfx//ui-bg.png");	//t³o
	background.SetImage(bgimg);
	background.SetPosition(0.f,0.f);

	Option1.SetFont(TextFont);				//tekst opcji 1 gracz
	Option1.SetColor(sf::Color(255,255,128));
	Option1.SetCharacterSize(12);
	Option1.SetPosition(240.f,300.f);
	Option1.SetString("1 Gracz");
	
	Option2.SetFont(TextFont);				//tekst opcji 2 graczy
	Option2.SetColor(sf::Color(128, 128, 128));
	Option2.SetCharacterSize(12);
	Option2.SetPosition(240.f,320.f);
	Option2.SetString("2 Graczy");
	
	Level.SetFont(TextFont);				//tekst opcji poziomu
	Level.SetColor(sf::Color(128, 128, 128));
	Level.SetCharacterSize(12);
	Level.SetPosition(240.f,380.f);
	Level.SetString("Poziom (    )");
	
	LevelId.SetFont(TextFont);
	LevelId.SetColor(sf::Color(128, 128, 128));
	LevelId.SetCharacterSize(12);
	LevelId.SetPosition(330.f,380.f);
	Window.SetFramerateLimit(10);
}

bool menu::initMenu(int &level, int &mode)
{
	std::string leveltxt;
	level = 1;
	while(isMenu)
	{
		sf::Event Event;
		Window.PollEvent(Event);	
		if(Event.Type == sf::Event::KeyPressed)		//reakcja na pojedyncze naciœniêcie - Event - zdarzenie
		{	
			if(Event.Key.Code == sf::Key::Escape)	//klawisz wyjœcia
			{
				Window.Close();
				return false;
			}
			else if(Event.Key.Code == sf::Key::Up)		//strza³ki
			{
				Option1.SetColor(sf::Color(255,255,128));
				Option2.SetColor(sf::Color(128, 128, 128));
				mode = 0;
			}
			else if(Event.Key.Code == sf::Key::Down)
			{
				Option1.SetColor(sf::Color(128, 128, 128));
				Option2.SetColor(sf::Color(255,255,128));
				mode = 1;
			}
			else if(Event.Key.Code == sf::Key::Left)		//strza³ki
			{
				level = (level-1)%10;
				if(level<0)
					level = 9;
			}
			else if(Event.Key.Code == sf::Key::Right)
				level = (level+1)%10;
			else if(Event.Key.Code == sf::Key::Return)
			{
				isMenu = false;
				--level;
				return true;
			}
		}
		else if(Event.Type == sf::Event::Closed)	//reakcja na przycisk [x] - zamkniêcie okna
		{
			Window.Close();
			return false;
		}
		Window.Draw(background);	//wyœwietlanie menu
		Window.Draw(Option1);
		Window.Draw(Option2);
		Window.Draw(Level);
		leveltxt = (level/10+'0');
		leveltxt += (level%10+'0');
		LevelId.SetString(leveltxt);
		Window.Draw(LevelId);
		Window.Display();
	}
	return true;
}