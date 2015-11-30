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

	bool boundsOn; // boolean to draw bounding boxes
	bool cullOn; // boolean to allow culling of the player
	Vector4 velocity; // the velocity of the player - determines the next position (in relation to the current position) in the next frame
	Vector4 acceleration; // the acceleration of the player - determines the next velocity in the next frame
	bool jumping; // indicates whether in a jumping sequence
	bool kicking; // indicates whether in a kicking sequence
	Vector4 faceDirection; // determines the facing direction of the character - should be normalized (since only direction is changed)
	int frequency; // used for updates on the player
	Player * enemy; // holds a pointer to the opposite player
	bool rekt; // indicates whether the player has been divekicked (receiver of the kick) or not

	static int playerCount;
	int playerID;
	

	Player();
	~Player();

	void drawPlayer(void); // correctly draws the player - call this instead of draw(M);
	void initiateJump(void); // used to initiate a jump sequence
	void updateJump(void); // used to update the player during jump sequence
	void initiateKick(void); // used to initiate a kick, should be during jumping
	void updateKick(void); // used to update the player during kick sequence
	void update(void); // updates variables - use this in idlecallback
};

#endif