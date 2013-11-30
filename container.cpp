#include "container.h"

container::container(std::string PathTo)	//k-tor
{
	fTab = new field*[7];
	for(int i=0; i<7; i++)
		fTab[i] = new field(i, PathTo);
	
	EagleProtection.LoadFromFile((PathTo+"//eagle-protection.png"));	//os�ona or�a (niezniszczalne klocki wok� or�a - bonus)
	EagleProtection.SetSmooth(false);
	sEagleProtection.SetImage(EagleProtection);
	sEagleProtection.SetPosition(220.f+MAPXPOS,460.f+MAPYPOS);
	uiBg.LoadFromFile("gfx//ui-bg.png");
	sUiBg.SetImage(uiBg);					//t�o gry
	sUiBg.SetPosition(0.f,0.f);
	sEndScreen.SetPosition(180.f,270.f);
	smallTank.LoadFromFile("gfx//smalltank.png");
	smallTank.SetSmooth(false);
	for(int i = 0; i < 2; i++) {	//ma�e czo�gi w interfejsie
		for(int j = 0; j < 10; j++) 
		{
			smallTanks[i*10+j].SetImage(smallTank);
			smallTanks[i*10+j].SetPosition((580.f+j*18.f),(150.f+i*25.f));
		}
	}
}
container::~container()	//d-tor
{
	for(int i=0; i<=6; i++)
		delete fTab[i];
	delete[] fTab;
}