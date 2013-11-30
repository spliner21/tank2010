#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "player.h"
#include "opponent.h"
#include "map.h"
#include "bonus.h"
#include "container.h"

class gameplay: public container, public bonus
{
private:
	sf::RenderWindow &Window;	//referencja do okna
	sf::Font TextFont;			//czcionka
	sf::Text TimerText;			//tekst zegara
	sf::Text Pts1Text;			//tekst punktów gracza 1
	sf::Text Pts2Text;			//tekst punktów gracza 2
	sf::Text life1text;			//tekst ¿ycia gracza 1
	sf::Text life2text;			//tekst ¿ycia gracza 2
	sf::Text leveltext;			//tekst numeru planszy
	sf::Text infotext;			//tekst informacyjny

	int time;					//czas gry w sekundach
	int tanks;					//ile czo³gów zosta³o do koñca planszy (do pojawienia siê - dekrementacja co utworzenie nowego czo³gu na planszy)
	int level;					//nr poziomu
	int onMap;					//ile czo³gów jest na planszy
	player **ply;				//gracze
	opponent **opp;				//przeciwnicy
	std::ifstream *LevelFile;	//Plik wejœciowy mapy
	map *GameMap;				//mapa
	int TypeMap[52][52];		//mapa typów pól
	int CollisionMap[52][52];	//mapa kolizyjna
	int EagleStateBackup[6][8][2];	//zabezpieczenie stanu mapy kolizyjnej/typów w momencie os³oniêcia or³a
	int multi;					//0 = jeden gracz, 1 = 2 graczy
	int QueueCounter;			//licznik pól czekaj¹cych na wygenerowanie (przy generowaniu czêœci zieleni)
	cord QueueMap[2704];		//mapa zieleni
	bool isPaused;				//pauza
	
	sf::Image MapShot;			//zrzut mapy (render do obrazka)
	sf::Image GreenShot;		//zrzut zieleni na mapie do obrazka
	sf::Sprite sMapShot;		//sprite do powyzszych
	sf::Sprite sGreenShot;		//dwóch elementów
public:
	gameplay(std::string,int,int, sf::RenderWindow &, int p1lifes, int p1points, int p2lifes, int p2points);
	~gameplay();
	bool Game(bool &isMenu, int &p1lifes, int &p1points, int &p2lifes, int &p2points);
	bool ReactOnEvent(bool &isMenu, bool &gameover);	//Funkcja reaguj¹ca na zdarzenia
	void Destroy(int Power, float x, float y, float r);
	sf::Image generate()	//Funkcja wczytuj¹ca mapê do obrazka
	{
		GreenShot.SetSmooth(false);
		int i = QueueCounter;
		while(i)
		{	//wywo³anie funkcji nak³adaj¹cej grafikê
			fTab[4]->apply(GreenShot,QueueMap[i-1].GetX(),QueueMap[i-1].GetY(),QueueMap[i-1].GetTX(),QueueMap[i-1].GetTY(),i,1);
		}
		return GreenShot;
	}
	std::string getTime(int);	//Funkcja generuj¹ca tekst zegara
};

#endif