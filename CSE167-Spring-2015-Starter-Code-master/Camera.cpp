#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 20.0, 30.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
	ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);

	FOV = 60.0;
	nearD = 1.0;
	farD = 1000.0;
	windowW = 512;
	windowH = 512;

	this->update();
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

void Camera::init() {
	c.identity();
	e.set(40.0, 20.0, 30.0);
	d.set(20.0, 0.0, 0.0);
	up.set(0.0, 1.0, 0.0);

	//Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
	//This is used as a default camera position for Project 1
	c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
	ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1); 
	this->update();
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
	Vector3 zAxis = (e - d);
	zAxis = zAxis.scale(1 / (zAxis.magnitude()));

	Vector3 xAxis = up.cross(zAxis);
	xAxis = xAxis.scale(1 / xAxis.magnitude());

	Vector3 yAxis = zAxis.cross(xAxis);

    //Use these axes and the e vector to create a camera matrix c
	c.set(xAxis[0], xAxis[1], xAxis[2], 0, yAxis[0], yAxis[1], yAxis[2], 0, zAxis[0], zAxis[1], zAxis[2], 0, e[0], e[1], e[2], 1);
    //Use c to solve for an inverse camera matrix ci
	ci = c.rigidInverse();

	float nearY = nearD * tan(FOV * 3.14159265358979323846 / 360);
	float nearX = nearY * (double(windowW) / double(windowH));

	float farY = farD * tan(FOV * 3.14159265358979323846 / 360);
	float farX = farY * (double(windowW) / double(windowH));
	
	Vector3 dUnit = zAxis.scale(-1);
	Vector3 farCenter = e + (dUnit * farD);
	Vector3 nearCenter = e + (dUnit * nearD);

	farPlane.clear();
	nearPlane.clear();

	farPlane.push_back( farCenter + (yAxis.scale(farY)) - (xAxis.scale(farX)) ); // far top left
	farPlane.push_back( farCenter + (yAxis.scale(farY)) + (xAxis.scale(farX)) ); // far top right
	farPlane.push_back( farCenter - (yAxis.scale(farY)) - (xAxis.scale(farX)) ); // far bot left
	farPlane.push_back( farCenter - (yAxis.scale(farY)) + (xAxis.scale(farX)) ); // far bot right

	nearPlane.push_back( nearCenter + (yAxis.scale(nearY)) - (xAxis.scale(nearX)) ); // near top left
	nearPlane.push_back( nearCenter + (yAxis.scale(nearY)) + (xAxis.scale(nearX)) ); // near top right
	nearPlane.push_back( nearCenter - (yAxis.scale(nearY)) - (xAxis.scale(nearX)) ); // near bot left
	nearPlane.push_back( nearCenter - (yAxis.scale(nearY)) + (xAxis.scale(nearX)) ); // near bot right
	

	normFront = (nearPlane[0] - nearPlane[1]).cross(nearPlane[3] - nearPlane[1]);
	normFront = normFront.normalize();


	normBack = (farPlane[3] - farPlane[1]).cross(farPlane[0] - farPlane[1]);
	normBack = normBack.normalize();

	normLeft = (nearPlane[0] - nearPlane[2]).cross(farPlane[2] - nearPlane[2]);
	normLeft = normLeft.normalize();

	normRight = (farPlane[1] - farPlane[3]).cross(nearPlane[3] - farPlane[3]);
	normRight = normRight.normalize();

	normTop = (farPlane[1] - nearPlane[1]).cross(nearPlane[0] - nearPlane[1]);
	normTop = normTop.normalize();

	normBot = (farPlane[3] - farPlane[2]).cross(nearPlane[2] - farPlane[2]);
	normBot = normBot.normalize();

}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
