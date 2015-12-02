#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "MatrixTransform.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"

bool incrementBool; bool letsTurn; bool letsMove;
MatrixTransform::MatrixTransform()
{
	this->pendulum = 0.0;
	this->moving = 0.0;
	this->turning = 0.0;
	Matrix4 trans;
	trans.identity();
	this->M = trans;
	incrementBool = true;
	letsTurn = true;
	letsMove = false;
}


MatrixTransform::~MatrixTransform()
{
}

void MatrixTransform::draw(Matrix4 C) {
	C = C * this->M;
	Group::draw(C);
}

void MatrixTransform::simDraw(Matrix4 C) {
	C = C * this->M;
	Vector4 center4 = this->center.toVector4(1);
	this->newCenter = (C * center4).toVector3();
	simC = C;
	Group::simDraw(C);
}

void MatrixTransform::update() {
	if (pendulum >= 1.0) {
		incrementBool = false;
	}
	else if (pendulum <= -1.0) {
		incrementBool = true;
	}

	if (incrementBool == true) {
		pendulum = pendulum + 0.005;
	}
	else {
		pendulum = pendulum - 0.005;
	}
}


void MatrixTransform::drawWireSphere() {
	glMatrixMode(GL_MODELVIEW);

	Matrix4 trans;
	trans.makeTranslate(newCenter[0], newCenter[1], newCenter[2]);

	glPushMatrix();
	glMultMatrixf(trans.ptr());


	Color color;
	if (collided) {
		color = color.red();
	}
	else {
		color = color.green();
	}
	glColor3fv(color.ptr());
	glutWireSphere(radius, 10, 10);

	glPopMatrix();

}

void MatrixTransform::drawWireCubeFromCube() {
	Vector4 tLB, tLF, tRB, tRF, bLB, bLF, bRB, bRF;

	tLB.set(-0.5, 0.5, -0.5, 1);
	tLF.set(-0.5, 0.5, 0.5, 1);
	tRB.set(0.5, 0.5, -0.5, 1);
	tRF.set(0.5, 0.5, 0.5, 1);

	bLB.set(-0.5, -0.5, -0.5, 1);
	bLF.set(-0.5, -0.5, 0.5, 1);
	bRB.set(0.5, -0.5, -0.5, 1);
	bRF.set(0.5, -0.5, 0.5, 1);

	tLB = simC * tLB;
	tLF = simC * tLF;
	tRB = simC * tRB;
	tRF = simC * tRF;

	bLB = simC * bLB;
	bLF = simC * bLF;
	bRB = simC * bRB;
	bRF = simC * bRF;

	// check here the min's max's
	maxX = std::fmax(std::fmax(std::fmax(tLB[0], tLF[0]), std::fmax(tRB[0], tRF[0])),
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

	// draw the transparent cube
	glMatrixMode(GL_MODELVIEW);
	Matrix4 trans;
	trans.identity();
	glPushMatrix();
	glMultMatrixf(trans.ptr());
	if (collided) {
		Color color(1.0, 0.0, 0.0);
		glColor3fv(color.ptr());
	}
	else {
		Color color(0.0, 1.0, 0.0);
		glColor3fv(color.ptr());
	}
	glBegin(GL_LINES);
	// lines touching bot, left, back
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ); //
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, maxY, minZ); //
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ); //
	// lines touching top, left, front
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ); //
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, minY, maxZ); //
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(maxX, maxY, maxZ); //
	// lines touching bot, right, front
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ); //
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ); //
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, minY, minZ); //
	// lines touching top, right, back
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ); //
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ); //
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, minY, minZ); //
	glEnd();
	glPopMatrix();

}

void MatrixTransform::drawWireCubeFromSphere() {
	maxX = newCenter[0] + radius;
	minX = newCenter[0] - radius;

	maxY = newCenter[1] + radius;
	minY = newCenter[1] - radius;

	maxZ = newCenter[2] + radius;
	minZ = newCenter[2] - radius;

	// draw the transparent cube
	glMatrixMode(GL_MODELVIEW);
	Matrix4 trans;
	trans.identity();
	glPushMatrix();
	glMultMatrixf(trans.ptr());
	if (collided) {
		Color color(1.0, 0.0, 0.0);
		glColor3fv(color.ptr());
	}
	else {
		Color color(0.0, 1.0, 0.0);
		glColor3fv(color.ptr());
	}
	glBegin(GL_LINES);
	// lines touching bot, left, back
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ); //
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, maxY, minZ); //
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ); //
	// lines touching top, left, front
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ); //
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, minY, maxZ); //
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(maxX, maxY, maxZ); //
	// lines touching bot, right, front
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ); //
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ); //
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, minY, minZ); //
	// lines touching top, right, back
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ); //
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ); //
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, minY, minZ); //
	glEnd();
	glPopMatrix();
}