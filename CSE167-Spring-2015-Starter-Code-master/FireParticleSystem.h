#ifndef CSE167_FIRE_PARTICLE_SYSTEM_h
#define CSE167_FIRE_PARTICLE_SYSTEM_h
#include "Geode.h"
#include "Vector3.h"
#include "Vector4.h"
struct Particle {
	Vector3 pos;
	Vector3 vel;
	Vector4 color;
	float rotate;
	float age;
	float lifetime;

	Particle() {
		pos = Vector3(0, 0, 0);
		vel = Vector3(0, 0, 0);
		color = Vector4(1, 1, 1, 1);
		age = 0;
		lifetime = 0;
	}
};
class FireParticleSystem : public Geode
{
public:

private:  int nParticles;
		  float time, deltaT;
		  int playerNumber;
public:
	void initializeFire(int);
	void updateFire();
	void drawFire();

	void render(void);
};

#endif