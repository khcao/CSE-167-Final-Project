#ifndef CSE167_MatrixTransform_h
#define CSE167_MatrixTransform_h

#include "Group.h"
#include "Matrix4.h"
#include "Vector3.h"
class MatrixTransform : public Group
{
public:
	Matrix4 M;
	float pendulum = 0.0;
	float moving = 0.0;
	float turning = 0.0;

	MatrixTransform();
	~MatrixTransform();

	void draw(Matrix4);
	void update();
	void drawWireSphere();
	void drawWireCube();

	void simDraw(Matrix4);
};

#endif