#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif



Light::Light()
{
    bindID = -1;
    
    ambientColor = Color::ambientDefault();
    diffuseColor = Color::diffuseDefault();
    specularColor = Color::specularDefault();
    
    constantAttenuation = 1.0;
    linearAttenuation = 0.0;
    quadraticAttenuation = 0.05;
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id)
{
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor.ptr());
    
    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
	if (bindID == 0) {
		glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, constantAttenuation);
	}
    //Add support for Linear Attenuation
	//glLightf(GL_LIGHT0 + bindID, GL_LINEAR_ATTENUATION, linearAttenuation);
	else {
		glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
	}
    
    //Position the light
	glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());


	if (bindID == 2) {
		//Setup spotlight direction, angle, and exponent here
		Vector4 spotDir = position;
		spotDir[0] = spotDir[0] * -1;
		spotDir[1] = spotDir[1] * -1;
		spotDir[2] = spotDir[2] * -1;
		glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, spotDir.ptr());
		GLfloat spotAngle = 15.0f;
		glLightf(GL_LIGHT0 + bindID, GL_SPOT_CUTOFF, 30.0f);
		GLfloat spotExp = 100.0f;
		glLightf(GL_LIGHT0 + bindID, GL_SPOT_EXPONENT, 100.0f);
	}

	// Position the sphere
	/*sphere.toWorld.identity();
	Matrix4 trans;
	trans.makeTranslate(position[0], position[1], position[2]);
	sphere.toWorld = trans * sphere.toWorld; */
}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}
