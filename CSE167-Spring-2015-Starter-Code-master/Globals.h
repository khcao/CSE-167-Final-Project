#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "House.h"
#include "OBJObject.h"
#include "Sphere.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
	static Sphere sphere;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
	static House house;
	static OBJObject bunny;
	static OBJObject dragon;
	static OBJObject bear;
	static Light directionalLight;
	static Light pointLight;
	static Light spotLight;
	static Vector4 pl[6];
	static Matrix4 perspectiveMatrix;
};

#endif
