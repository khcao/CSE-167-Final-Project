// Changelog 14.02.2001

#ifndef __City__ 
#define __City__

#include <vector>
#include "geometry.h"
#include "shape.h"


#include "mobilierUrbain.h"

#include "BuildingBlock.h"
#include "Globals.h"

#define UNIT 1/4 //soit 1 m?tre, on pourra la modifier plus tard

enum TypeCentre { VILLE = 0, RESIDENCE = 1, INDUSTRIEL = 2 };

class Centre {

public:

	Centre(const Centre& _centre);
	Centre(const Vector &, const TypeCentre);

	double getDistance(const Quadrangle &_q) const;
	double getDistance(const Vector &, const Vector &, const Vector &) const;
	double getDistance(const Vector &, const Vector &, const Vector &, const Vector &) const;
	double getDistance(const Vector &, const Vector &, const Vector &, const Vector &, const Vector &) const;
	double getHauteur(const double &) const;
	TypeCentre getType() const;

private:

	Vector positionCentre;
	TypeCentre type;
};



class BlockQuad :public Quadrangle {
protected:
public:
	BlockQuad(const Vector&, const Vector&, const Vector&, const Vector&, const std::vector<Centre>&);
	void Subdivide();
	std::vector<Centre> centres;
};


class LandQuad :public Quadrangle {
protected:
public:
	void drawEmptyGrassLot();
	LandQuad(const Vector&, const Vector&, const Vector&, const Vector&, const std::vector<Centre>&);
	void Subdivide();
	void createBuildingBlock();
	//void Subdivise();

	void verticalCut(double ab, double bc, double cd, double da, double random);
	void horizontalCut(double ab, double bc, double cd, double da, double random);

	bool is_point_in_rectangle(Vector& p);
	std::vector<Centre> centres;
};



class City {

public:
	City();
	void Generate();
	static bool shouldCull(Vector4);
};


#else
class Centre; //laisser cette ligne -> pour la 3?me partie
#endif