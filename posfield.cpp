#include "posfield.h"

posField::posField(std::string inTab, float x, float y)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			type[i][j] = inTab[i*4+j]-'0';		//ustalenie typu w oparciu o tablicê znaków 
			pos[i][j] = new cord(y + j*10,x + i*10);	//utworzenie nowej wspó³rzêdnej w oparciu o wsp. pola i indeks tablicy
		}
}

posField::~posField()	//destruktor
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			delete pos[i][j];
}

int posField::apply(sf::Image &Img, field **fTab, int &qCount, cord *qField)
{	//na³o¿enie pól w oparciu o tablice wspó³rzêdnych na obrazek przekazany w argumencie funkcji
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			int result = fTab[type[i][j]]->apply(Img,pos[i][j]->GetX(),pos[i][j]->GetY(),i,j,qCount,0);
			if(result == 1 && qCount >= 1)	//dodanie zielonego pola do kolejki
			{
				fTab[0]->apply(Img,pos[i][j]->GetX(),pos[i][j]->GetY(),i,j,qCount,0);	//na³o¿enie zieleni
				qField[qCount-1].AssignCords(pos[i][j]->GetX(),pos[i][j]->GetY(),i,j);
			}
		}

	return 0;
}
