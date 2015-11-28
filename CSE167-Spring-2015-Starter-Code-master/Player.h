#ifndef CSE167_Player_h
#define CSE167_Player_h

#include "MatrixTransform.h"
#include "Sphere.h"
#include "Cube.h"
#include "Vector4.h"
#include "Matrix4.h"
class Player :
	public MatrixTransform
{
public:
	MatrixTransform robot, fullBody;
	MatrixTransform torsoScale, torsoTranslate;
	MatrixTransform headScale, headTranslate;
	MatrixTransform leftLegScale, translateToPivotLL, leftLegRotate, translateFromPivotLL, leftLegTranslate;
	MatrixTransform rightLegScale, translateToPivotRL, rightLegRotate, translateFromPivotRL, rightLegTranslate;
	MatrixTransform leftArmScale, translateToPivotLA, leftArmRotate, translateFromPivotLA, leftArmTranslate;
	MatrixTransform rightArmScale, translateToPivotRA, rightArmRotate, translateFromPivotRA, rightArmTranslate;

	Sphere baseSphere;
	Cube baseCube;

	bool boundsOn;
	bool cullOn;
	Vector4 velocity;
	Vector4 acceleration;
	bool jumping;
	bool kicking;
	Vector4 faceDirection;

	Player();
	~Player();

	void drawPlayer(void);
	void initiateJump(void);
	void updateJump(void);
	void initiateKick(void);
	void updateKick(void);
};

#endif