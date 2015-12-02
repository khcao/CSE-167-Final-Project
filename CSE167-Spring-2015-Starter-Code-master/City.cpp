#include <iostream>
#include "city.h"

//########################################################################################################### QUADRANGLE

/*!
\brief Create a quadrangular block.
\param a,b,c,d End vertices of the parcel.
*/
BlockQuad::BlockQuad(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const std::vector<Centre>&_centres) : Quadrangle(_a, _b, _c, _d)
{
	//this gives us a lamp
//	Mobilier(7 * UNITE, 50 * UNITE, 0.3*UNITE).creerLampadaires(Quadrangle(_a, _b, _c, _d)); 
	//draw the sidewalk then the building
	Vector::setCol(COL_TROTT1, COL_TROTT2, COL_TROTT3);
	PrismQuad(Quadrangle(_a, _b, _c, _d), 0.30*UNIT).Render(); // hauteur de 20 cm
	Vector::setColDefaut();
	double tShrink = 4 * UNIT; // 4 m
	Quadrangle q = Quadrangle(_a, _b, _c, _d).Shrink(tShrink, tShrink, tShrink, tShrink);
	BuildingBlock::constructBlock(q, _centres);
}

/*
Quardilateral piece of land
*/
LandQuad::LandQuad(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const std::vector<Centre> &_centres) :Quadrangle(_a, _b, _c, _d)
{
	centres = _centres;
}

void LandQuad::createBuildingBlock()
{
	int counter = 0;
	for (int i = 0; i < 4; i++){
		Camera cam = Globals::camera;
		Vector3 topLeftFrontPoint = cam.nearPlane[0];
		Vector3 botRightBackPoint = cam.farPlane[3];
		float  p1[16];
		glGetFloatv(GL_PROJECTION_MATRIX, p1);
		Matrix4 perspectiveMatrix = Matrix4(p1[0], p1[1], p1[2], p1[3], 
			p1[4], p1[5], p1[6], p1[7], p1[8], p1[9], p1[10], p1[11], p1[12], p1[13], p1[14], p1[15]);

		Vector4 centerOfItem(p[i][0], p[i][1], p[i][2],1);

		Vector4 transformedCenter = cam.getInverseMatrix() * centerOfItem;
	
		float distTop = transformedCenter.dot(cam.normTop.toVector4(1));
		float distLeft = transformedCenter.dot(cam.normLeft.toVector4(1));
		float distFront = transformedCenter.dot(cam.normFront.toVector4(1));
		float distBot = transformedCenter.dot(cam.normBot.toVector4(1));
		float distRight = transformedCenter.dot(cam.normRight.toVector4(1));
		float distBack = transformedCenter.dot(cam.normBack.toVector4(1));

		if ( distLeft < 5 && distRight <  5 && distFront < 0) {
			//we're good
			break;
		}
		else {
			counter++;
		}
	
	}
	if (counter == 4)
		return;
	//shrink to give space to the road
	Vector::setCol(COL_ROUTE1, COL_ROUTE2, COL_ROUTE3);
	PrismQuad(Quadrangle(p[0], p[1], p[2], p[3]), 0.10*UNIT).Render();
	Vector::setColDefaut();
	double tShrink = 7.5*UNIT;
	Quadrangle q = Quadrangle(p[0], p[1], p[2], p[3]).Shrink(tShrink, tShrink, tShrink, tShrink);
	//draw the building itself

	for (int i = 0; i < 4; i++) {
		if (is_point_in_rectangle( p[i])) {
			return;
		}
	}

	BlockQuad(q.getVectors(0), q.getVectors(1), q.getVectors(2), q.getVectors(3), centres);
}

bool LandQuad::is_point_in_rectangle( Vector& p) {
	//smallest , //biggest
	float val =3;
	float min = -10 * val;

	float max = 10 * val;
	return (min < p[0] && max >p[0] && min < p[1] && max>p[1]);
}
void LandQuad::drawEmptyGrassLot() {
	//first, we draw part of the road and then bring the block in
	Vector::setCol(COL_ROUTE1, COL_ROUTE2, COL_ROUTE3);
	PrismQuad(Quadrangle(p[0], p[1], p[2], p[3]), 0.10*UNIT).Render();

	//draw the sidewalk
	double tShrink = 7.5*UNIT;
	Quadrangle q = Quadrangle(p[0], p[1], p[2], p[3]).Shrink(tShrink, tShrink, tShrink, tShrink);
	Vector::setCol(COL_TROTT1, COL_TROTT2, COL_TROTT3);
	PrismQuad(Quadrangle(q[0], q[1], q[2], q[3]), 0.30*UNIT).Render();

	//draws the grass
	tShrink = 4 * UNIT; // 4 m
	Quadrangle q2 = Quadrangle(q[0], q[1], q[2], q[3]).Shrink(tShrink, tShrink, tShrink, tShrink);
	Vector::setCol(COL_HERBE1, COL_HERBE2, COL_HERBE3);
	PrismQuad(Quadrangle(q2[0], q2[1], q2[2], q2[3]), 0.40*UNIT).Render();
}
void LandQuad::verticalCut(double ab, double bc, double cd, double da, double random) {
	Vector v1(0, 0, 0); v1.setDiffxy(p[0], p[1], random * ab);
	Vector v2(0, 0, 0); v2.setDiffxy(p[3], p[2], random * cd);
	LandQuad(p[0], v1, v2, p[3], centres).Subdivide();
	LandQuad(v1, p[1], p[2], v2, centres).Subdivide();
}
void LandQuad::horizontalCut(double ab, double bc, double cd, double da, double random) {
	Vector v1(0, 0, 0); v1.setDiffxy(p[0], p[3], random * da);
	Vector v2(0, 0, 0); v2.setDiffxy(p[1], p[2], random * bc);
	LandQuad(v1, v2, p[2], p[3], centres).Subdivide();
	LandQuad(p[0], p[1], v2, v1, centres).Subdivide();
}
/*
\brief Subdivide a quadrangular land parcel.
*/
void LandQuad::Subdivide()
{
	// Area
	double area = Area();

	// Compute index of smallest edge. Norm is just the magnitude
	double ab = Norm(p[1] - p[0]);
	double bc = Norm(p[2] - p[1]);
	double cd = Norm(p[3] - p[2]);
	double da = Norm(p[0] - p[3]);
	//seeding for the split
	double random =  ((double)(rand() % 5 + 3) / 10); 
	//split it horizontal or vertically.
	int partage = rand() % 2;
	//true is cut vertically. false is cut horizontally
	if (ab > 150 * UNIT && da > 150 * UNIT)
	{
		if (partage)
			verticalCut(ab, bc, cd, da, random);
		else
			horizontalCut(ab, bc, cd, da, random);
	}
	else if (ab > 150 * UNIT)//&& partage
	{
		verticalCut(ab, bc, cd, da, random);
	}
	else if (da >  150 * UNIT)//&& !partage
	{
		horizontalCut(ab, bc, cd, da, random);

	}

	else if ((ab > 90 * UNIT && ab < 160 * UNIT  && bc > 2 * ab && bc < 320 * UNIT && bc > 180 * UNIT) || 
		(bc > 90 * UNIT && bc < 160 * UNIT  && ab > 2 * bc && ab < 320 * UNIT && ab > 180 * UNIT) || // tr?s grands quartiers rectangulaires
		(ab > 150 * UNIT && ab < 200 * UNIT  && bc > 1.5*ab && bc < 300 * UNIT && bc >225 * UNIT) || 
		(bc > 150 * UNIT && bc < 200 * UNIT  && ab > 1.5*bc && ab < 300 * UNIT && ab > 225 * UNIT) || // tr?s grands quartiers semi rectangulaires
		(ab > 80 * UNIT && ab < 100 * UNIT  && bc < 100 * UNIT  && bc > 80 * UNIT)) // grands quartiers carr?s
	{

		createBuildingBlock();

	}
	else if (ab > 90 * UNIT && da >  90 * UNIT)
	{
		if (partage) 
			verticalCut(ab, bc, cd, da, random);
		else 
			horizontalCut(ab, bc, cd, da, random);

	}
	else if (ab > 90 * UNIT) 
		verticalCut(ab, bc, cd, da, random);
	else if (da >  90 * UNIT) 
		horizontalCut(ab, bc, cd, da, random);

	else if ((ab > 80 * UNIT && ab < 100 * UNIT  && bc > 2 * ab && bc < 200 * UNIT && bc > 180 * UNIT) || (bc > 80 * UNIT && bc < 100 * UNIT  && ab > 2 * bc && ab < 200 * UNIT && ab >160 * UNIT) ||  //  quartiers rectangulaires moyens
		(ab > 50 * UNIT && ab < 70 * UNIT  && bc < 70 * UNIT  && bc > 50 * UNIT) || //  quartiers carr?s moyens
		(ab > 50 * UNIT && ab < 70 * UNIT  && bc > 3 * ab && bc < 210 * UNIT && bc >150 * UNIT) || (bc> 50 * UNIT && bc < 70 * UNIT  && ab > 3 * bc && ab < 210 * UNIT && ab >150 * UNIT) ||  //  quartiers rectangulaires ?tal?s moyens
		(ab > 50 * UNIT && ab < 80 * UNIT  && bc > 1.5*ab && bc < 120 * UNIT && bc > 75 * UNIT) || (bc > 50 * UNIT && bc < 80 * UNIT  && ab > 1.5*bc && ab < 120 * UNIT && ab > 75 * UNIT)) //  quartiers semi rectangulaires moyens
		createBuildingBlock();

	else if (ab > 120 * UNIT && ab > 2 * bc)
		verticalCut(ab, bc, cd, da, random);
	else if (da >  120 * UNIT && da > 2 * ab)
		horizontalCut(ab, bc, cd, da, random);
	else if (da > 30 * UNIT && ab > 30 * UNIT)
		createBuildingBlock();
	else
		drawEmptyGrassLot();
}



void drawSidewalk(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d) {

	//	Mobilier(7 * UNITE, 50 * UNITE, 0.3*UNITE).creerLampadaires(Quadrangle(_a, _b, _c, _d)); 
	//push in the 
	Vector::setCol(COL_TROTT1, COL_TROTT2, COL_TROTT3);
	PrismQuad(Quadrangle(_a, _b, _c, _d), 0.30*UNIT).Render(); // hauteur de 20 cm
	Vector::setColDefaut();
}

//########################################################################################################### CENTRE

Centre::Centre(const Centre& _centre) : type(_centre.type), positionCentre(_centre.positionCentre)
{}

Centre::Centre(const Vector &_a, const TypeCentre _type) : type(_type), positionCentre(_a)
{}

double Centre::getDistance(const Quadrangle &_q) const
{
	Vector centreQuadrangle((_q[0] + _q[1]) / 4 + (_q[3] + _q[2]) / 4);
	double distance = Norm(positionCentre - centreQuadrangle);
	return distance;
}

double Centre::getDistance(const Vector &_a, const Vector &_b, const Vector &_c)const
{
	Vector centreTriangle(((_a + _b) / 2 + _c) / 3);
	double distance = Norm(positionCentre - centreTriangle);

	return distance;
}

double Centre::getDistance(const Vector &_a, const Vector &_b, const Vector &_c, const Vector &_d)const
{
	Vector centreQuadrangle((_a + _b) / 4 + (_d + _c) / 4);

	double distance = Norm(positionCentre - centreQuadrangle);
	//std::cout<< distance << std::endl;

	return distance;
}

double Centre::getDistance(const Vector &_a, const Vector &_b, const Vector &_c, const Vector &_d, const Vector &_e)const
{
	Vector centreQuadrangle((_a + _b + _d + _c + _e) / 5);
	double distance = Norm(positionCentre - centreQuadrangle);

	return distance;
}

double Centre::getHauteur(const double &_distance) const
{
	//calculette grahique online : http://grapheur.cours-de-math.eu/
	double hauteur = 250 * (exp(6 / _distance) - 1);

	if (hauteur > 40) { hauteur = rand() % 15 + 40; }
	return hauteur;
}

TypeCentre Centre::getType() const { return type; }


//########################################################################################################### CITY

/*!
\brief Constructor of a city
*/
City::City() {}


void City::Generate()
{
	double x = 20 * UNIT; // x = 10  ->  1km?

	std::vector<Centre> centres;

	TypeCentre type1 = VILLE, type2 = INDUSTRIEL, type3 = RESIDENCE;
	//set location type so we can have different areas at different centers of the city
	centres.push_back(Centre(Vector(0, 0, 0), type1));

	//scope of the entire map
	Vector v[4];
	v[0] = Vector(-50 * x, -50 * x, 0);
	v[1] = Vector(50 * x, -50 * x, 0);
	v[2] = Vector(50 * x, 50 * x, 0);
	v[3] = Vector(-50 * x, 50 * x, 0);

	//begin rendering
	LandQuad(v[0], v[1], v[2], v[3], centres).Subdivide();
	
}

