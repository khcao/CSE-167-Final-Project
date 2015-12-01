#ifndef __Maison__
#define __Maison__

#include <iostream>

#include "BaseBuilding.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class BaseBuilding;

class Maison : public BaseBuilding
{
	public:
		Maison(const Triangle& t, const unsigned int& typeCentre, const double& heightMax);
		Maison(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		Maison(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax);
		~Maison(void);

		static void choixBatiment(const Triangle& t, const unsigned int& typeCentre, const double& heightMax);
		static void chooseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		static void choixBatiment(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax);

		virtual void build(const Triangle& t) =0;
		virtual void build(const Quadrangle& q) =0;
		virtual void build(const Pentangle& p) =0;

	protected :

		bool garage;

		void setMaisonInfos();

		virtual void buildEtages(const Triangle& t) =0;
		virtual void buildFloors(const Quadrangle& q) =0;
		virtual void buildEtages(const Pentangle& p) =0;

};

#endif
