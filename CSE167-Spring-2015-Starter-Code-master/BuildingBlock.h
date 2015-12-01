#ifndef _QUARTIER_
#define _QUARTIER_


#include "shape.h"
#include "geometry.h"
#include "city.h"
#include "BaseBuilding.h"
#include <vector>
#include <algorithm>    // std::min
class BuildingBlock {

public:

	BuildingBlock();

	BuildingBlock(const Vector&, const Vector&, const Vector&);
	BuildingBlock(const Vector&, const Vector&, const Vector&, const std::vector<Centre> &);

	BuildingBlock(const Vector&, const Vector&, const Vector&, const Vector&);
	BuildingBlock(const Vector&, const Vector&, const Vector&, const Vector&, const std::vector<Centre> &);

	static void constructBlock(const Quadrangle&, const std::vector<Centre>&);

protected:

	Vector a;
	Vector b;
	Vector c;
	Vector d;

	double ab,bc,cd,da,ca;

	std::vector<Centre> centres;

	
};

#endif
