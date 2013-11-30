#pragma once
#include "map.h"

map::map(std::ifstream &inFile, std::string pathTo)	//k-tor
{
	if(!inFile.is_open())
	{
		throw "Unable to open file";	//rzucamy wyj�tkiem je�li plik wej�ciowy nie jest otwarty
		return;
	}
	std::string inTab;
	fMap = new posField**[13];
	for(int i=0; i<13; i++)
	{
		fMap[i] = new posField*[13];
		for(int j=0; j<13; j++)
		{
			std::getline(inFile,inTab);
			fMap[i][j] = new posField(inTab, i*40.0f, j*40.0f);	//wywo�anie konstruktora pola wsp�rz�dnych
			inTab.erase();
		}
	}
}
map::~map()	//d-tor
{
	for(int i=0; i<13; i++)
	{
		for(int j=0; j<13; j++)
				delete fMap[i][j];
		delete[] fMap[i];
	}
	delete[] fMap;
}

int map::apply(sf::Image &Img,field **fTab, int &qCount, cord *qField)	//funkcja nak�adaj�ca map� na zmienn� typu obraz
{
	for(int i=0; i<13; i++)
		for(int j=0; j<13; j++)
			fMap[i][j]->apply(Img,fTab,qCount,qField);
	return 0;
}