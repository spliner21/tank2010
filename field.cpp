#include "field.h"

field::field()	//k-tor domy�lny
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
			pField[i][j] = new point();
	}
}
field::~field()	//d-tor
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
			delete pField[i][j];
	}
}
field::field(int fType, std::string PathTo)	//k-tor w oparciu o typ pola i �cie�k� do pliku graficznego
{
	std::string tempString = PathTo;
	int i,j;
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)		//p�tla generuj�ca �cie�k� do grafiki
		{
			tempString += "\\";
			tempString += (fType+'0');
			tempString += "-";
			tempString += (i+'1');
			tempString += (j+'1'); 
			tempString += ".png";
			pField[i][j] = new point(tempString,fType);		//wywo�anie konstruktora pola w oparciu o �cie�k� i typ pola
			pField[i][j]->setPos(j*10.f,i*10.f);
		tempString = PathTo;
		}
	}																					 
}		

int field::apply(sf::Image &Img, float x, float y, int i, int j, int &qCount, int mode)		//funkcja nak�adaj�ca pole na obrazek
{
	int result = 1;
	pField[i][j]->setPos(x,y);	//ustalenie pozycji pola
	result = pField[i][j]->apply(Img,qCount,mode);	//wywo�anie funkcji nak�adaj�cej grafik�
	return result;
}
																								