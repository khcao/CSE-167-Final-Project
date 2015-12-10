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
		fire[i].age = rand() % 10 + 1;
		fire[i].pos = Vector3(rand() % 2, 0, rand() % 1);
		fire[i].lifetime = rand() % 10 + 1;
		fire[i].velocity = Vector3(0, 0, 0);
	}
}

void FireParticleSystem::updateFire() {

	for (int i = 0; i<num_fire; i++) {
		if (fire[i].age > fire[i].lifetime) { 
			fire[i].pos = Vector3(rand() % 2, 0, rand() % 1);
			fire[i].velocity = Vector3(0, 0, 0);
			//age reset
			fire[i].age = 0;
		}
		else {
			//width of the flame
			int velocityRange = 40;
			float scalingCoefficient = .5;

			float dvx = 0.01*(rand() % velocityRange + 1);
			bool posNegX = rand() % 2;

			float dvz = 0.01*(rand() % velocityRange + 1);
			bool posNegZ = rand() % 2;

			float x = fire[i].pos.get(0);
			float y = fire[i].pos.get(1);
			float z = fire[i].pos.get(2);

			float vx = fire[i].velocity.get(0);
			float vy = fire[i].velocity.get(1);
			float vz = fire[i].velocity.get(2);

			x += vx;
			y += vy;
			z += vz;


			vx = scalingCoefficient* ((posNegX) ? dvx : -dvx);
			vy = scalingCoefficient*(0.01*(rand() % 80 + 1));
			vz = scalingCoefficient* ((posNegZ) ? dvz : -dvz);


			fire[i].pos = Vector3(x, y, z);
			fire[i].velocity = Vector3(vx, vy, vz);

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