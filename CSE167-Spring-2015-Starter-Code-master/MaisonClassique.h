#ifndef __MaisonClassique__
#define __MaisonClassique__

#include <iostream>

#include "Maison.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Maison;

class MaisonClassique : public Maison
{
	public:
		MaisonClassique(const Triangle& t, const unsigned int& typeCentre, const double& heightMax);
		MaisonClassique(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		MaisonClassique(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax);
		~MaisonClassique(void);

		virtual void build(const Triangle& t);
		virtual void build(const Quadrangle& q);
		virtual void build(const Pentangle& p);

	protected :

		void setMaisonClassiqueInfos();

		virtual void buildEtages(const Triangle& t);
		virtual void buildFloors(const Quadrangle& q);
		virtual void buildEtages(const Pentangle& p);

};


#endif
