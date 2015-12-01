#include "FloorWindow.h"

#include <iostream>
using namespace std;

FloorWindow::FloorWindow()
{
	createWindow = true;
}

FloorWindow::FloorWindow( const double _sizeOfWindow,
							const double _sizeCorner,
							const double _sizeBetweenWindows,
							const double _heightBorderAbove,
							const double _heightBottomBorder) :
							sizeOfWindow(_sizeOfWindow),
							cornerSize(_sizeCorner),
							sizeBetweenWindow(_sizeBetweenWindows),
							heightTopBorder(_heightBorderAbove),
							heightBottomBorder(_heightBottomBorder)
{
	createWindow = true;
}


void FloorWindow::setBoolCreateWindow(double airMin)
{
	double airMinPourCreation = ((sizeOfWindow + 2*cornerSize)*(sizeOfWindow + 2*cornerSize)) + 0.1; 
	createWindow = airMin > airMinPourCreation;
}

bool FloorWindow::isCreateWindow(){return createWindow;}
void FloorWindow::setSizeWindow(const double _sizeWindow){sizeOfWindow = _sizeWindow;}
void FloorWindow::setTailleCoin(const double _cornerSize){cornerSize = _cornerSize;}
void FloorWindow::setSizeBetweenWindow(const double _tailleInterFenetre){sizeBetweenWindow = _tailleInterFenetre;}
void FloorWindow::setHeightTopBorder(const double _heightBorderTop){heightTopBorder = _heightBorderTop;}
void FloorWindow::setHeightBottomBorder(const double _heightBorderBottom){heightBottomBorder = _heightBorderBottom;}


void FloorWindow::createFloorWindows(std::vector<Vector>& listPoints,
									 const double& floorHeight,
									 const unsigned int& numberOfFloors,
									 const unsigned int& newFloorStart,
									 const unsigned int& numberOfFloorsGroundFloor,
									 const unsigned int& numberOfFloorsMax)
{

	
	const unsigned int numOfPoints = listPoints.size();
	double sizeOfBaseCorner = cornerSize;

	

	std::vector<double> rectangleSize;
	std::vector<unsigned int> numberBetweenWindow; 

	//handles size conversion for the vertical walls in between the sides
	//only need 2 sides because they extend into each other
	for(unsigned int side = 0; side < 2; side++)
	{
		//size of the segment without corners.
		double sizeWithoutCorner = Norm(listPoints[(side+1)%numOfPoints] - listPoints[side]) - 2*cornerSize;
		//number of walls vertical
		double numberBetweenWallandWindowTemp = sizeWithoutCorner/(sizeOfWindow + sizeBetweenWindow);

		//take the floor and subtract 1 because we already have 1 corner taken care of beforehand
		double value = floor(numberBetweenWallandWindowTemp) - 1;
		if(value <= 0) value = 0;
		numberBetweenWindow.push_back(value);

		double waste = numberBetweenWallandWindowTemp - floor(numberBetweenWallandWindowTemp) + sizeBetweenWindow;
		rectangleSize.push_back( sizeOfBaseCorner + (waste/2) );
	}



	//create the floors themselves. Like a pancake!
	
	for(unsigned int floor = 0; floor < numberOfFloors; floor++)
	{
		Quadrangle newQ;

		unsigned int newFloor = newFloorStart + floor;
		newQ = Quadrangle(listPoints[0], listPoints[1], listPoints[2], listPoints[3]);
		//first floor (where we start the building)
		if (newFloor == numberOfFloorsGroundFloor || floor == 0)
		{
			PrismQuad(newQ, heightBottomBorder).Render();
		}


		if(newFloor != numberOfFloorsMax-1 && floor != numberOfFloors-1) //between floors
		{
			//adjust Z after drawing the previous Floor
			for(unsigned int vect = 0; vect < 4; vect++) newQ.setCompVector(vect, 3, newQ[vect][3] + floorHeight );
			
			PrismQuad(newQ,   heightBottomBorder).Render();
		}
		else if (newFloor == numberOfFloorsMax-1 || floor == numberOfFloors-1) //last floor
		{
			
			for(unsigned int vect = 0; vect < 4; vect++) newQ.setCompVector(vect, 3, newQ[vect][3] + floorHeight );
			PrismQuad(newQ, heightTopBorder).Render();
		}

		//adjust the Z
		for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] += Vector(0,0, floorHeight);
	}

	//reset our heights of our points
	for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] -= Vector(0,0, floorHeight*numberOfFloors);

	
	std::vector<Vector> pointCorner;
	std::vector<Vector> faceDeplacement;

	//recover vectors
	Vector aCoin = listPoints[0]; pointCorner.push_back(listPoints[0]);
	Vector bCoin = listPoints[1]; pointCorner.push_back(listPoints[1]);
	Vector cCoin = listPoints[2]; pointCorner.push_back(listPoints[2]);
	Vector dCoin = listPoints[3]; pointCorner.push_back(listPoints[3]);

	//calculateVectors of the sides
	Vector abCoin = bCoin - aCoin;
	Vector bcCoin = cCoin - bCoin;
	Vector dcCoin = cCoin - dCoin;
	Vector adCoin = dCoin - aCoin;

	double nbFoisAb = Norm(abCoin)/rectangleSize[0];
	double nbFoisBc = Norm(bcCoin)/rectangleSize[1];
	double nbFoisDc = Norm(dcCoin)/rectangleSize[0];
	double nbFoisAd = Norm(adCoin)/rectangleSize[1];

	Vector abDeplace = abCoin/nbFoisAb; faceDeplacement.push_back(abDeplace);
	Vector bcDeplace = bcCoin/nbFoisBc; faceDeplacement.push_back(bcDeplace);
	Vector dcDeplace = dcCoin/nbFoisDc; faceDeplacement.push_back(dcDeplace);
	Vector adDeplace = adCoin/nbFoisAd; faceDeplacement.push_back(adDeplace);

	//itterate through each side of the building
	for(unsigned int side = 0; side < numOfPoints; side++)
	{

		//displacement vector
		Vector deplacementAbOubA = side < 2 ? faceDeplacement[side]:-faceDeplacement[side];
		Vector deplacementBcOucB = (side+1)%numOfPoints < 2 ? faceDeplacement[(side+1)%numOfPoints]:-faceDeplacement[(side+1)%numOfPoints];

		//Coordinates of the rectangle
		Vector bPrim = pointCorner[side] + deplacementAbOubA;
		Vector cPrim = bPrim + deplacementBcOucB;
		Vector dPrim = pointCorner[side] + deplacementBcOucB;

		//draw the corner wall
		 PrismQuad(pointCorner[side], bPrim, cPrim, dPrim, floorHeight*numberOfFloors).Render();

		//carve space between windows
 		if(side < 2 && numberBetweenWindow[side%2] > 0)
		{
			Vector e = pointCorner[side] + faceDeplacement[side%numOfPoints];
			Vector f = e;
			Vector h = pointCorner[(side+3)%numOfPoints] + faceDeplacement[(side+2)%numOfPoints];
			Vector g = h; 

			Vector aCoinBCoin = pointCorner[(side+1)%numOfPoints] - pointCorner[side];
			Vector dCoinCCoin = pointCorner[(side+2)%numOfPoints] - pointCorner[(side+3)%numOfPoints];

			double nbFoisAb2 = Norm(aCoinBCoin)/sizeOfWindow;
			double nbFoisDc2 = Norm(dCoinCCoin)/sizeOfWindow;
			Vector abDeplaceFen = (aCoinBCoin)/nbFoisAb2;
			Vector dcDeplaceFen = (dCoinCCoin)/nbFoisDc2;

			nbFoisAb2 = Norm(aCoinBCoin)/sizeBetweenWindow;
			nbFoisDc2 = Norm(dCoinCCoin)/sizeBetweenWindow;
			Vector abDeplaceItM = (aCoinBCoin)/nbFoisAb2;
			Vector dcDeplaceItM = (dCoinCCoin)/nbFoisDc2;

			//Ajout de EF et HG, on le fait pour définir la largeur de l'inter-mur.
			e += abDeplaceFen;
			f += abDeplaceFen + abDeplaceItM; //abDeplaceItM = EF
			g += dcDeplaceFen + dcDeplaceItM; //dcDeplaceItM = HG
			h += dcDeplaceFen;

			for(unsigned int windowNumber = 0; windowNumber < numberBetweenWindow[side%2]; windowNumber++)
			{
				//Create between floors
				PrismQuad(e,f,g,h, floorHeight*numberOfFloors).Render();
					
				//on se déplace d'une fenêtre et d'un inter-mur
				e += abDeplaceFen + abDeplaceItM;
				f += abDeplaceFen + abDeplaceItM;
				g += dcDeplaceFen + dcDeplaceItM;
				h += dcDeplaceFen + dcDeplaceItM;
			}

		}
		
		
	}
	Vector center = (listPoints[0] + listPoints[1] + listPoints[2] + listPoints[3])/4;
	double edgeWidth = ((double) UNIT) * 0.2;

	double coef = 0.1;
	//here is where we draw the window anyway
	Vector::setCol(COL_FEN1, COL_FEN2, COL_FEN3);
	PrismQuad(listPoints[0] + faceDeplacement[0]*coef + faceDeplacement[1]*coef,
			  listPoints[1] + faceDeplacement[1]*coef - faceDeplacement[2]*coef,
			  listPoints[2] - faceDeplacement[2]*coef - faceDeplacement[3]*coef,
			  listPoints[3] - faceDeplacement[3]*coef + faceDeplacement[0]*coef,
			  floorHeight*numberOfFloors - heightTopBorder).Render();
	Vector::setColDefaut();


	//reset the height
	for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] += Vector(0,0, floorHeight*numberOfFloors);
}

