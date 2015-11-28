#ifndef CSE167_Node_h
#define CSE167_Node_h

#include "Matrix4.h"
#include "Vector3.h"

class Node
{
public:
	Vector3 center;
	float radius;
	Vector3 newCenter;

	Node();
	~Node();
	virtual void draw(Matrix4 C) = 0;
	virtual void update() = 0;
	//virtual void drawWireSphere();
	void translateSphere(float, float, float);
	void scaleSphere(float);

	virtual void simDraw(Matrix4) = 0;
};

#endif