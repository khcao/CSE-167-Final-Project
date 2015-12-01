#ifndef __Batiment__
#define __Batiment__

#include <vector>
#include "city.h"
#include "geometry.h"
#include "FloorWindow.h"

class FloorWindow;

/**
@class Classe de base pour toutes les constructions.
*/
class BaseBuilding
{
	public:

		BaseBuilding(const Triangle& t, const unsigned int& typeCentre, const double& heightMax);
		BaseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		BaseBuilding(const Pentangle& p, const unsigned int& typeCentre, const double& heightMax);
		~BaseBuilding(void);

		static void chooseBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& heightMax);
		

		/** @brief maison o� entrep�ts */
		static double getDefaultHeight();

		virtual void build(const Quadrangle& q) =0;

		unsigned int getNumberFloorsMax();

		static std::vector <double> ToitPyramideCoupe;
		static std::vector <double> ToitPyramide;
		static std::vector <double> PrismRoof;

	protected :
		int seed;
		unsigned int numOfFloorsGroundFloor; /** hauteur du RDC = un nombre d'�tages */

		bool separation; /** PAS ENCORE UTILISE */

		unsigned int type; /** le type du batiment */
		unsigned int numberOfMaxFloors;
		double windowHeight;
		double height; /** hauteur max */
		bool creerFenetre; /** si vrai, alors on cr�e des fen�tres **/

		std::vector<Vector> listPoints;

		double airMin; /** au minimum  = 3 unit�s� (� peu pr�s 16m�) */

		FloorWindow* floorWindow;

		virtual void buildFloors(const Quadrangle& q) =0;
	
		//-------------------------------- M�thodes de construction ------------------------>

		//le rez-de-chauss�
		void createGroundFloor(const unsigned int& _nbEtages);

		//un �tage
		void createFloors(const unsigned int& _nbEtages, const unsigned int& etageActu);
		void createSimpleFloors(const unsigned int& _nbEtages);

		void creerToitPyramideCoupe();
		void createPyramidRoof();

		/**
		* @param ajouterCheminer si vrai, ajoute un carr� sur l'avant du to�t pour repr�senter une chemin�e
		*/
		void creerToitPrisme(bool ajouterCheminer = true);

		//------------------------------------- Autres --------------------------------->

		/**
		* @brief r�tr�cie la distance entre plusieurs vecteurs et un point central invariant (= moyenne des points invariants)
		* @param invariants les vecteurs invariant (il en faut au moins 1)
		* @param variants les vecteurs qui vont subir le r�tr�cissement (il en faut au moins 1)
		*/
		void scaleXY(const double& facteur, const Vector& invariants, std::vector<Vector>& variants) const;
		void scaleXY(const double& facteur, const Vector& invariants, Vector& variants) const;

	private :
		void setBuildingColor();
		/** @brief Calcul la hauteur maximal selon la proximit� et l'importance des Centres */
		void setheightMax(const double& distTotVersCentres, const std::vector<Centre>& centres, const unsigned int& nbVecteurs);

		void setBuildingInfo(const unsigned int& typeCentre, const double& heightMax);

};
#else
class BaseBuilding;
#endif;
