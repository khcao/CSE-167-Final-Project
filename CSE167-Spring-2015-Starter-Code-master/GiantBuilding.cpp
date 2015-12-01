#include "GiantBuilding.h"
using namespace std;
GiantBuilding::GiantBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax): Building(q, typeCentre, heightMax){setGiantBuildingInfos();}
GiantBuilding::~GiantBuilding(void){}

void GiantBuilding::build(const Quadrangle& q)
{
	setBuildingInfos();
	createGroundFloor();

		buildFloors(q);
	//Roof stuff

}

void GiantBuilding::buildFloors(const Quadrangle& q)
{

	Quadrangle newQ(q);

	Vector a,b,c,d; 
	double heightBetweenFloors = 0;
	if(rand()%100 > 20) heightBetweenFloors = 0.2;

	if(activeBearings)
	{
		//add floor bearings
		for(unsigned int i = numOfFloorsGroundFloor; i < numberOfMaxFloors; i+=bearingDist)
		{
			newQ = Quadrangle(listPoints[0],listPoints[1],listPoints[2],listPoints[3]);

			if(newQ.Area() > airMin)
			{
				if(i != numOfFloorsGroundFloor)
				{//narrowing of the floor
					if(narrowingFactor > 0)
					{
						scale(a,b,c,d);
						listPoints.clear();
						listPoints.push_back(a);
						listPoints.push_back(b);
						listPoints.push_back(c);
						listPoints.push_back(d);
					}
					else if(heightBetweenFloors > 0 && (numberOfMaxFloors - i - 1) > 3)
					{
						measureLedgeWidthBetweenFloors(heightBetweenFloors);
					}
				}
				double numberFloorsCreated;
				if( (i + bearingDist) >= numberOfMaxFloors)
					numberFloorsCreated = numberOfMaxFloors - i;
				else if(i != numberOfMaxFloors)
					numberFloorsCreated = bearingDist;

				createFloors(numberFloorsCreated, i);

				measureBearing();
				
			}

		}
	}
	else
	{
		createFloors(numberOfMaxFloors - numOfFloorsGroundFloor, 0);
	}

}



void GiantBuilding::measureLedgeWidthBetweenFloors(const double& heightBetweenFloors)
{
	Vector centre(0,0,0); 

	for(unsigned int i = 0; i < listPoints.size(); i++)
		centre += listPoints[i];
	centre /= listPoints.size();

	double ledgeWidth = (double) UNIT;

	std::vector<Vector> newPoints;
	for(unsigned int i = 0; i < listPoints.size(); i++)
	{
		double pas = Norm(listPoints[i] - centre)/ledgeWidth;
		newPoints.push_back( listPoints[i] + ( (listPoints[i] - centre)/pas ) );
	}
	
	PrismQuad(newPoints[0],newPoints[1],newPoints[2],newPoints[3], heightBetweenFloors).Render();

	for(unsigned int vect = 0; vect < listPoints.size(); vect++) listPoints[vect] += Vector(0,0, heightBetweenFloors);
}

void GiantBuilding::scale(Vector& a, Vector& b, Vector& c, Vector& d, double val, bool retCentre) 
{
	a = listPoints[0];
	b = listPoints[1];
	c = listPoints[2];
	d = listPoints[3];

	if(narrowingCenter == 0 || retCentre) //Centre
	{
		Vector centre = (a + b + c + d)/4;
		std::vector<Vector> variants;
		variants.push_back(a);
		variants.push_back(b);
		variants.push_back(c);
		variants.push_back(d);

		if(!retCentre) scaleXY(narrowingFactor, centre, variants);
		else scaleXY(val, centre, variants);

		a = variants[0];
		b = variants[1];
		c = variants[2];
		d = variants[3];

	}
	else if(narrowingCenter == 1) //North
	{
		scaleXY(narrowingFactor, d, a);
		scaleXY(narrowingFactor, c, b);
	}
	else if(narrowingCenter == 2) // South
	{
		scaleXY(narrowingFactor, b, c);
		scaleXY(narrowingFactor, a, d);
	}
	else if(narrowingCenter == 3) //East
	{
		scaleXY(narrowingFactor, b, a);
		scaleXY(narrowingFactor, c, d);
	}
	else //West
	{
		scaleXY(narrowingFactor, a, b);
		scaleXY(narrowingFactor, d, c);
	}
}


void GiantBuilding::setGiantBuildingInfos()
{
	double unite = (double) UNIT;

 windowHeight = unite*2.5;

	double largeurF = unite * ( .5+ 1);
	floorWindow->setSizeWindow(largeurF);

	double bordureSup = windowHeight*0.1;
	double bordureInf = windowHeight*0.1;

	floorWindow->setHeightTopBorder(bordureSup);
	floorWindow->setHeightBottomBorder(bordureInf);

	double betweenWindow = (rand()%100)/100 + unite;
	floorWindow->setSizeBetweenWindow(betweenWindow);
}