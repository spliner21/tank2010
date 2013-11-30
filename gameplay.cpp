#include "gameplay.h"

gameplay::gameplay(std::string pathTo,int level, int mode, sf::RenderWindow &WindowRef, 
	int p1lifes, int p1points, int p2lifes, int p2points)	//k-tor w oparciu o wszystkie wymagane parametry
	:time(0),tanks(20),level(1), container(pathTo),QueueCounter(0), onMap(0), Window(WindowRef),multi(mode),isPaused(false), bonus("gfx")
{
	std::string levelId = "levels//level";	//tworzenie �cie�ki
	levelId += (level+'0');
	levelId += ".txt";
	MapShot.Create(520,520);
	GreenShot.Create(520,520,sf::Color(0,0,0,0));
	LevelFile = new std::ifstream(levelId,std::ifstream::in);	//wczytanie pliku z plansz�

	try
	{
		GameMap = new map(*LevelFile,pathTo);	//pr�bujemy wygenerowa� map� na podstawie pliku wej�ciowego
	}
	catch(const char* errorTxt)
	{
		std::cout << errorTxt << ": \"" << levelId << "\". Reason: FILE NOT EXISTS" << std::endl;	//je�li si� nie uda�o, to rzucamy wyj�tkiem
		delete LevelFile;
		LevelFile = new std::ifstream("levels//level1.txt",std::ifstream::in);	//i otwieramy plansze nr 1
		GameMap = new map(*LevelFile,pathTo);
		std::cout << "\"levels//level1.txt\" Opened." << std::endl;
	}
	LevelFile->close();

	for(int i=0; i<52; i++)
	{	//p�tla tworz�ca i wype�niaj�ca map� kolizji
		for(int j=0; j<52; j++)
		{
			TypeMap[i][j] = GameMap->ReturnType(i,j);
			CollisionMap[i][j] = TypeMap[i][j];
			if(CollisionMap[i][j] == 3 || CollisionMap[i][j] == 4)	//usuni�cie trawy i lodu z mapy kolizji
				CollisionMap[i][j] = 0;
		}
	}
	MapShot.SetSmooth(false);
	GameMap->apply(MapShot,fTab,QueueCounter,QueueMap);	//generowanie mapy
	sMapShot.SetImage(MapShot);
	sMapShot.SetPosition(MAPXPOS,MAPYPOS);

	generate();		//generowanie cz�ci zielonej mapy
	sGreenShot.SetImage(GreenShot);
	sGreenShot.SetPosition(MAPXPOS,MAPYPOS);

	ply = new player*[1+multi];
	ply[0] = new player(pathTo,180.f+MAPXPOS,500.f+MAPYPOS,1,5,1,p1lifes,0,p1points);		//tworzenie graczy
	ply[0]->fill(CollisionMap,1);
	if(multi == 1)
	{
		ply[1] = new player(pathTo,340.f+MAPXPOS,500.f+MAPYPOS,1,5,1,p2lifes,1,p2points);
		ply[1]->fill(CollisionMap,1);
	}

	opp = new opponent*[4+2*multi];
	opp[0] = new opponent(pathTo,20.f+MAPXPOS,20.f+MAPYPOS,1,5,1,100,0);		//tworzenie przeciwnik�w
	opp[1] = new opponent(pathTo,260.f+MAPXPOS,20.f+MAPYPOS,2,2,1,200,1);
	opp[2] = new opponent(pathTo,500.f+MAPXPOS,20.f+MAPYPOS,1,8,1,300,2);
	opp[3] = new opponent(pathTo,20.f+MAPXPOS,20.f+MAPYPOS,3,5,1,400,3);
	if(multi == 1)
	{
		opp[4] = new opponent(pathTo,260.f+MAPXPOS,20.f+MAPYPOS,2,2,0,200,4);
		opp[5] = new opponent(pathTo,500.f+MAPXPOS,20.f+MAPYPOS,1,8,0,300,5);
	}
	/****** tworzenie teks�w *******/
	TextFont.LoadFromFile("font.ttf");	
	TimerText.SetFont(TextFont);	//zegar
	TimerText.SetColor(sf::Color(128, 128, 128));
	TimerText.SetCharacterSize(12);
	TimerText.SetPosition(470.f,10.f);

	Pts1Text.SetFont(TextFont);	//punkty gracza 1
	Pts1Text.SetColor(sf::Color(128, 128, 128));
	Pts1Text.SetCharacterSize(12);
	Pts1Text.SetPosition(150.f,10.f);
		
	Pts2Text.SetFont(TextFont);	//punkty gracza 2
	Pts2Text.SetColor(sf::Color(128, 128, 128));
	Pts2Text.SetCharacterSize(12);
	Pts2Text.SetPosition(250.f,10.f);

	life1text.SetFont(TextFont);	//�ycia gracza 1
	life1text.SetColor(sf::Color(128, 128, 128));
	life1text.SetCharacterSize(12);
	life1text.SetPosition(620.f,125.f);
	
	life2text.SetFont(TextFont);	//�ycia gracza 2
	life2text.SetColor(sf::Color(128, 128, 128));
	life2text.SetCharacterSize(12);
	life2text.SetPosition(660.f,125.f);
	
	leveltext.SetFont(TextFont);	//text nr-u planszy
	leveltext.SetColor(sf::Color(128, 128, 128));
	leveltext.SetCharacterSize(12);
	leveltext.SetPosition(740.f,125.f);
	std::string temp;
	temp = char((level/10)+'0');
	temp += ((level%10)+'0');
	leveltext.SetString(temp);

	infotext.SetFont(TextFont);	//napis na ko�cu gry
	infotext.SetColor(sf::Color(0, 0, 0));
	infotext.SetCharacterSize(14);
	infotext.SetPosition(45.f,580.f);


	Window.SetFramerateLimit(30);	

}

void gameplay::Destroy(int power, float x, float y, float r)	//funkcja niszcz�ca elementy trafione na planszy
{
	int px = int(x)-MAPXPOS;	//zmienne pomocnicze w celu przyspieszenia oblicze�
	px /= 10;					//pozycja pocisku w X i Y skwantowana do kwadrat�w 10x10px
	int py = int(y)-MAPYPOS;
	py /= 10;
	int pwr = 1;
	if(power > 2)	//ustalenie mocy broni
		pwr = 2;
	sf::Image Temp;
	Temp.Create(40,40);
	switch(int(r)%180)
	{
	case 0:	//je�eli pocisk lecia� w g�r� lub w d�
		if(TypeMap[py][px] <= pwr && TypeMap[py][px] != 0)	//sprawdzanie po kolei 4-ech p�
		{
			if(TypeMap[py][px+1] <= pwr)
			{
				if(TypeMap[py][px-1] <= pwr)
				{
					if(TypeMap[py][px-2] <= pwr)
					{
						MapShot.Copy(Temp,px*10-20,py*10,sf::IntRect(0,0,40,10));	//4 pola zniszczalne
						CollisionMap[py][px-2] = 0;
						TypeMap[py][px-2] = 0;
					}
					else 
						MapShot.Copy(Temp,px*10-10,py*10,sf::IntRect(0,0,30,10));	//3 pola
					CollisionMap[py][px-1] = 0;
					TypeMap[py][px-1] = 0;
				}
				else
					MapShot.Copy(Temp,px*10,py*10,sf::IntRect(0,0,20,10));	//2 pola
				CollisionMap[py][px+1] = 0;
				TypeMap[py][px+1] = 0;
			}
			else
				MapShot.Copy(Temp,px*10,py*10,sf::IntRect(0,0,10,10));	//1 pole
			CollisionMap[py][px] = 0;
			TypeMap[py][px] = 0;
		}
		else if(TypeMap[py][px-1] <= pwr && TypeMap[py][px-1] != 0)	//sprawdzamy 2 pola, je�li pierwsze z wcze�niej sprawdzonych nie by�o zniszczalne
		{
			if(TypeMap[py][px-2] <= pwr)
			{
				MapShot.Copy(Temp,px*10-20,py*10,sf::IntRect(0,0,20,10));
				CollisionMap[py][px-2] = 0;
				TypeMap[py][px-2] = 0;
			}
			else
				MapShot.Copy(Temp,px*10-10,py*10,sf::IntRect(0,0,10,10));
			CollisionMap[py][px-1] = 0;
			TypeMap[py][px-1] = 0;
		}
		break;
	case 90:	//j.w. tylko dla kierunku w lewo/w prawo
		if(TypeMap[py][px] <= pwr && TypeMap[py][px] != 0)
		{
			if(TypeMap[py+1][px] <= pwr)
			{
				if(TypeMap[py-1][px] <= pwr)
				{
					if(TypeMap[py-2][px] <= pwr)
					{
						MapShot.Copy(Temp,px*10,py*10-20,sf::IntRect(0,0,10,40));
						CollisionMap[py-2][px] = 0;
						TypeMap[py-2][px] = 0;
					}
					else 
						MapShot.Copy(Temp,px*10,py*10-10,sf::IntRect(0,0,10,30));
					CollisionMap[py-1][px] = 0;
					TypeMap[py-1][px] = 0;
				}
				else
					MapShot.Copy(Temp,px*10,py*10,sf::IntRect(0,0,10,20));
				CollisionMap[py+1][px] = 0;
				TypeMap[py+1][px] = 0;
			}
			else
				MapShot.Copy(Temp,px*10,py*10,sf::IntRect(0,0,10,10));
			CollisionMap[py][px] = 0;
			TypeMap[py][px] = 0;
		}
		else if(TypeMap[py-1][px] <= pwr && TypeMap[py-1][px] != 0)
		{
			if(TypeMap[py-2][px] <= pwr)
			{
				MapShot.Copy(Temp,px*10,py*10-20,sf::IntRect(0,0,10,20));
				CollisionMap[py-2][px] = 0;
				TypeMap[py-2][px] = 0;
			}
			else
				MapShot.Copy(Temp,px*10-10,py*10,sf::IntRect(0,0,10,10));
			CollisionMap[py-1][px] = 0;
			TypeMap[py-1][px] = 0;
		}
		break;
	}
}

std::string gameplay::getTime(int fps)
{
	std::string temporary;			//generuje czas gry do �a�cucha string
	temporary += ((fps/18000)%10) + '0';
	temporary += ((fps/1800)%10) + '0';
	temporary += ":";
	temporary += ((fps/ 300)%6) + '0';
	temporary += ((fps/ 30)%10) + '0';
	return temporary;
}

bool gameplay::ReactOnEvent(bool &isMenu, bool &gameover)
{
	float x,y,r; //zmienne pomocnicze

	const sf::Input & GameInput = Window.GetInput(); //zmienna wej�cia (reakcja na klawisze ci�g�e)
	if(ply[0]->AmI() > 0 && !ply[0]->AmIDestroyed())
	{
		if(GameInput.IsKeyDown(sf::Key::W))		//sprawdzanie strza�ek
		{			//funkcja ruchu - przyjmuje wsp�rz�dne i mape typ�w
			ply[0]->move(0,1,CollisionMap,TypeMap,BonusMap);	
		}
		else if(GameInput.IsKeyDown(sf::Key::S))
		{
			ply[0]->move(0,-1,CollisionMap,TypeMap,BonusMap);
		}
		else if(GameInput.IsKeyDown(sf::Key::A))
		{
			ply[0]->move(-1,0,CollisionMap,TypeMap,BonusMap);
		}
		else if(GameInput.IsKeyDown(sf::Key::D))
		{
			ply[0]->move(1,0,CollisionMap,TypeMap,BonusMap);
		}
		else ply[0]->slide(CollisionMap,TypeMap,BonusMap);
		if(GameInput.IsKeyDown(sf::Key::Space))	//strza�
		{
			if(!(ply[0]->AmIDestroyed()))
			{
				x=ply[0]->GetX();
				y=ply[0]->GetY();
				r=ply[0]->GetRotation();
				ply[0]->shot(x,y,r,CollisionMap);
			}
		}
	}
	if(multi == 1 && ply[1]->AmI() > 0 && !ply[1]->AmIDestroyed())
	{
		if(GameInput.IsKeyDown(sf::Key::Up))		//sprawdzanie strza�ek
		{		//funkcja ruchu - przyjmuje wsp�rz�dne i mape typ�w
			ply[1]->move(0,1,CollisionMap,TypeMap,BonusMap);
		}
		else if(GameInput.IsKeyDown(sf::Key::Down))
		{
			ply[1]->move(0,-1,CollisionMap,TypeMap,BonusMap);
		}
		else if(GameInput.IsKeyDown(sf::Key::Left))	
		{
			ply[1]->move(-1,0,CollisionMap,TypeMap,BonusMap);
		}
		else if(GameInput.IsKeyDown(sf::Key::Right))
		{
			ply[1]->move(1,0,CollisionMap,TypeMap,BonusMap);
		}
		else ply[1]->slide(CollisionMap,TypeMap,BonusMap);
		if(GameInput.IsKeyDown(sf::Key::Return))	//strza�
		{
			if(!(ply[1]->AmIDestroyed()))
				ply[1]->shot(ply[1]->GetX(),ply[1]->GetY(),ply[1]->GetRotation(),CollisionMap);
		}
	}
	sf::Event Event;			//zdarzenie
	Window.PollEvent(Event);
	if(Event.Type == sf::Event::KeyPressed)		//reakcja na pojedyncze naci�ni�cie - Event - zdarzenie
	{	
		if(Event.Key.Code == sf::Key::P)		//klawisz pauzy
		{
			isPaused = !isPaused;
		}
		else if(Event.Key.Code == sf::Key::Escape)	//klawisz [Esc]
		{
			isMenu = true;
			gameover = true;
			return true;
		}
	}
	else if(Event.Type == sf::Event::Closed)	//reakcja na przycisk [x] - zamkni�cie okna
	{
		Window.Close();
		isMenu = false;
		return false;
	}
	return true;
}

bool gameplay::Game(bool &isMenu, int &p1lifes, int &p1points, int &p2lifes, int &p2points)
{
	int fps=0;			//zmienne pomocnicze
	int shooted = 0;
	int i, pts;
	int isEagleProtected = 0;
	int OppImmobilizeTimer = 0;	//licznik zatrzymania przeciwnik�w
	bool returnable = true;
	bool gameover = false;
	bool eagleDestroyed = false;
	ply[0]->respawn(CollisionMap);	//spawn startowy graczy
	if(multi == 1)
		ply[1]->respawn(CollisionMap);
	while(Window.IsOpened() && tanks > 0 && gameover == false)
	{
		
		if(!isPaused)
		{		
			returnable = ReactOnEvent(isMenu,gameover);				//wywo�anie reakcji na klawisze
			if(gameover)	//przerwanie gry - [esc]
				break;
			if(((++fps)%30)==0 && onMap < 4+2*multi)
					opp[onMap++]->respawn(CollisionMap);	//spawn startowy przeciwnika
			Window.Draw(sUiBg);			//t�o
			Window.Draw(sMapShot);		//wy�wietlenie dolnej cz�ci planszy
			gameover = true;
			for(i=0; i<(multi+1); i++)
			{							//p�tla obs�ugi dzia�a� graczy
				if(ply[i]->AmI() > 0)
				{	
					gameover = false;
					ply[i]->display(Window, CollisionMap);		//wy�wietlenie
					if(ply[i]->checkBonus())
					{
						switch(bonusType)
						{
						case 1:	//Czo�g � 1, He�m � 2, Granat � 3, Gwiazda � 4, Zegar � 5, �opata - 6, Pistolet - 7, Statek - 8.
							ply[i]->AddLife();		//bonus dodatkowego �ycia
							break;
						case 2:
							ply[i]->Protect();	//os�ona
							break;
						case 3:	//bonus zniszczenia wszystkich przeciwnikow na planszy
							int temp;
							for(int j = 0; j<onMap; j++)
							{
								temp = opp[j]->hit(CollisionMap,3);
								if(temp != 0)
									--tanks;
								temp = 0;								
							}
							break;
						case 4:	//bonus zwi�kszenia mocy broni
							ply[i]->IncreasePower(0);	
							break;
						case 5:	//15 sekund zatrzymania przeciwnika
							OppImmobilizeTimer = 450;	
							break;
						case 6:	//bonus os�ony or�a
							for(int j=0;j<8;j++)
							{
								for(int k=0;k<6;k++)
								{
									EagleStateBackup[k][j][0] = CollisionMap[k+46][j+22];
									EagleStateBackup[k][j][1] = TypeMap[k+46][j+22];
									CollisionMap[k+46][j+22] = 2;
									TypeMap[k+46][j+22] = 2;
								}
							}
							isEagleProtected = 450;
							break;
						case 7:
							ply[i]->IncreasePower(1);	//bonus zwi�kszenia mocy broni (2x mocniejszy ni� bonus 4)
							ply[i]->incrementPower();
							break;
						case 8:
							ply[i]->MakeAmphibia();	//os�ona i zdolno�� przep�ywania nad wod�
							break;
						default:
							break;
						}
						clear();
						ply[i]->AddPoints(500);
					}
					if(ply[i]->AmIarmed())
					{	//obs�uga wystrzelonego pocisku
						shooted = ply[i]->moveBullet(TypeMap,CollisionMap);
						if(shooted>=10 && shooted <20)
						{	//obs�uga trafienia przeciwnika
							pts = opp[shooted-10]->hit(CollisionMap,1);
							if(pts > 0)
							{
								ply[i]->AddPoints(pts);
								if(tanks%3 == 0)
									GenerateBonus();
							}
						}
						else if(shooted==1 || shooted==2)
						{	//obs�uga trafienia 
							Destroy(ply[i]->ReturnPwr(),ply[i]->ReturnBullet().GetPosition().x,
								ply[i]->ReturnBullet().GetPosition().y,ply[i]->ReturnBullet().GetRotation());
						}
						else if(shooted == 6)	//trafienie or�a
						{
							gameover = true;
							eagleDestroyed = true;
						}
						if(ply[i]->AmIarmed())	//wy�wietlanie pocisku
							Window.Draw(ply[i]->ReturnBullet());
						shooted = 0;
					}
				}
			}

			for(i = 0; i < onMap; i++)
			{	//p�tla obs�ugi przeciwnika	
				if(!opp[i]->AmIDestroyed())
				{
					if(OppImmobilizeTimer == 0)
						opp[i]->move(CollisionMap,TypeMap,BonusMap);	//wywo�anie funkcji losuj�cej ruch
					else
						opp[i]->fill(CollisionMap,1);	//wype�nienie planszy w miejscu w kt�rym jest przeciwnik
				}
				if(opp[i]->AmIarmed())
				{	//obs�uga pocisku
					shooted = opp[i]->moveBullet(TypeMap,CollisionMap);
					if(shooted == 20 || shooted == 21)
					{	//obs�uga trafienia
						ply[shooted-20]->hit(CollisionMap);
					}
					else if(shooted==1 || shooted==2)
					{	//obs�uga trafienia
						Destroy(opp[i]->ReturnPwr(),opp[i]->ReturnBullet().GetPosition().x,
							opp[i]->ReturnBullet().GetPosition().y,opp[i]->ReturnBullet().GetRotation());
					}
					else if(shooted == 6)	//trafienie w or�a
					{
						gameover = true;
						eagleDestroyed = true;
					}
					if(opp[i]->AmIarmed())	//wy�wietlanie lec�cego pocisku
						Window.Draw(opp[i]->ReturnBullet());
					shooted = 0;
				}
				else if((fps%30)==0 && !(opp[i]->AmIDestroyed()) && OppImmobilizeTimer == 0)	
					//strza�, przeciwnicy strzelaj� o pe�nej sekundzie je�li mog�
					opp[i]->shot(opp[i]->GetX(),opp[i]->GetY(),opp[i]->GetRotation(),CollisionMap);
				opp[i]->display(Window, CollisionMap,tanks);
			}

			i = 0;
			while(i< (((tanks-onMap)>0)?(tanks-onMap):0))	//wy�wietlanie listy czo�g�w przeciwnika do ko�ca gry
				Window.Draw(smallTanks[i++]);
			OppImmobilizeTimer -= ( (OppImmobilizeTimer == 0) ? 0 : 1);	//licznik bonusu unieruchomienia przeciwnika
			Window.Draw(sGreenShot);		//wy�wietlenie zieleni na mapie

			TimerText.SetString(getTime(fps));	//wy�wietlanie punkt�w i ilo�ci �y�
			Pts1Text.SetString(ply[0]->GetPoints("I"));	//punkty gracza 1
			Window.Draw(Pts1Text);
			life1text.SetString(ply[0]->GetLifes("I"));	//�ycia gracza 1
			Window.Draw(life1text);
			if(multi == 1)	//je�li jest drugi gracz
			{
				Pts2Text.SetString(ply[1]->GetPoints("II"));	//wy�wietlenie punkt�w gracza 2
				Window.Draw(Pts2Text);
				life2text.SetString(ply[1]->GetLifes("II"));	//i �y� gracza 2
				Window.Draw(life2text);
			}
			Window.Draw(TimerText);
			Window.Draw(leveltext);
			if(isBonus())
				displayBonus(Window);
			if(isEagleProtected>0)		//obs�uga bonusu nr 6 - os�ony na or�a
			{
				Window.Draw(sEagleProtection);	//wy�wietlenie os�ony nad or�em
				--isEagleProtected;	//dekrementacja licznika czasu wy�wietlenia os�ony
				if(isEagleProtected == 0)	//je�eli koniec, to odtwarzamy map� kolizji i typ�w w cz�ci z or�em
				{
					for(int j=0;j<8;j++)
						for(int k=0;k<6;k++)
						{
							CollisionMap[k+46][j+22] = EagleStateBackup[k][j][0];
							TypeMap[k+46][j+22] = EagleStateBackup[k][j][1];

						}
				}
			}
			Window.Display();				//wyrzucenie wy�wietlonych rzeczy na ekran
		}
		else
		{
			sf::Event Event;			//zdarzenie
			Window.PollEvent(Event);	
			if(Event.Type == sf::Event::KeyPressed)		//reakcja na pojedyncze naci�ni�cie - Event - zdarzenie
			{	
				if(Event.Key.Code == sf::Key::P)		//klawisz pauzy
					isPaused = !isPaused;
				else if(Event.Key.Code == sf::Key::Escape)	//klawisz [Esc]
				{
					isMenu = true;
					gameover = true;
					return true;
				}
			}
			else if(Event.Type == sf::Event::Closed)	//reakcja na przycisk [x] - zamkni�cie okna
			{
				Window.Close();
				isMenu = false;
				return false;
			}
		}

	}
	if(eagleDestroyed == true)	//je�eli trafiono or�a, to wy�wietlamy jego zniszczon� wersj�
	{
		sf::Image destroyedEagle;
		destroyedEagle.LoadFromFile("gfx//d_eagle.png");
		destroyedEagle.SetSmooth(false);
		sf::Sprite sDEagle;
		sDEagle.SetImage(destroyedEagle);
		sDEagle.SetPosition(240.f+MAPXPOS,480.f+MAPYPOS);
		Window.Draw(sDEagle);
	}
	if(Window.IsOpened())
	{
		if(tanks <= 0)	//ekran ko�cowy
		{
			EndScreen.LoadFromFile("gfx//victory.png");	//przej�cie do nast�pnej planszy
			isMenu = false;
			p1lifes = ply[0]->AmI();	//zapisywanie stanu gry
			p1points = ply[0]->AddPoints(0);
			if(multi == 1)
			{	
				p2lifes = ply[1]->AmI();
				p2points = ply[1]->AddPoints(0);
			}
			infotext.SetString("nacisnij (enter) by przejsc dalej...");
		}
		else
		{
			EndScreen.LoadFromFile("gfx//lose.png");	//koniec gry - przej�cie do menu
			isMenu = true;
			infotext.SetString("nacisnij (enter) by przejsc do menu...");
		}
		sEndScreen.SetImage(EndScreen);	//wy�wietlanie GAME OVER, lub ZWYCI�STWO
		Window.Draw(sEndScreen);
		Window.Display();
		sf::Sleep(2000);	//2 sekundy przerwy - bufor, aby nie by�o przypadkowego naci�ni�cia klawisza
		Window.Draw(sEndScreen);
		Window.Draw(infotext);
		Window.Display();

		bool isEnter = false;
		while(!isEnter)		//czekanie na enter
		{
			sf::Event Event;			//zdarzenie
			Window.PollEvent(Event);	
			if(Event.Type == sf::Event::Closed)	//reakcja na zamkni�cie okna oraz enter
			{
				Window.Close();
				returnable = false;
				isEnter = true;
			}	
			else if((Event.Type = sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
			{
				isEnter = true;
			}
		}
		return returnable;
	}
	else return false;
}
gameplay::~gameplay()	//d-tor
{
	delete LevelFile;
	delete GameMap;
	delete ply[0];
	delete opp[0];
	delete opp[1];
	delete opp[2];
	delete opp[3];
	if(multi == 1)
	{
		delete ply[1];
		delete opp[4];
		delete opp[5];
	}
	delete[] ply;
	delete[] opp;
}

