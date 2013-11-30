#include "bonus.h"

bonus::bonus(std::string path)	//konstruktor w oparciu o œcie¿kê do katalogu grafik
{
	posId[0] = 0;
	posId[1] = 0;
	std::string tmp = path;
	for(int i=0;i<52;i++)	//wyczyszczenie mapy bonusów 
		for(int j=0;j<52;j++)
			BonusMap[i][j]=0;
	bonusType = 0;
	for(int i = 0; i<8;i++)
	{	//za³adowanie grafik bonusów
		tmp+="//bonus-";
		tmp+=(i+'0');
		tmp+=".png";
		iBonus[i].LoadFromFile(tmp);
		tmp=path;
	}
}

void bonus::GenerateBonus()
{	//losowanie bonusu
	clear();
	bonusCounter = 300;	//inicjalizacja czasu
	bonusType = std::rand()%8+1;	//losowanie bonusu z zakresu 1-8
	posId[0] = 26+int((double(std::rand()%2)-0.5)*(16.f*double(std::rand()%2+1.f)));	//losowanie pozycji
	posId[1] = 26+int((double(std::rand()%2)-0.5)*(16.f*double(std::rand()%2+1.f)));
	sBonus.SetImage(iBonus[bonusType-1]);	//ustawienie obrazka
	sBonus.SetPosition(float(posId[0]*10+MAPXPOS),float(posId[1]*10+MAPYPOS));
	for(int i = posId[0]; i < posId[0]+4; i++)	//wype³enienie mapy bonusów
		for(int j  = posId[1]; j < posId[1]+4; j++)
			BonusMap[j][i] = 1;
}

void bonus::clear()
{
	for(int i = posId[0];i<posId[0]+4;i++)
		for(int j = posId[1];j<posId[1]+4;j++)
			BonusMap[j][i] = 0;
	bonusType = 0;
}