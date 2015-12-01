#ifndef __EtageFenetre__
#define __EtageFenetre__

#include <iostream>

#include "BaseBuilding.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"


/**
@class Permet principalement de créer un étage avec des fenêtres
*/
class FloorWindow
{
public:

	FloorWindow();
	FloorWindow(const double _tailleFenetre,
		const double _tailleCoin,
		const double _tailleInterFenetre,
		const double _hauteurBordSup,
		const double _hauteurBordInf);

	~FloorWindow(void) {}

	void createFloorWindows(std::vector<Vector>& listePoints,
		const double& hauteurEtage,
		const unsigned int& nbEtages,
		const unsigned int& etageActu,
		const unsigned int& nbEtagesRdc,
		const unsigned int& nbEtagesMax);

	void setBoolCreateWindow(double airMin);
	bool isCreateWindow();

	void setSizeWindow(const double _tailleFenetre);
	void setTailleCoin(const double _tailleCoin);
	void setSizeBetweenWindow(const double _tailleInterFenetre);
	void setHeightTopBorder(const double _hauteurBordSup);
	void setHeightBottomBorder(const double _hauteurBordInf);


private:

	bool createWindow; /** true si on peut créer des fenêtres, false sinon */
	double sizeOfWindow; /** largeur */
	double cornerSize; /** taille minimal d'un rectangle dans chaque coin de l'étage */
	double sizeBetweenWindow; /** mur entre deux fenêtres */
	double heightTopBorder; /** mur au dessus de la fenêtres */
	double heightBottomBorder; /** mur en dessous de la fenêtres */
};

#else if
class EtageFenetre;
#endif
