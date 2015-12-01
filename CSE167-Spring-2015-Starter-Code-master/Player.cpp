#include "Player.h"
#include "Globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int Player::playerCount = 0;
Vector4 noWhere(0, 0, 0, 0);
// Makes a player centered at x = 0, z = 0, on floor y = 0
Player::Player()
{
	boundsOn = false;
	cullOn = false;
	Matrix4 trans;
	//Begin by adding robot to our root
	this->addChild(&robot);
	robot.addChild(&fullBody);
	trans.makeTranslate(0.0, 3.5, 0.0);
	fullBody.M = trans;
	fullBody.radius = 3.55;

	//Then connect the parts of the robot. Translate is our last transform for these, so they go near the top
	robot.addChild(&headTranslate); // root -> robot -> headT
	robot.addChild(&torsoTranslate); // root -> robot -> torsoT
	robot.addChild(&leftLegTranslate); // root -> robot -> leftLT
	robot.addChild(&rightLegTranslate); // root -> robot -> rightLT
	robot.addChild(&leftArmTranslate); // root -> robot -> leftAT
	robot.addChild(&rightArmTranslate); // root -> robot -> rightAT

	/////////// Size the robot parts //////////////////////////////////////
	//Head - sphere diameter = 2
	headScale.scaleSphere(1.05);

	//Torso - cube size = (2, 3, 2)
	trans.makeScale(2.0, 3.0, 2.0);
	torsoScale.M = trans;
	torsoScale.radius = 2.0;

	//Arms and Legs - cube size = (1, 1, 2)
	trans.makeScale(0.5, 2.0, 1.0);
	leftArmScale.M = trans;
	leftArmScale.scaleSphere(1.2);
	leftLegScale.M = trans;
	leftLegScale.scaleSphere(1.2);
	rightArmScale.M = trans;
	rightArmScale.scaleSphere(1.2);
	rightLegScale.M = trans;
	rightLegScale.scaleSphere(1.2);


	/////////// Translate the robot parts /////////////////////////////////
	//Head - bottom of sphere at (0, 5, 0)/center at (0, 6, 0)
	trans.makeTranslate(0.0, 6.0, 0.0);
	headTranslate.M = trans;
	headTranslate.addChild(&headScale); // root -> robot -> headT -> headS

	//Torso - bottom at (0, 2, 0)/center at (0, 3.5, 0)
	trans.makeTranslate(0.0, 3.5, 0.0);
	torsoTranslate.M = trans;
	torsoTranslate.addChild(&torsoScale); // root -> robot -> torsoT -> torsoS

	//Left Leg
	trans.makeTranslate(-0.5, 1.0, 0.0);
	leftLegTranslate.M = trans;
	leftLegTranslate.addChild(&translateFromPivotLL); // root -> robot -> leftLT -> pivot(From)
	translateFromPivotLL.addChild(&leftLegRotate); // root -> robot -> leftLT -> pivot(From) -> leftLR
	leftLegRotate.addChild(&translateToPivotLL); // root -> robot -> leftLT -> pivot(From) -> leftLR -> pivot(To)
	translateToPivotLL.addChild(&leftLegScale); // root -> robot -> leftLT -> pivot(From) -> leftLR -> pivot(To) -> leftLS

	//Right Leg
	trans.makeTranslate(0.5, 1.0, 0.0);
	rightLegTranslate.M = trans;
	rightLegTranslate.addChild(&translateFromPivotRL); // root -> robot -> rightLT -> pivot(From)
	translateFromPivotRL.addChild(&rightLegRotate); // root -> robot -> rightLT -> pivot(From) -> rightLR
	rightLegRotate.addChild(&translateToPivotRL); // root -> robot -> rightLT -> pivot(From) -> rightLR -> pivot(To)
	translateToPivotRL.addChild(&rightLegScale); // root -> robot -> rightLT -> pivot(From) -> rightLR -> pivot(To) -> rightLS

	//Right Arm
	trans.makeTranslate(1.5, 4.0, 0.0);
	rightArmTranslate.M = trans;
	rightArmTranslate.addChild(&translateFromPivotRA); // root -> robot -> rightAT -> pivot(From)
	translateFromPivotRA.addChild(&rightArmRotate); // root -> robot -> rightAT -> pivot(From) -> rightAR
	rightArmRotate.addChild(&translateToPivotRA); // root -> robot -> rightAT -> pivot(From) -> rightAR -> pivot(To)
	translateToPivotRA.addChild(&rightArmScale); // root -> robot -> rightAT -> pivot(From) -> rightAR -> pivot(To) -> rightAS

	//Left Arm
	trans.makeTranslate(-1.5, 4.0, 0.0);
	leftArmTranslate.M = trans;
	leftArmTranslate.addChild(&translateFromPivotLA); // root -> robot -> leftAT -> pivot(From)
	translateFromPivotLA.addChild(&leftArmRotate); // root -> robot -> leftAT -> pivot(From) -> leftAR
	leftArmRotate.addChild(&translateToPivotLA); // root -> robot -> leftAT -> pivot(From) -> leftAR -> pivot(To)
	translateToPivotLA.addChild(&leftArmScale); // root -> robot -> leftAT -> pivot(From) -> leftAR -> pivot(To) -> leftAS

	/////////// Finally, set the translateToPivot and translateFromPivot, and connect the scales to their Geodes
	//translateToPivot
	trans.makeTranslate(0.0, -1.0, 0.0);
	translateToPivotLL.M = trans;
	translateToPivotRL.M = trans;
	translateToPivotLA.M = trans;
	translateToPivotRA.M = trans;

	//translateFromPivot
	trans.makeTranslate(0.0, 1.0, 0.0);
	translateFromPivotLL.M = trans;
	translateFromPivotRL.M = trans;
	translateFromPivotLA.M = trans;
	translateFromPivotRA.M = trans;

	//Connecting all Scale Nodes to their Geodes
	headScale.addChild(&baseSphere);
	torsoScale.addChild(&baseCube);
	leftArmScale.addChild(&baseCube);
	rightArmScale.addChild(&baseCube);
	leftLegScale.addChild(&baseCube);
	rightLegScale.addChild(&baseCube);


	//Set the color of our Geodes
	int time = glutGet(GLUT_ELAPSED_TIME);
	srand(time);
	float red, green, blue;
	red = (static_cast<float>(rand())) / ((RAND_MAX));
	green = (static_cast<float>(rand())) / ((RAND_MAX));
	blue = (static_cast<float>(rand())) / ((RAND_MAX));
	Color colorSph(red, green, blue);
	baseSphere.color = colorSph;

	red = (static_cast<float>(rand())) / ((RAND_MAX));
	green = (static_cast<float>(rand())) / ((RAND_MAX));
	blue = (static_cast<float>(rand())) / ((RAND_MAX));
	Color colorCub(red, green, blue);
	baseCube.color = colorCub;

	
	velocity = noWhere;
	acceleration = noWhere;
	jumping = false;
	kicking = false;
	Vector4 faceDir(0, 0, 1);
	faceDirection = faceDir;
	frequency = 0;
	rekt = false;
	Player::playerCount++;
	playerID = Player::playerCount;
}


Player::~Player()
{

}


void Player::drawPlayer() {

	this->simDraw(this->M);
	if (boundsOn) {
		leftLegScale.drawWireSphere();
		rightLegScale.drawWireSphere();
		leftArmScale.drawWireSphere();
		rightArmScale.drawWireSphere();
		headScale.drawWireSphere();
		torsoScale.drawWireSphere();
		fullBody.drawWireSphere();
	}
	if (cullOn) {
		Camera cam = Globals::camera;
		Vector3 topLeftFrontPoint = cam.nearPlane[0];
		Vector3 botRightBackPoint = cam.farPlane[3];

		Vector3 topLeftFrontTest = fullBody.newCenter - topLeftFrontPoint;
		Vector3 botRightBackTest = fullBody.newCenter - botRightBackPoint;

		float distTop = topLeftFrontTest.dot(cam.normTop);
		float distLeft = topLeftFrontTest.dot(cam.normLeft);
		float distFront = topLeftFrontTest.dot(cam.normFront);
		float distBot = botRightBackTest.dot(cam.normBot);
		float distRight = botRightBackTest.dot(cam.normRight);
		float distBack = botRightBackTest.dot(cam.normBack);

		if (distTop < fullBody.radius && distLeft < fullBody.radius && distFront < fullBody.radius &&
			distBot < fullBody.radius && distRight < fullBody.radius && distBack < fullBody.radius) {

			this->draw(this->M);
		}
	}
	else {
		this->draw(this->M);
	}
}

void Player::initiateJump() {
	// If the player is on the ground, do it
	if (!jumping && !kicking) {
		Vector4 velVec(0, 0.09, 0);
		velocity = velVec;
		Vector4 accVec(0, -0.0005, 0);
		acceleration = accVec;
		jumping = true;
		updateJump();
		//std::cout << "start" << std::endl;
	}
	return;
}

void Player::updateJump() {
	Matrix4 trans;
	if (this->M.get(3, 1) < 0) {
		acceleration = noWhere;
		velocity = noWhere;
		trans.makeTranslate(0, -1 * this->M.get(3, 1), 0);
		this->M = trans * this->M;
		jumping = false;
		kicking = false;
		//std::cout << "stop jump" << std::endl;
	}
	if(jumping && !kicking) {
		trans.makeTranslate(velocity[0], velocity[1], velocity[2]);
		this->M = trans * this->M;
		velocity = velocity.add(acceleration);
		//std::cout << "jumping" << std::endl;
	}
}

void Player::initiateKick() {
	if (jumping && !kicking) {
		jumping = false;
		kicking = true;
		Vector4 velVec(0.1*faceDirection[0], -0.1, 0.1*faceDirection[2]);
		velocity = velVec;
		updateKick();
		//std::cout << "start kick" << std::endl;
	}
	return;
}

void Player::updateKick() {
	Matrix4 trans;
	if (this->M.get(3, 1) < 0) {
		velocity = noWhere;
		acceleration = noWhere;
		trans.makeTranslate(0, -1 * this->M.get(3, 1), 0);
		this->M = trans * this->M;
		jumping = false;
		kicking = false;
		//std::cout << "stop kick" << std::endl;
	}
	if (kicking) {
		if (this->M.get(3, 1) < 0.15) {
			trans.makeTranslate(velocity[0] / 10.0, velocity[1] / 10.0, velocity[2] / 10.0);
		}
		else {
			trans.makeTranslate(velocity[0] * 2.0, velocity[1] * 2.0, velocity[2] * 2.0);
		}
		this->M = trans * this->M;
		//std::cout << "kicking" << std::endl;
		if (this->M.get(3, 1) < 0) {
			velocity = noWhere;
			acceleration = noWhere;
			trans.makeTranslate(0, -1 * this->M.get(3, 1), 0);
			this->M = trans * this->M;
			jumping = false;
			kicking = false;
			enemy->rekt = false;
			enemy->fullBody.collided = false;
			leftLegScale.collided = false;
			//std::cout << "stop kick" << std::endl;
			return;
		}

		// check if you have kicked an enemy
		if (enemy != NULL && !enemy->kicking) {
			// find the enemy's body's center coordinates
			Vector4 enemyPos(enemy->fullBody.newCenter[0], 
				enemy->fullBody.newCenter[1], 
				enemy->fullBody.newCenter[2], 
				0);
			// find our left (kicking) leg's center coordinates
			Vector4 myPos(leftLegScale.newCenter[0],
				leftLegScale.newCenter[1],
				leftLegScale.newCenter[2],
				0);
			// find the vector from ourLeg to the enemy body
			Vector4 meToEnemy = enemyPos - myPos;
			
			// see if that vector's magnitude is less than the radius of enemy body and our leg combined
			if (meToEnemy.toVector3().magnitude() < enemy->fullBody.radius + leftLegScale.radius) {
				enemy->velocity.set(-1 * faceDirection[0], -1, -1 * faceDirection[2], 0);
				if (enemy->rekt == false) {
					std::cout << "Player " << enemy->playerID << " got REEEEEEEKT" << std::endl;
				}
				enemy->rekt = true;
				enemy->fullBody.collided = true;
				leftLegScale.collided = true;
			}
			else {
				enemy->rekt = false;
				enemy->fullBody.collided = false;
				leftLegScale.collided = false;
			}
		} // end collision check
	} // end if(kicking)
}


void Player::update() {
	if (frequency == 0) {
		updateJump();
		if (kicking) {
			updateKick();
		}
		frequency++;
	}
	else if (frequency == 5) {
		frequency = 0;
	}
	else {
		frequency++;
	}
	Matrix4 trans;
	if (jumping) {
		trans.makeRotateX(1.0472);
		leftLegRotate.M = trans;
		rightArmRotate.M = trans;

		trans.makeRotateX(-1.0472);
		rightLegRotate.M = trans;
		leftArmRotate.M = trans;
	}
	else if (kicking) {
		trans.makeRotateX(-1.0472);
		leftLegRotate.M = trans;
		rightArmRotate.M = trans;

		trans.makeRotateX(1.0472);
		rightLegRotate.M = trans;
		leftArmRotate.M = trans;
	}
	else {
		trans.identity();
		leftLegRotate.M = trans;
		rightArmRotate.M = trans;
		rightLegRotate.M = trans;
		leftArmRotate.M = trans;
	}
}