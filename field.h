#ifndef _FIELD_H_
#define _FIELD_H_
#include "point.h"
#include <string>

/********************************
*		klasa pola planszy		*
*	   (macierz 4x4 punkty)		*
*		p11|p12|p13|p14			*
*		---------------			*
*		p21|p22|p23|p24			*
*		---------------			*
*		p31|p32|p33|p34			*
*		---------------			*
*		p41|p42|p43|p44			*
*								*
*********************************/
class field
{
private:
	point *pField[4][4];		//tablica punktów pola

public:
	field();	//k-tor domyœlny
	field(int, std::string);						//konstruktor w oparciu o numer(typ pola) i œcie¿kê do katalogu z grafikami
	~field();	//d-tor
	int apply(sf::Image &, float, float, int, int, int &, int);				//funkcja nak³adaj¹ca na grafikê

};
#endif