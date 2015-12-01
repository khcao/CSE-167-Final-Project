#ifndef __SmallBuilding__
#define __SmallBuilding__

#include <iostream>
#include "Building.h"
#include "SmallBuilding.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Building;

/**
* @class Ce sont les petits building de 3 à 10 étages
*/
class SmallBuilding : public Building
{
	public:
		SmallBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		~SmallBuilding(void);

		void build(const Quadrangle& q);

	protected :

		void buildFloors(const Quadrangle& q);

		void setSmallBuildingInfos();

};

#endif
