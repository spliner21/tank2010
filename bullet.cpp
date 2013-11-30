#include "bullet.h"

void bullet::fill(int collmap[52][52], int type)	//wype³nienie mapy kolizji przez pocisk
{
	int x = int(sBullet.GetPosition().x);
	int y = int(sBullet.GetPosition().y);
	for(int i=-2;i<2;i++)
		for(int j=-2;j<2;j++)
		{
			if((i+x)>0 && (i+x) && (j+y)>0 && (j+y)<52)
				if(collmap[j+y][i+x] >100)
					collmap[j+y][i+x] = 0;
		}
}

int bullet::move(int TypeMap[52][52], int CollisionMap[52][52],int TypeId, int &BulletCounter)		//przesuwanie pocisku
{
	int result = 0;		//wartoœæ zwracana
	int typeId, colId;	//zmienne pomocnicze (przyspieszenie dzia³ania)
	sf::Vector2f sV = sBullet.GetPosition();
	sV.x = (sV.x-MAPXPOS)/10;
	sV.y = (sV.y-MAPYPOS)/10;
	switch(int(sBullet.GetRotation()))	//dzia³anie zale¿ne od kierunku 
	{
	case 0:	//wszystkie 4 analogicznie
		if((sBullet.GetPosition().y-BULLETSPD)>MAPYPOS)
		{
			if(CollisionMap[int(sV.y)][int(sV.x)]==300)
			{	//ju¿ ktoœ wykry³ kolizjê
				--BulletCounter;
				CollisionMap[int(sV.y)][int(sV.x)]=0;
			}
			else if(CollisionMap[int(sV.y)-1][int(sV.x)-1]>100)
			{	//detekcja mijania siê z czyimœ pociskiem
				--BulletCounter;
				CollisionMap[int(sV.y)-1][int(sV.x)-1]=300;
				CollisionMap[int(sV.y)][int(sV.x)]=0;
			}
			else if(CollisionMap[int(sV.y)+1][int(sV.x)-1]>100)
			{	//detekcja mijania siê z czyimœ pociskiem
				--BulletCounter;
				CollisionMap[int(sV.y)+1][int(sV.x)-1]=300;
				CollisionMap[int(sV.y)][int(sV.x)]=0;
			}
			else
			{	//detekcja trafienia w coœ/kogoœ
				CollisionMap[int(sV.y)][int(sV.x)]=0; //zerowanie naszej aktualnej pozycji na mapie kolizji
				sBullet.Move(0,-BULLETSPD);
				sV = sBullet.GetPosition();
				typeId = TypeMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)-1];	//dla przyspieszenia
				colId = CollisionMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)-1];
				if(typeId == 1 || typeId == 2 || typeId == 6)	//trafienie muru/skrzyni/or³a
					result = typeId;
				else if(colId > 6)
					result = colId;
				else	
				{	//j.w. tylko dla pola obok
					typeId = TypeMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
					colId = CollisionMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
					if(typeId == 1 || typeId == 2 || typeId == 6)
						result = typeId;
					else if(colId > 6)
						result = colId;
					else if(colId == 0)
						CollisionMap[int(sV.y-MAPYPOS)/10][int(sV.x-MAPXPOS)/10]=TypeId;
				}
			}
		}
		else
		{
			CollisionMap[0][int(sV.x)]=0;
			result = -1;
		}
		break;
	case 180:	//analogicznie co wy¿ej
		if((sBullet.GetPosition().y+BULLETSPD)<520+MAPYPOS)
		{
			if(CollisionMap[int(sV.y)][int(sV.x)-1]==300)
			{
				--BulletCounter;
				CollisionMap[int(sV.y)][int(sV.x)-1]=0;
			}
			else if(CollisionMap[int(sV.y)-1][int(sV.x)]>100)
			{	
				--BulletCounter;
				CollisionMap[int(sV.y)-1][int(sV.x)]=300;
				CollisionMap[int(sV.y)][int(sV.x)-1]=0;
			}
			else if(CollisionMap[int(sV.y)+1][int(sV.x)]>100)
			{
				--BulletCounter;
				CollisionMap[int(sV.y)+1][int(sV.x)]=300;
				CollisionMap[int(sV.y)][int(sV.x)-1]=0;
			}
			else
			{
				CollisionMap[int(sV.y)][int(sV.x)-1]=0;
				sBullet.Move(0,BULLETSPD);
				sV = sBullet.GetPosition();
				typeId = TypeMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
				colId = CollisionMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
				if(typeId == 1 || typeId == 2 || typeId == 6)
					result = typeId;
				else if(colId > 6)
					result = colId;
				else
				{
					typeId = TypeMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)-1];
					colId = CollisionMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)-1];
					if(typeId == 1 || typeId == 2 || typeId == 6)
						result = typeId;
					else if(colId > 6)
						result = colId;
					else if(colId == 0)
						CollisionMap[int(sV.y-MAPYPOS)/10][int(sV.x-MAPXPOS)/10-1]=TypeId;
				}
			}
		}
		else
		{
			CollisionMap[51][int(sV.x)-1]=0;
			result = -1;
		}
		break;
	case 270:
		if((sBullet.GetPosition().x-BULLETSPD)>MAPXPOS)
		{
			if(CollisionMap[int(sV.y)][int(sV.x)]==300)    //detekcja mijania siê z czyimœ pociskiem
			{	//jeœli osoba strzelaj¹ca wykry³a wczesniej
				--BulletCounter;
				CollisionMap[int(sV.y)][int(sV.x)]=0;	//zerowanie naszego pola
			}
			else if(CollisionMap[int(sV.y)-1][int(sV.x)-1]>100)
			{	//detekcja
				--BulletCounter;
				CollisionMap[int(sV.y)-1][int(sV.x)-1]=300;	//informacja dla pocisku mijanego
				CollisionMap[int(sV.y)][int(sV.x)]=0;			//zerowanie naszego pola
			}
			else if(CollisionMap[int(sV.y)-1][int(sV.x)+1]>100)
			{	//detekcja
				--BulletCounter;
				CollisionMap[int(sV.y)-1][int(sV.x)+1]=300;	//informacja dla pocisku mijanego
				CollisionMap[int(sV.y)][int(sV.x)]=0;			//zerowanie naszego pola
			}

			else
			{
				CollisionMap[int(sV.y)][int(sV.x)]=0;
				sBullet.Move(-BULLETSPD,0);							//przesuniêcie pocisku
				sV = sBullet.GetPosition();
				typeId = TypeMap[int((sV.y-MAPYPOS)/10)-1][int((sV.x-MAPXPOS)/10)];
				colId = CollisionMap[int((sV.y-MAPYPOS)/10)-1][int((sV.x-MAPXPOS)/10)];
				if(typeId == 1 || typeId == 2 || typeId == 6)
					result = typeId;
				else if(colId > 6)
					result = colId;
				else
				{
					typeId = TypeMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
					colId = CollisionMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
					if(typeId == 1 || typeId == 2 || typeId == 6)
						result = typeId;
					else if(colId > 6)
						result = colId;
					else if(colId == 0)
						CollisionMap[int(sV.y-MAPYPOS)/10][int(sV.x-MAPXPOS)/10]=TypeId;
				}
			}
		}
		else
		{
			CollisionMap[int(sV.y)][0]=0;
			result = -1;
		}
		break;
	case 90:
		if((sBullet.GetPosition().x+BULLETSPD)<520+MAPXPOS)
		{
			if(CollisionMap[int(sV.y)-1][int(sV.x)]==300)
			{
				--BulletCounter;
				CollisionMap[int(sV.y)-1][int(sV.x)]=0;
			}
			else if(CollisionMap[int(sV.y)][int(sV.x)+1]>100)
			{	//detekcja mijania siê z czyimœ pociskiem
				--BulletCounter;
				CollisionMap[int(sV.y)][int(sV.x)+1]=300;
				CollisionMap[int(sV.y)-1][int(sV.x)]=0;
			}
			else if(CollisionMap[int(sV.y)][int(sV.x)-1]>100)
			{	//detekcja mijania siê z czyimœ pociskiem
				--BulletCounter;
				CollisionMap[int(sV.y)][int(sV.x)-1]=300;
				CollisionMap[int(sV.y)-1][int(sV.x)]=0;
			}
			else
			{
				CollisionMap[int(sV.y)-1][int(sV.x)]=0;
				sBullet.Move(BULLETSPD,0);
				sV = sBullet.GetPosition();
				typeId = TypeMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
				colId = CollisionMap[int((sV.y-MAPYPOS)/10)][int((sV.x-MAPXPOS)/10)];
				if(typeId == 1 || typeId == 2 || typeId == 6)
					result = typeId;
				else if(colId > 6)
					result = colId;
				else
				{
					typeId = TypeMap[int((sV.y-MAPYPOS)/10)-1][int((sV.x-MAPXPOS)/10)];
					colId = CollisionMap[int((sV.y-MAPYPOS)/10)-1][int((sV.x-MAPXPOS)/10)];
					if(typeId == 1 || typeId == 2 || typeId == 6)
						result = typeId;
					else if(colId > 6)
						result = colId;
					else if(colId == 0)
						CollisionMap[int(sV.y-MAPYPOS)/10-1][int(sV.x-MAPXPOS)/10]=TypeId;
				}
			}
		}
		else
		{
			CollisionMap[int(sV.y)-1][51]=0;
			result = -1;
		}
		break;
	}
	return result;
}