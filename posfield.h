#ifndef _POS_H_
#define _POS_H_

#include "field.h"
#include <string>

/********************************
*		klasa wsp�rz�dnych		*
*********************************/
class cord
{
private:
	float x;	//wsp�rz�dne
	float y;
	int tx;
	int ty;
public:
	cord()	//k-tory
		:x(0),y(0),tx(0),ty(0)
	{
	}
	cord(float cx,float cy)
		:x(cx),y(cy)
	{
	}
	void AssignCords(float cx, float cy,int tpx, int tpy)
	{	//funkcja przypisuj�ca
		x = cx;
		y = cy;
		tx = tpx;
		ty = tpy;
	}
	float GetX()	//funkcje zwracaj�ce warto�ci p�l sk�adowych
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	int GetTX()
	{
		return tx;
	}
	int GetTY()
	{
		return ty;
	}

};
class posField
{
private:
	cord *pos[4][4];	//tablica wsp�rz�dnych
	int type[4][4];		//tablica typ�w
public:
	posField(std::string, float, float);		//k-tory
	posField()
	{
	}
	~posField();	//d-tor
	int apply(sf::Image &, field **, int &, cord *);	//funkcja nak�adaj�ca grafiki na obraz mapy
	int ReturnType(int i, int j)	//funkcja zwracaj�ca typ pola o wsp. i,j w polu
	{
		return type[i][j];
	}
};

#endif