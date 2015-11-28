#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Geode.h"

Geode::Geode()
{
}


Geode::~Geode()
{
}

void Geode::draw(Matrix4 C) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(C.ptr());

	render();

	glPopMatrix();
}

void Geode::simDraw(Matrix4 C) {

}

void Geode::update() {

}