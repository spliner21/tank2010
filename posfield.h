#ifndef _POS_H_
#define _POS_H_

#include "field.h"
#include <string>

/********************************
*		klasa wspó³rzêdnych		*
*********************************/
class cord
{
private:
	float x;	//wspó³rzêdne
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
	{	//funkcja przypisuj¹ca
		x = cx;
		y = cy;
		tx = tpx;
		ty = tpy;
	}
	float GetX()	//funkcje zwracaj¹ce wartoœci pól sk³adowych
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
	cord *pos[4][4];	//tablica wspó³rzêdnych
	int type[4][4];		//tablica typów
public:
	posField(std::string, float, float);		//k-tory
	posField()
	{
	}
	~posField();	//d-tor
	int apply(sf::Image &, field **, int &, cord *);	//funkcja nak³adaj¹ca grafiki na obraz mapy
	int ReturnType(int i, int j)	//funkcja zwracaj¹ca typ pola o wsp. i,j w polu
	{
		return type[i][j];
	}
};

#endif