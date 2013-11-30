#include "point.h"

int point::apply(sf::Image &Img, int &qCount, int mode)		//Funkcja nak³adaj¹ca punkt na obraz przekazywany przez referencjê
{															//(dzia³anie zale¿ne od rodzaju pola i trybu)
	if(FieldType != 4)										
	{	//nak³adanie normalne - pole nie jest zieleni¹
		Img.Copy(iPoint,int(sPoint.GetPosition().x),int(sPoint.GetPosition().y),sf::IntRect(0,0,0,0),false);
		return 0;
	}
	else if(FieldType == 4 && mode == 0)
	{	//dodawanie zieleni do kolejki
		qCount++;
		return 1;
	}
	else
	{	//nak³adanie zieleni
		qCount--;
		Img.Copy(iPoint,int(sPoint.GetPosition().x),int(sPoint.GetPosition().y),sf::IntRect(0,0,10,10),false);
		return 0;
	}
}
point::point()			//k-tor domyœlny
	:FieldType(0)
{
}

point::point(const point *p)	//k-tor w oparciu o drugi punkt przekazywany przez wskaŸnik
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

point::point(const point *p, float x, float y)	//k-tor w oparciu o wskaŸnik na punkt i zmienne wspó³rzêdnych x i y
{
	point::point(p);
	this->sPoint.SetPosition(x,y);
}
