#include "MetroBlock.h"

using namespace std;


MetroBlock::MetroBlock(const Vector& _a, const Vector& _b, const Vector& _c, const Centre& _centre) : BuildingBlock(_a, _b, _c), centre(Centre(_centre))
{}

MetroBlock::MetroBlock(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const Centre& _centre) : BuildingBlock(_a, _b, _c, _d), centre(Centre(_centre))
{}


void MetroBlock::constructBlock(const Quadrangle& _q, const Centre& _centre)
{
	MetroBlock qc(_q[0], _q[1], _q[2], _q[3], Centre(_centre));

	//we will build a building that fills the 

		qc.constructBuilding();

}


void MetroBlock::constructBuilding()
{
		BaseBuilding::chooseBuilding(Quadrangle(a, b, c, d), centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a, b, c, d))));
		
}

