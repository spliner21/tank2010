#ifndef _MAP_H_
#define _MAP_H_
#include "posfield.h"
#include <fstream>

class map
{
private:
	posField ***fMap;				//tablica mapy
public:
	map(std::ifstream &, std::string);	//k-tor
	~map();	//d-tor
	int ReturnType(int i, int j)	//funkcja zwracaj�ca typ zadanego pola
	{
		return fMap[i / 4][j / 4]->ReturnType(i%4,j%4);
	}
	int apply(sf::Image &Img,field **fTab, int &qCount, cord *qField);	//funkcja nak�adaj�ca map� na zmienn� typu obraz
};

#endif