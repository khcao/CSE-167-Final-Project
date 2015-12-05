#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Sphere.h"
#include "Color.h"
#include <cstdlib>
#include <math.h>

Sphere::Sphere()
{ 
	float red, green, blue;
	red = (static_cast<float>(rand())) / ((RAND_MAX));
	green = (static_cast<float>(rand())) / ((RAND_MAX));
	blue = (static_cast<float>(rand())) / ((RAND_MAX));

	Color colorNew(red, green, blue);
	color = colorNew;
	glColor3fv(color.ptr());
}


Sphere::~Sphere()
{

}

void Sphere::render() {
	//glColor3fv(this->color.ptr());
	glutSolidSphere(1.0, 80, 80);
}

void Sphere::simDraw(Matrix4 C) {

}