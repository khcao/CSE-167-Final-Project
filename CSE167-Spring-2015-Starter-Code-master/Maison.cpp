#include "Maison.h"

#include "MaisonClassique.h"

Maison::Maison(const Triangle& t, const unsigned int& typeCentre, const double& heightMax): BaseBuilding(t, typeCentre, heightMax){setMaisonInfos();}
Maison::Maison(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax): BaseBuilding(q, typeCentre, heightMax){setMaisonInfos();}
Maison::Maison(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax): BaseBuilding(p, typeCentre, heightMax){setMaisonInfos();}
Maison::~Maison(void){}



void Maison::chooseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax)
{
	MaisonClassique(q, typeCentre, heightMax).build(q);
}


void Maison::setMaisonInfos()
{

}