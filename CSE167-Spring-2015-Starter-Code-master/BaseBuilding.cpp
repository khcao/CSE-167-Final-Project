#include "BaseBuilding.h"
#include "Building.h"
#include "Maison.h"
#include <iostream>

std::vector<double> BaseBuilding::ToitPyramideCoupe;
std::vector<double> BaseBuilding::ToitPyramide;
std::vector<double> BaseBuilding::PrismRoof;

BaseBuilding::BaseBuilding(const Triangle& t, const unsigned int& typeCentre, const double& heightMax)
{
	listPoints.push_back(t[0]);
	listPoints.push_back(t[1]);
	listPoints.push_back(t[2]);
	airMin = t.Area()*0.3;
	setBuildingInfo(typeCentre, heightMax);
}

BaseBuilding::BaseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax)
{
	seed = rand();
	listPoints.push_back(q[0]);
	listPoints.push_back(q[1]);
	listPoints.push_back(q[2]);
	listPoints.push_back(q[3]);
	airMin = q.Area()*0.3;
	setBuildingInfo(typeCentre, heightMax);
}

BaseBuilding::BaseBuilding(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax)
{
	listPoints.push_back(p[0]);
	listPoints.push_back(p[1]);
	listPoints.push_back(p[2]);
	listPoints.push_back(p[3]);
	listPoints.push_back(p[4]);
	airMin = p.Area()*0.3;
	setBuildingInfo(typeCentre, heightMax);
}

BaseBuilding::~BaseBuilding(void)
{
	delete floorWindow;
}



void BaseBuilding::chooseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax)
{
	Building::chooseBuilding(q, typeCentre, heightMax);
}


void BaseBuilding::createGroundFloor(const unsigned int& _nbEtages)
{
	setBuildingColor();
	PrismQuad(listPoints[0], listPoints[1], listPoints[2], listPoints[3], windowHeight*_nbEtages).Render();

	for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] += Vector(0,0, windowHeight*_nbEtages);
}

void BaseBuilding::createFloors(const unsigned int& _nbEtages, const unsigned int& etageActu)
{
	setBuildingColor();
	if (floorWindow->isCreateWindow())
		floorWindow->createFloorWindows(listPoints, windowHeight, _nbEtages, etageActu, numOfFloorsGroundFloor, numberOfMaxFloors);
	else
		createSimpleFloors(_nbEtages);
}
void BaseBuilding::setBuildingColor() {

	if (seed % 3 == 0)
		Vector::setCol(COL_BUILDA1, COL_BUILDA2, COL_BUILDA3);
	else if (seed % 3== 1)
		Vector::setCol(COL_BUILDB1, COL_BUILDB2, COL_BUILDB3);
	else
		Vector::setCol(COL_BUILD1, COL_BUILD2, COL_BUILD3);
}
void BaseBuilding::createSimpleFloors(const unsigned int& _nbEtages)
{
	PrismQuad(listPoints[0],listPoints[1],listPoints[2],listPoints[3], _nbEtages*windowHeight).Render();
	for(unsigned int vect = 0; vect < 4; vect++) listPoints[vect] += Vector(0,0,_nbEtages*windowHeight);
}

//----------------------------------------------------------------->
//------------------------------TOIT--------------------------------
//-----------------------------------------------------------------<


void BaseBuilding::creerToitPyramideCoupe()
{
	double largeurBord = (double) UNIT*0.2;
	double hauteurBord = (double) UNIT*0.2;
	double air = Quadrangle(listPoints[0],listPoints[1],listPoints[2],listPoints[3]).Area();
	bool airMini = air > 8*(largeurBord*largeurBord);

	if(airMini)
	{
		float zTriangle = listPoints[0][2] + (float) windowHeight*2;
		Vector centre(0,0,0);

		for(unsigned int i = 0; i < listPoints.size(); i++) centre += listPoints[i];
		centre /= listPoints.size();
		double& z = centre[2]; 
		z = zTriangle; // mise à jour de Z

		//-------------------------Quadrangle supérieur --------------------------------------------------->
		std::vector<Vector> quadrangleIn; //la liste des points du quadrangle supérieur

		double onConserve = (double)(rand()%15)/100;
		for(unsigned int i = 0; i < listPoints.size(); i++)
		{
			Vector in = listPoints[i] + (centre - listPoints[i])*(onConserve + 0.5);
			double& z = in[2];
			z = zTriangle;
			quadrangleIn.push_back(in);
		}

		glBegin(GL_QUADS);
			glNormal3d(0,0,1.0f);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(quadrangleIn[0][0], quadrangleIn[0][1], quadrangleIn[0][2]);
			glVertex3f(quadrangleIn[1][0], quadrangleIn[1][1], quadrangleIn[1][2]);
			glVertex3f(quadrangleIn[2][0], quadrangleIn[2][1], quadrangleIn[2][2]);
			glVertex3f(quadrangleIn[3][0], quadrangleIn[3][1], quadrangleIn[3][2]);

			for(int i=0; i<4;i++)
			{
				for(int j =0;j<3;j++)
				{
					ToitPyramideCoupe.push_back(quadrangleIn[i][j]);
				}
			}
			
		glEnd(); 
		//--------------------------------------------------------------------------------------------------<


		//----------------------------Faces de la "pyramide coupée"-----------------------------------------<  
		glBegin(GL_QUADS);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			for(unsigned int i = 0; i < 4; i++)
			{	
				glVertex3f(quadrangleIn[i%4][0], quadrangleIn[i%4][1], quadrangleIn[i%4][2]); // point Haut-Gauche
				glVertex3f(listPoints[i%4][0], listPoints[i%4][1], listPoints[i%4][2]); // point Bas-Gauche
				glVertex3f(listPoints[(i+1)%4][0], listPoints[(i+1)%4][1], listPoints[(i+1)%4][2]); //point Bas-Droite
				glVertex3f(quadrangleIn[(i+1)%4][0], quadrangleIn[(i+1)%4][1], quadrangleIn[(i+1)%4][2]); //point Haut-Droite
			}

			int j;
			for (int i=0; i<=3 ;i++)
			{
				for(j=0;j<=2;j++)
					ToitPyramideCoupe.push_back(quadrangleIn[i%4][j]);
				for(j=0;j<=2;j++)
			   	    ToitPyramideCoupe.push_back(listPoints[i%4][j]);
			    for(j=0;j<=2;j++)
				    ToitPyramideCoupe.push_back(listPoints[(i+1)%4][j]);
			    for(j=0;j<=2;j++)
			        ToitPyramideCoupe.push_back(quadrangleIn[(i+1)%4][j]);
			}


		glEnd();
		//--------------------------------------------------------------------------------------------------<

		listPoints.clear();
		for(unsigned int i = 0; i < quadrangleIn.size(); i++) listPoints.push_back(quadrangleIn[i]);
 PrismQuad(quadrangleIn[0],quadrangleIn[1],quadrangleIn[2],quadrangleIn[3], ((double) UNIT)*0.2).Render();
	}
	
}


void BaseBuilding::creerToitPrisme(bool addChimney)
{

	/*
	 d_________________c
	 |				   |
	e|________g________|f --> arrête supérieure du prisme
	 | 				   |
	 |________h________|
	 a				   b
	*/

	double air = Quadrangle(listPoints[0],listPoints[1],listPoints[2],listPoints[3]).Area();

	if(air > airMin)
	{
		double hauteurPrisme = (double) UNIT * 3;
		Vector monterEnZ(0,0,hauteurPrisme);
		int j;

		Vector e = ( (listPoints[3] + listPoints[0]) /2 ) + monterEnZ;
		Vector f = ( (listPoints[2] + listPoints[1]) /2 ) + monterEnZ;

		glBegin(GL_TRIANGLES); // Face ade
			Vector n= (listPoints[3]-listPoints[0])/(e-listPoints[0]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listPoints[0][0], listPoints[0][1], listPoints[0][2]);
			glVertex3f(listPoints[3][0], listPoints[3][1], listPoints[3][2]);
			glVertex3f(e[0], e[1], e[2]);

			  
			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[0][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[3][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(e[j]);			

		glEnd();

		glBegin(GL_QUADS); // Face abfe
			n= (listPoints[1]-listPoints[0])/(e-listPoints[0]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listPoints[0][0], listPoints[0][1], listPoints[0][2]);
			glVertex3f(listPoints[1][0], listPoints[1][1], listPoints[1][2]);
			glVertex3f(f[0], f[1], f[2]);
			glVertex3f(e[0], e[1], e[2]);

			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[0][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[1][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(f[j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(e[j]);
			
		glEnd();

		glBegin(GL_QUADS); // Face cdef
			n= (listPoints[3]-listPoints[2])/(f-listPoints[2]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listPoints[2][0], listPoints[2][1], listPoints[2][2]);
			glVertex3f(listPoints[3][0], listPoints[3][1], listPoints[3][2]);
			glVertex3f(e[0], e[1], e[2]);
			glVertex3f(f[0], f[1], f[2]);

			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[2][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[3][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(e[j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(f[j]);

		glEnd();

		glBegin(GL_TRIANGLES); // Face bcf
			n= (listPoints[2]-listPoints[1])/(f-listPoints[1]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listPoints[1][0], listPoints[1][1], listPoints[1][2]);
			glVertex3f(listPoints[2][0], listPoints[2][1], listPoints[2][2]);
			glVertex3f(f[0], f[1], f[2]);

			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[1][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(listPoints[2][j]);
			for(j=0;j<=2;j++)
				PrismRoof.push_back(f[j]);

		glEnd();


		//-------------------Cheminée----------------------------->

		if(addChimney)
		{
			Vector g = (e + f)/2;
			Vector h = (listPoints[0] + listPoints[1])/2;

			double chimneyWidth = (double) UNIT;

			std::vector<Vector> newPoints;
			newPoints.push_back(listPoints[0] + monterEnZ/3);
			newPoints.push_back(h + monterEnZ/3); //e - monterEnZ + (monterEnZ/3)
			newPoints.push_back(e - (monterEnZ*2/3)); //g - monterEnZ + (monterEnZ/3)
			newPoints.push_back(g - (monterEnZ*2/3));

			Vector tmp = (listPoints[0] + e + g + h)/4;
			Vector centerAEGH = Vector(tmp[0],tmp[1], newPoints[0][2]); //le centre de la cheminée

			double tailleAd = Norm(newPoints[3] - newPoints[0]);
			double tailleAb = Norm(newPoints[1] - newPoints[0]);
			double ratioAbEtDc,ratioAdEtBc;
			if(tailleAd > tailleAb)
			{
				ratioAbEtDc = tailleAd/tailleAb;
				ratioAdEtBc = 1;
			}
			else
			{
				ratioAbEtDc = 1;
				ratioAdEtBc = tailleAb/tailleAd;
			}
		
			for(unsigned int i = 0; i < newPoints.size(); i++)
			{
				double pas = Norm(newPoints[i] - centerAEGH)/chimneyWidth;
				newPoints[i] = centerAEGH + ( (newPoints[i] - centerAEGH)/pas );
			}

			//Les sommets de la cheminée
			Vector a,b,c,d;
			a = newPoints[0];
			b = newPoints[1];
			c = newPoints[3];
			d = newPoints[2];

			//comme on veut que tous les côtés soient égaux, on applique un ratio
			PrismQuad(
				a,
				a + (b - a)*ratioAbEtDc,
				d + (c - d)*ratioAbEtDc,
				a + (d - a)*ratioAdEtBc,
				((double)UNIT)*3).Render();
		}
	}

}



void BaseBuilding::scaleXY(const double& factor, const Vector& invariants, std::vector<Vector>& variants) const
{
	if(!variants.empty() && factor != 0 && factor != 1)
	{

		double newFactor = 1 - factor;
		if(factor > 1) newFactor = factor;

		for(unsigned int i = 0; i < variants.size(); i++)
		{
			variants[i][0] = invariants[0] + (variants[i][0] - invariants[0])*newFactor;
			variants[i][1] = invariants[1] + (variants[i][1] - invariants[1])*newFactor;
		}

	}
}


void BaseBuilding::scaleXY(const double& factor, const Vector& invariants, Vector& variants) const
{
	if(factor != 0 && factor != 1)
	{
		double newFactor = 1 - factor;
		if(factor > 1) newFactor = factor;

		variants[0] = invariants[0] + (variants[0] - invariants[0])*newFactor;
		variants[1] = invariants[1] + (variants[1] - invariants[1])*newFactor;
	}
}


void BaseBuilding::setBuildingInfo(const unsigned int& typeCentre, const double& maxHeight)
{
	numOfFloorsGroundFloor = 1;

	height = maxHeight; 
	separation = false;


	windowHeight = (double) UNIT*2.5; 
	numberOfMaxFloors = floor(height/windowHeight);
	
	
	double unite = (double) UNIT;
	double widthF = unite * (((double) (rand()%100)/100) + 1);
	floorWindow = new FloorWindow(widthF, unite/2, unite, unite*0.4, unite*0.75);
	floorWindow->setBoolCreateWindow(airMin);
}

double BaseBuilding::getDefaultHeight(){return rand()%2 + 0.5;}
unsigned int BaseBuilding::getNumberFloorsMax(){return numberOfMaxFloors;}
