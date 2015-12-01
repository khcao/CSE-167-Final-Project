#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include "Geode.h"
class Sphere : public Geode
{
public:
	Vector4 tLB, tLF, tRB, tRF, bLB, bLF, bRB, bRF;

	Sphere();
	~Sphere();

	void render(void);
	void simDraw(Matrix4);
};

#endif