#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Geode.h"
class Cube : public Geode
{
public:

	Cube();
	~Cube();

	void render(void);
	void simDraw(Matrix4);
};

#endif