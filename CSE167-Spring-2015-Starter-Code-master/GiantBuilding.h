#ifndef __GiantBuilding__
#define __GiantBuilding__

#include <iostream>

#include "Building.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Building;

class GiantBuilding : public Building
{
	public:
		GiantBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		~GiantBuilding(void);

		void build(const Quadrangle& q);
	protected :

		void buildFloors(const Quadrangle& q);
		void scale(Vector& a, Vector& b, Vector& c, Vector& d, double val = 1, bool retCentre = false);

		void measureLedgeWidthBetweenFloors(const double& hauteurIntEtg);

		void setGiantBuildingInfos();
};

#endif
