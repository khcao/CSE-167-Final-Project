#ifndef __Building__
#define __Building__

#include "BaseBuilding.h"
#include "city.h"
#include "geometry.h"

class BaseBuilding;

class Building : public BaseBuilding
{
	public:

		Building(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		~Building(void);
	static void chooseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);

		virtual void build(const Quadrangle& q) =0;

	protected :

		double narrowingFactor; /**  pourcentage de rétrecissement = 0% Ou 20-30% */
		int narrowingCenter; /** on rétrécie la batiment selon un côté/point fixe : 0 = Centré, 1 = Nord, 2 = Sud, 3 = Est, 4 = Ouest  */

		bool activeBearings; /** si vrai alors les paliers sont pris en compte, faux sinon */
		int bearingDist; /** rétrécissement tous les N étages, avec N >= 4 */
		int bearingMeasure;  /** 0 = le nombe de paliers reste constant, 1 = augmente. Cette loi n'est pas modifiées pendant la construction */ 

		bool separation; /** si vrai, il y a séparation, false sinon (pas plus d'une fois par batiment) - TODO */
		unsigned int numEtageSeparation; /** l'étage à  partir duquel un batiment se scinde en 2 ou 3 parties (pas plus)*/

		/** @brief Initilise tous les attributs du building (à faire une seule fois) */
		void setBuildingInfos();

		/** @brief met à jour la valeur loiPalier */
		void measureBearing();

		void createGroundFloor();

		virtual void buildFloors(const Quadrangle& q) =0;

};


#endif
