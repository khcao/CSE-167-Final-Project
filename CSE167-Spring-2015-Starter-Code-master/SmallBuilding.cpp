#include "SmallBuilding.h"

SmallBuilding::SmallBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax) : Building(q, typeCentre, heightMax) { setSmallBuildingInfos(); }
SmallBuilding::~SmallBuilding(void) {}


void SmallBuilding::build(const Quadrangle& q)
{
	createGroundFloor();

	buildFloors(q);


}
void SmallBuilding::buildFloors(const Quadrangle& q)
{
	Quadrangle newQ(q);
	createFloors(numberOfMaxFloors - numOfFloorsGroundFloor, 0);
}


void SmallBuilding::setSmallBuildingInfos()
{
	//no earthquake bearings and the ground floor is fairly small 
	activeBearings = false;
	numOfFloorsGroundFloor = rand() % 2 + 1;

	double unite = (double)UNIT;

	//floors usually not larger than 3 units
	int chooseSize = rand() % 3;
	if (chooseSize == 0) windowHeight = unite*2.5;
	else if (chooseSize == 1) windowHeight = unite*2.7;
	else windowHeight = unite * 3;

	//Les fenêtres sont en général hautes et +/- large
	double widthF = unite * ((((double)(rand() % 70)) / 100) + 1);
	floorWindow->setSizeWindow(widthF);
	floorWindow->setHeightTopBorder(windowHeight*0.2);
	floorWindow->setHeightBottomBorder(windowHeight*0.2);
}