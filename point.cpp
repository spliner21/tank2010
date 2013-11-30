#include "point.h"

int point::apply(sf::Image &Img, int &qCount, int mode)		//Funkcja nak�adaj�ca punkt na obraz przekazywany przez referencj�
{															//(dzia�anie zale�ne od rodzaju pola i trybu)
	if(FieldType != 4)										
	{	//nak�adanie normalne - pole nie jest zieleni�
		Img.Copy(iPoint,int(sPoint.GetPosition().x),int(sPoint.GetPosition().y),sf::IntRect(0,0,0,0),false);
		return 0;
	}
	else if(FieldType == 4 && mode == 0)
	{	//dodawanie zieleni do kolejki
		qCount++;
		return 1;
	}
	else
	{	//nak�adanie zieleni
		qCount--;
		Img.Copy(iPoint,int(sPoint.GetPosition().x),int(sPoint.GetPosition().y),sf::IntRect(0,0,10,10),false);
		return 0;
	}
}
point::point()			//k-tor domy�lny
	:FieldType(0)
{
}

point::point(const point *p)	//k-tor w oparciu o drugi punkt przekazywany przez wska�nik
	:FieldType(p->FieldType)
{
	sPoint.SetImage(p->iPoint);
}

point::point(const std::string img, int FType)	//k-tor w oparciu o adres do obrazu i identyfikator rodzaju pola
	:FieldType(FType), pathPoint(img)
{
	iPoint.LoadFromFile(img);
	iPoint.SetSmooth(false);
	sPoint.SetImage(iPoint);
}

point::point(const point *p, float x, float y)	//k-tor w oparciu o wska�nik na punkt i zmienne wsp�rz�dnych x i y
{
	point::point(p);
	this->sPoint.SetPosition(x,y);
}
