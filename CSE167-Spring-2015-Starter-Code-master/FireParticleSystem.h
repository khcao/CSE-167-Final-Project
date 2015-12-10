#ifndef CSE167_FIRE_PARTICLE_SYSTEM_h
#define CSE167_FIRE_PARTICLE_SYSTEM_h
#include "Geode.h"
#include "Vector3.h"
#include "Vector4.h"
struct Particle {
	Vector3 pos;
	Vector4 color;
	float age;
	float lifetime;
	Vector3 velocity;

	Particle() {
		color = Vector4(0, 0, 0, 0);
		pos = Vector3(0, 0, 0);
		lifetime = 0;
		velocity = Vector3(0, 0, 0);
		age = 0;
	}
};
class FireParticleSystem : public Geode
{
public:

private:  int numOfParticles;
		  float time, changeInTime;
		  int playerNumber;
public:
	void initializeFire(int);
	void updateFire();
	void drawFire();

	void render(void);
};

#endif