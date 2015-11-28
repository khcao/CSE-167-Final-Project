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
	color = color.green();
	glColor3fv(color.ptr());
	glutWireSphere(radius, 10, 10);

	glPopMatrix();

}