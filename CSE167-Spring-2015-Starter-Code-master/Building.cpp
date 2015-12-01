#include "Building.h"

#include "GiantBuilding.h" //le laisser ici
#include "SmallBuilding.h"
#include "MaisonClassique.h"
#include <iostream>

Building::Building(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax): BaseBuilding(q, typeCentre, heightMax){setBuildingInfos();}
Building::~Building(void){}



void Building::chooseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& maxHeight)
{
	
	double unEtageMoyen = 2.5*UNIT; //2.5 mèters
	if (rand() % 3 == 1)
	{
		Maison::chooseBuilding(q, typeCentre, maxHeight);

	}else{
			if(maxHeight > 20*unEtageMoyen) 
		GiantBuilding(q, typeCentre, maxHeight).build(q);
	else if (maxHeight > 3 * unEtageMoyen && maxHeight <= 20*unEtageMoyen)
		SmallBuilding(q, typeCentre, maxHeight).build(q); 
	}

}

//--------------------------------------------------------->


void Building::setBuildingInfos()
{

	

	//************************************
	//***** PROPORTIONS DU BATIMENT *****
	//************************************

	//pas de rétrécissement sur des building dont les côtés ne respectent pas le ratio 2
	bool bonnesProportions = false;
	double ab = Norm(listPoints[1] - listPoints[0]);
	double bc = Norm(listPoints[2] - listPoints[1]);
	if(ab > bc) bonnesProportions = ab/bc <= 2;
	else bonnesProportions = bc/ab <= 2;

	if(rand()%100 > 30 && bonnesProportions)
	{	
		//% de rétrecissement tous les N étage
		narrowingFactor = (double) ((rand()%10) + 7) /100;

		//type de rétrécissement
		narrowingCenter = rand()%5; // Centré | Nord | Sud | Est | Ouest -> 0 1 2 3 4
	}
	else
	{
		narrowingFactor = 0; 
		narrowingCenter = 0;
		creerFenetre = false; //pour éviter que certains étages aient des fenêtre et les autres non (risque de surface trop petite)
	}



		numOfFloorsGroundFloor = rand()%3 + 1;

//bearings
	activeBearings = rand()%100 > 15? true:false;
	int tmpValMin = (double) numberOfMaxFloors*0.2;
	if(tmpValMin < 4) tmpValMin = 3;
	bearingDist = rand()%(tmpValMin) + tmpValMin;
	
	if(narrowingFactor)
	{
		unsigned int randLoiPalier = rand()%100;
		if(randLoiPalier > 40)
			bearingMeasure = 0; //constante
		else if(randLoiPalier > 10)
			bearingMeasure = 1; //augmente
	}
	else bearingMeasure = 0; //plus joli

	if(numOfFloorsGroundFloor == bearingDist) measureBearing();


	if(rand()%100 < 7) separation = true; else separation = false;
	if(separation && numOfFloorsGroundFloor < 5) numEtageSeparation = numOfFloorsGroundFloor + rand()%4; //ajout du RDc + 4 étages au maximum
	else numEtageSeparation = -1;
	

}

void Building::createGroundFloor()
{

	PrismQuad(listPoints[0], listPoints[1], listPoints[2], listPoints[3], windowHeight*numOfFloorsGroundFloor).Render();

	for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] += Vector(0,0, windowHeight*numOfFloorsGroundFloor);
}


void Building::measureBearing()
{
	int val = ceil((double) bearingDist*20/100);
	if(bearingMeasure == 1) bearingDist += val;
	//else if(palier-val > 1) palier -= val; //-> pas vraiment bien par rapport à se qui existe
}