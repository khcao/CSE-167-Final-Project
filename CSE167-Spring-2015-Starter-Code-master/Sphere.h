#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include "Geode.h"
class Sphere : public Geode
{
public:

	Sphere();
	~Sphere();

	void render(void);
	void simDraw(Matrix4);
};

#endif