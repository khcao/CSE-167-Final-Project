#include "FireParticleSystem.h"

#include <vector>
#include "Globals.h"
#include <GL/glut.h>
using namespace std;
static int num_fire = 4000;
static vector<Particle> fire(num_fire, Particle());
void FireParticleSystem::initializeFire(int playerNum) {
	playerNumber = playerNum;
	for (int i = 0; i<num_fire; i++) {
		fire[i].pos = Vector3(rand() % 2, 0, rand() % 1);
		fire[i].vel = Vector3(0, 0, 0);
		fire[i].age = rand() % 10 + 1;
		fire[i].lifetime = rand() % 10 + 1;
	}
}

void FireParticleSystem::updateFire() {

	for (int i = 0; i<num_fire; i++) {
		if (fire[i].age > fire[i].lifetime) { // reset particle when reaching end of life
			fire[i].pos = Vector3(rand() % 2, 0, rand() % 1);
			fire[i].vel = Vector3(0, 0, 0);
			fire[i].age = 0;
		}
		else {
			float x = fire[i].pos.get(0);
			float y = fire[i].pos.get(1);
			float z = fire[i].pos.get(2);

			float vx = fire[i].vel.get(0);
			float vy = fire[i].vel.get(1);
			float vz = fire[i].vel.get(2);

			x += vx;
			y += vy;
			z += vz;

			float pos_vx = 0.01*(rand() % 100 + 1);
			float neg_vx = -0.01*(rand() % 100 + 1);
			bool pick_pos_vx = rand() % 2;

			float pos_vz = 0.01*(rand() % 100 + 1);
			float neg_vz = -0.01*(rand() % 100 + 1);
			bool pick_pos_vz = rand() % 2;


			vx = 0.5* ((pick_pos_vx) ? pos_vx : neg_vx);
			//y is straight up
			vy = 0.5*(0.01*(rand() % 200 + 1));
			vz = 0.5* ((pick_pos_vz) ? pos_vz : neg_vz);


			fire[i].pos = Vector3(x, y, z);
			fire[i].vel = Vector3(vx, vy, vz);

			fire[i].age += 0.2;
		}
	}
}

void FireParticleSystem::drawFire() {
	glEnable(GL_POINT_SMOOTH);
	glPointSize(1);

	glBegin(GL_POINTS);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int i = 0; i<num_fire; i++) {
	//	float alphaChannel = ((float)(rand() % 80)) / 100.0f;
	float r = 1 - .60*fire[i].age / fire[i].lifetime;
	float g = rand() % 2 * (1 - .60*fire[i].age / fire[i].lifetime);
	if (r < .2 && g < .2)
	continue;
	glColor4f(r,g, 0,0);
	glVertex3f(fire[i].pos.get(0), fire[i].pos.get(1), fire[i].pos.get(2));
	}
	glVertex3f(fire[0].pos.get(0), fire[0].pos.get(1), fire[0].pos.get(2));
	glEnd();
}

void FireParticleSystem::render() {
	if (playerNumber == 1 && Globals::player1Kicking) {
	updateFire();
	drawFire();
}
else if (playerNumber == 2 && Globals::player2Kicking) {
	updateFire();
	drawFire();
}
}