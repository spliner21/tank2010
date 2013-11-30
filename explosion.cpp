#include "explosion.h"

explosion::explosion(std::string pathTo)	//k-tor w oparciu o �cie�k� do katalogu z grafikami
	:ExpCounter(0), sExp()	
{
	std::string temp = pathTo;
	for(int i=1; i<=15; i++)	//p�tla generuj�ca �cie�ki do grafik i �aduj�ca je
	{
		temp += "//explosion-";
		if(i>9)
			temp += '1';
		temp += ((i%10)+'0');
		temp += ".png";
		iExp[i-1].LoadFromFile(temp);	//za�adowanie grafiki
		temp = pathTo;
	}
	sExp.SetOrigin(20.f,20.f);	//przesuni�cie �rodka grafiki "na �rodek" :D
}

bool explosion::display(sf::RenderWindow &Window)
{
	if(ExpCounter<15)	//pierwsze 15 klatek
	{
		sExp.SetImage(iExp[ExpCounter]);
		Window.Draw(sExp);
		ExpCounter++;
		return true;
	}
	else if(ExpCounter<30)	//ostatnie 15 klatek
	{
		sExp.SetImage(iExp[29-ExpCounter]);
		Window.Draw(sExp);
		ExpCounter++;
		return true;
	}
	else	//koniec eksplozji
	{
		ExpCounter = 0;
		return false;
	}
}