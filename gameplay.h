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
	sf::Text Pts1Text;			//tekst punkt�w gracza 1
	sf::Text Pts2Text;			//tekst punkt�w gracza 2
	sf::Text life1text;			//tekst �ycia gracza 1
	sf::Text life2text;			//tekst �ycia gracza 2
	sf::Text leveltext;			//tekst numeru planszy
	sf::Text infotext;			//tekst informacyjny

	int time;					//czas gry w sekundach
	int tanks;					//ile czo�g�w zosta�o do ko�ca planszy (do pojawienia si� - dekrementacja co utworzenie nowego czo�gu na planszy)
	int level;					//nr poziomu
	int onMap;					//ile czo�g�w jest na planszy
	player **ply;				//gracze
	opponent **opp;				//przeciwnicy
	std::ifstream *LevelFile;	//Plik wej�ciowy mapy
	map *GameMap;				//mapa
	int TypeMap[52][52];		//mapa typ�w p�l
	int CollisionMap[52][52];	//mapa kolizyjna
	int EagleStateBackup[6][8][2];	//zabezpieczenie stanu mapy kolizyjnej/typ�w w momencie os�oni�cia or�a
	int multi;					//0 = jeden gracz, 1 = 2 graczy
	int QueueCounter;			//licznik p�l czekaj�cych na wygenerowanie (przy generowaniu cz�ci zieleni)
	cord QueueMap[2704];		//mapa zieleni
	bool isPaused;				//pauza
	
	sf::Image MapShot;			//zrzut mapy (render do obrazka)
	sf::Image GreenShot;		//zrzut zieleni na mapie do obrazka
	sf::Sprite sMapShot;		//sprite do powyzszych
	sf::Sprite sGreenShot;		//dw�ch element�w
public:
	gameplay(std::string,int,int, sf::RenderWindow &, int p1lifes, int p1points, int p2lifes, int p2points);
	~gameplay();
	bool Game(bool &isMenu, int &p1lifes, int &p1points, int &p2lifes, int &p2points);
	bool ReactOnEvent(bool &isMenu, bool &gameover);	//Funkcja reaguj�ca na zdarzenia
	void Destroy(int Power, float x, float y, float r);
	sf::Image generate()	//Funkcja wczytuj�ca map� do obrazka
	{
		GreenShot.SetSmooth(false);
		int i = QueueCounter;
		while(i)
		{	//wywo�anie funkcji nak�adaj�cej grafik�
			fTab[4]->apply(GreenShot,QueueMap[i-1].GetX(),QueueMap[i-1].GetY(),QueueMap[i-1].GetTX(),QueueMap[i-1].GetTY(),i,1);
		}
		return GreenShot;
	}
	std::string getTime(int);	//Funkcja generuj�ca tekst zegara
};

#endif