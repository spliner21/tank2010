#ifndef _POINT_H_
#define _POINT_H_
#include "includes.h"

/********************************
*	klasa pojedynczego punktu	*
*********************************/
class point		
{
private:
	std::string pathPoint;	//�cie�ka do pliku graficznego
	int FieldType;			//Typ pola
	sf::Image iPoint;	//grafika
	sf::Sprite sPoint;	//Pole zawieraj�ce parametry obiektu (wymiary, pozycja, rozmiar, itd.)

public:
	point();				//k-tory
	point(const point *);
	point(const std::string, int);
	point(const point *, float, float);
	~point()
	{			//d-tor
	}
	int apply(sf::Image &, int &, int);				//funkcja nak�adaj�ca na grafik�
	void setPos(float x, float y)
	{
		sPoint.SetPosition(x,y);
	}

};
#endif