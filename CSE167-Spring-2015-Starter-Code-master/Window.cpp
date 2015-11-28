#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"
#include "MatrixTransform.h"
#include "Sphere.h"
#include "Group.h"
#include "Player.h"
#include <algorithm>

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

float prevFrameTime = glutGet(GLUT_ELAPSED_TIME);
float fps = 0, frame = 0;
int lightControl = 0;

Light * currLight = &Globals::pointLight;

Group root;
Sphere baseSphere;
Cube baseCube;
Player player1;
bool boundsOn = false;
bool cullOn = true;
float frustumFOVFactor = 1.0;

void Window::initialize(void)
{
    //Setup the light
	Vector4 lightPos(0.0, 20.0, 3.0, 1.0);
	Color ambLight(1.0, 1.0, 1.0, 1.0);
	Color difLight(1.0, 1.0, 1.0, 1.0);
	Color spcLight(1.0, 1.0, 1.0, 1.0);
	Globals::directionalLight.ambientColor = ambLight;
	Globals::directionalLight.diffuseColor = difLight;
	Globals::directionalLight.specularColor = spcLight;
	Globals::directionalLight.position = lightPos;

	Vector4 lightPos1(0.0, 0.0, 11.0, 1.0);
	Color ambLight1(1.0, 1.0, 1.0, 1.0);
	Color difLight1(1.0, 1.0, 1.0, 1.0);
	Color spcLight1(1.0, 1.0, 1.0, 1.0);
	Globals::pointLight.position = lightPos1;
	Globals::pointLight.ambientColor = ambLight1;
	Globals::pointLight.diffuseColor = difLight1;
	Globals::pointLight.specularColor = spcLight1;
	Globals::pointLight.quadraticAttenuation = 0.05;

	Vector4 sLightPos(0.0, 8.0, 4.0, 1.0);
	Globals::spotLight.position = sLightPos;
	Color ambLight2(1.0, 1.0, 1.0, 1.0);
	Color difLight2(1.0, 1.0, 1.0, 1.0);
	Color spcLight2(1.0, 1.0, 1.0, 1.0);
	Globals::spotLight.ambientColor = ambLight2;
	Globals::spotLight.diffuseColor = difLight2;
	Globals::spotLight.specularColor = spcLight2;
	Globals::spotLight.quadraticAttenuation = 0.1;


	/////////// Begin Scene ///////////////////////////////////////////////
	Matrix4 trans;
	//Begin by adding robot to our root
	root.addChild(&player1);
	
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
int frequency = 0;
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
	// rotate the arms and legs
	//player1.robot.update();
	// if we jump, update that
	if (frequency == 0) {
		player1.updateJump();
		if (player1.kicking) {
			player1.updateKick();
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
	if (player1.jumping) {
		trans.makeRotateX(1.0472);
		player1.leftLegRotate.M = trans;
		player1.rightArmRotate.M = trans;

		trans.makeRotateX(-1.0472);
		player1.rightLegRotate.M = trans;
		player1.leftArmRotate.M = trans;
	}
	else if (player1.kicking) {
		trans.makeRotateX(-1.0472);
		player1.leftLegRotate.M = trans;
		player1.rightArmRotate.M = trans;

		trans.makeRotateX(1.0472);
		player1.rightLegRotate.M = trans;
		player1.leftArmRotate.M = trans;
	}
	else {
		trans.identity();
		player1.leftLegRotate.M = trans;
		player1.rightArmRotate.M = trans;
		player1.rightLegRotate.M = trans;
		player1.leftArmRotate.M = trans;
	}
	/*trans.makeRotateX(1.0472 * robot.pendulum);
	leftLegRotate.M = trans;
	rightArmRotate.M = trans;

	trans.makeRotateX(-1.0472 * robot.pendulum);
	rightLegRotate.M = trans;
	leftArmRotate.M = trans;*/

	//trans.makeRotateY(0.0005);
	//player1.M = trans * player1.M;
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
	Globals::camera.nearD = 1.0;
	Globals::camera.farD = 1000.0;
	Globals::camera.FOV = 60.0;
	Globals::camera.windowW = double(width);
	Globals::camera.windowH = double(height);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::directionalLight.bind(0);
	//Globals::pointLight.bind(1);
	//Globals::spotLight.bind(2);
	frame++;
	int currFrameTime = glutGet(GLUT_ELAPSED_TIME);
	if (currFrameTime - prevFrameTime > 1000.0) {
		fps = frame * 1000.0 / (currFrameTime - prevFrameTime);
		prevFrameTime = currFrameTime;
		frame = 0;
		//std::cout << "FPS: " << fps << " frames per second." << std::endl;
	}
    
	player1.drawPlayer();
	
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-20, 0, -20);
	glVertex3f(-20, 0, 20);
	glVertex3f(20, 0, 20);
	glVertex3f(20, 0, -20);
	glEnd();

	//currDrawable->draw(Globals::drawData);
	//Globals::pointLight.sphere.draw(Globals::drawData);
	//Globals::spotLight.sphere.draw(Globals::drawData);
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//TODO: Keyboard callbacks!
void Window::keyPress(unsigned char key, int x, int y) {
	Matrix4 trans;
	Matrix4 scale;
	Vector3 rotAxis(0,0,1);
	Vector4 d;
	Vector3 d3;
	Vector4 forward;
	Vector4 position(0,0,0);

	switch (key) {
		case 'b':
			if (player1.boundsOn) {
				player1.boundsOn = false;
			}
			else {
				player1.boundsOn = true;
			}
			//std::cout << boundsOn << std::endl;
			break;
		case 'j':
			d3 = Globals::camera.e;
			d3 = d3.scale(-1);
			trans.makeTranslate(d3[0], d3[1], d3[2]);

			d = Globals::camera.d.toVector4(1);
			d = trans * d;
			trans.makeRotateY(0.1);
			d = trans * d;
			d3 = d3.scale(-1);
			trans.makeTranslate(d3[0], d3[1], d3[2]);
			d = trans * d;
			Globals::camera.d = d.toVector3();

			Globals::camera.update();
			break;
		case 'l':
			d3 = Globals::camera.e;
			d3 = d3.scale(-1);
			trans.makeTranslate(d3[0], d3[1], d3[2]);

			d = Globals::camera.d.toVector4(1);
			d = trans * d;
			trans.makeRotateY(-0.1);
			d = trans * d;
			d3 = d3.scale(-1);
			trans.makeTranslate(d3[0], d3[1], d3[2]);
			d = trans * d;
			Globals::camera.d = d.toVector3();

			Globals::camera.update();
			break;
		case 'k':
			if (frustumFOVFactor <= 2.0) {
				frustumFOVFactor = frustumFOVFactor + 0.02;
			}
			else {
				frustumFOVFactor = 2.0;
			}
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(frustumFOVFactor * 60.0, double(width) / (double)height, 1.0, 1000.0);

			Globals::camera.FOV = frustumFOVFactor * 60.0;
			Globals::camera.update();
			break;
		case 'i':
			if (frustumFOVFactor >= 0.5) {
				frustumFOVFactor = frustumFOVFactor - 0.02;
			}
			else {
				frustumFOVFactor = 0.5;
			}
			glMatrixMode(GL_PROJECTION);                                
			glLoadIdentity();                                                
			gluPerspective(frustumFOVFactor * 60.0, double(width) / (double)height, 1.0, 1000.0); 

			Globals::camera.FOV = frustumFOVFactor * 60.0;
			Globals::camera.update();
			break;
		case 'c':
			if (player1.cullOn) {
				player1.cullOn = false;
			}
			else {
				player1.cullOn = true;
			}
			break;
		case ' ':
			if (!player1.jumping)
				player1.initiateJump();
			else
				player1.initiateKick();
			
			break;
		case 'w':
			forward = player1.faceDirection;
			trans.makeTranslate(0.5 * forward[0], 0.5 * forward[1], 0.5 * forward[2]);
			player1.M = trans * player1.M;
			break;
		case 's':
			forward = player1.faceDirection;
			trans.makeTranslate(-0.5 * forward[0], -0.5 * forward[1], -0.5 * forward[2]);
			player1.M = trans * player1.M;
			break;
		case 'a':
			position.set(0, 0, 0, 0);
			position = player1.M * position;
			trans.makeRotateY(0.2);
			player1.robot.M = trans * player1.robot.M;
			player1.faceDirection = trans * player1.faceDirection;
			break;
		case 'd':
			position.set(0, 0, 0, 0);
			position = player1.M * position;
			trans.makeRotateY(-0.2);
			player1.robot.M = trans * player1.robot.M;
			player1.faceDirection = trans * player1.faceDirection;
			break;
	}
}
