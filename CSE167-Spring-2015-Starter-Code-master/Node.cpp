#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Node.h"
#include "Color.h"
#include "Matrix4.h"

Node::Node()
{
	radius = 1.0;
	center.set(0.0, 0.0, 0.0);
	newCenter.set(0.0, 0.0, 0.0);
}


Node::~Node()
{
}



void Node::translateSphere(float x, float y, float z) {
	center.set(center[0] + x, center[1] + y, center[2] + z);
}

void Node::scaleSphere(float factor) {
	radius = radius * factor;
}
