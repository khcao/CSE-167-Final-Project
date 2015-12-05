#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Cube.h"
#include "Color.h"
#include <cstdlib>
#include <math.h>

Cube::Cube()
{
	float red, green, blue;
	red = (static_cast<float>(rand())) / ((RAND_MAX));
	green = (static_cast<float>(rand())) / ((RAND_MAX));
	blue = (static_cast<float>(rand())) / ((RAND_MAX));

	Color colorNew(red, green, blue);
	color = colorNew;
	glColor3fv(color.ptr());
}


Cube::~Cube()
{
}

void Cube::render() {
	//glColor3fv(this->color.ptr());
	glutSolidCube(1.0);
}

void Cube::simDraw(Matrix4 C) {
	
}