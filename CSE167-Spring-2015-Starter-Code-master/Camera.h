#ifndef CSE167_Camera_h
#define CSE167_Camera_h

#include "Matrix4.h"
#include "Vector3.h"
#include <stdlib.h>
#include <vector>

class Camera
{
private:
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix
    
public:
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
	std::vector<Vector3> nearPlane;
	std::vector<Vector3> farPlane;

	float nearD;
	float farD;
	float FOV;
	float windowW, windowH;
	Vector3 normFront, normBack, normLeft, normRight, normTop, normBot;
    
    Camera(void);
    ~Camera(void);
    
	void init();
    void update(void);
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    void set(Vector3&, Vector3&, Vector3&);
    
};

#endif
