#include "MaisonClassique.h"

MaisonClassique::MaisonClassique(const Triangle& t, const unsigned int& typeCentre, const double& heightMax): Maison(t, typeCentre, heightMax){setMaisonClassiqueInfos();}
MaisonClassique::MaisonClassique(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax): Maison(q, typeCentre, heightMax){setMaisonClassiqueInfos();}
MaisonClassique::MaisonClassique(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax): Maison(p, typeCentre, heightMax){setMaisonClassiqueInfos();}
MaisonClassique::~MaisonClassique(void){}


void MaisonClassique::build(const Triangle& t){}

void MaisonClassique::build(const Quadrangle& q)
{
	buildFloors(q);
	creerToitPrisme();
}

void MaisonClassique::build(const Pentangle& p){}


void MaisonClassique::buildEtages(const Triangle& t){}

void MaisonClassique::buildFloors(const Quadrangle& q)
{
	Vector plusUnEtage(0,0, windowHeight);

	PrismQuad(q, numberOfMaxFloors*windowHeight).Render();
	for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] += (plusUnEtage*numberOfMaxFloors);

	//double unite = (double) UNITE;

	//for(unsigned int i = 1; i < nbEtagesMax; i++)
	//{
		//creerEtagesSimples(nbEtagesMax);

		//double nbFenetres = 2;
		//double tailleDesFenetres = unite;
		//double tailleDesCoins = unite;

		//double plusPetitCote = Norm(listePoints[3]-listePoints[0]);
		//if(plusPetitCote > Norm(listePoints[1]-listePoints[0])) plusPetitCote = Norm(listePoints[1]-listePoints[0]);	

		//double tailleDesInterFenetre = plusPetitCote - tailleDesFenetres * nbFenetres - tailleDesCoins*2;
		//tailleDesInterFenetre -= 0.5;

		//etageFenetre->setHauteurBordInf(hauteurEtage*0.1);
		//etageFenetre->setHauteurBordSup(hauteurEtage*0.1);
		//etageFenetre->setTailleInterFenetre(tailleDesInterFenetre);
		//etageFenetre->setTailleFenetre(tailleDesFenetres);
		//etageFenetre->setTailleCoin(tailleDesCoins);
		//etageFenetre->creerEtageVitre(listePoints, hauteurEtage);
	//}
}

void MaisonClassique::buildEtages(const Pentangle& p){}


void MaisonClassique::setMaisonClassiqueInfos()
{
	numberOfMaxFloors = rand()%2 + 2;
}