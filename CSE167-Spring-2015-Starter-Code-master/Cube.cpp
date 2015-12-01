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

	Color color(red, green, blue);
	glColor3fv(color.ptr());

	tLB.set(-0.5, 0.5, -0.5, 1);
	tLF.set(-0.5, 0.5, 0.5, 1);
	tRB.set(0.5, 0.5, -0.5, 1);
	tRF.set(0.5, 0.5, 0.5, 1);

	bLB.set(-0.5, -0.5, -0.5, 1);
	bLF.set(-0.5, -0.5, 0.5, 1);
	bRB.set(0.5, -0.5, -0.5, 1);
	bRF.set(0.5, -0.5, 0.5, 1);
}


Cube::~Cube()
{
}

void Cube::render() {
	glColor3fv(this->color.ptr());
	glutSolidCube(1.0);
}

void Cube::simDraw(Matrix4 C) {
	// apply C to all points
	tLB = C * tLB;
	tLF = C * tLF;
	tRB = C * tRB;
	tRF = C * tRF;

	bLB = C * bLB;
	bLF = C * bLF;
	bRB = C * bRB;
	bRF = C * bRF;

	// check here the min's max's
	maxX = std::fmax(  std::fmax( std::fmax(tLB[0], tLF[0]), std::fmax(tRB[0], tRF[0]) ), 
		std::fmax(std::fmax(bLB[0], bLF[0]), std::fmax(bRB[0], bRF[0])));
	maxY = std::fmax(std::fmax(std::fmax(tLB[1], tLF[1]), std::fmax(tRB[1], tRF[1])),
		std::fmax(std::fmax(bLB[1], bLF[1]), std::fmax(bRB[1], bRF[1])));
	maxZ = std::fmax(std::fmax(std::fmax(tLB[2], tLF[2]), std::fmax(tRB[2], tRF[2])),
		std::fmax(std::fmax(bLB[2], bLF[2]), std::fmax(bRB[2], bRF[2])));

	minX = std::fmin(std::fmin(std::fmin(tLB[0], tLF[0]), std::fmin(tRB[0], tRF[0])),
		std::fmin(std::fmin(bLB[0], bLF[0]), std::fmin(bRB[0], bRF[0])));
	minY = std::fmin(std::fmin(std::fmin(tLB[1], tLF[1]), std::fmin(tRB[1], tRF[1])),
		std::fmin(std::fmin(bLB[1], bLF[1]), std::fmin(bRB[1], bRF[1])));
	minZ = std::fmin(std::fmin(std::fmin(tLB[2], tLF[2]), std::fmin(tRB[2], tRF[2])),
		std::fmin(std::fmin(bLB[2], bLF[2]), std::fmin(bRB[2], bRF[2])));

	// reset all the points
	tLB.set(-0.5, 0.5, -0.5, 1);
	tLF.set(-0.5, 0.5, 0.5, 1);
	tRB.set(0.5, 0.5, -0.5, 1);
	tRF.set(0.5, 0.5, 0.5, 1);

	bLB.set(-0.5, -0.5, -0.5, 1);
	bLF.set(-0.5, -0.5, 0.5, 1);
	bRB.set(0.5, -0.5, -0.5, 1);
	bRF.set(0.5, -0.5, 0.5, 1);
}