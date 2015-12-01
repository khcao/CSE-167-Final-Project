#ifndef _QCENTRE_
#define _QCENTRE_

#include <vector>
#include "BuildingBlock.h"


class BuildingBlock;

class MetroBlock : public BuildingBlock
{

public:

	MetroBlock(const Vector& _a, const Vector& _b, const Vector& _c,  const Centre&);
	MetroBlock(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const Centre&);


	static void constructBlock(const Quadrangle& _t, const Centre &);

private:

	void constructBuilding();
Centre centre;
};

#endif