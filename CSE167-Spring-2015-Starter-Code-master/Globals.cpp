#include "Globals.h"

Camera Globals::camera;

Light Globals::light;
Light Globals::directionalLight;
Light Globals::pointLight;
Light Globals::spotLight;

DrawData Globals::drawData;
UpdateData Globals::updateData;

//OBJObject Globals::bunny("bunny.obj");
//OBJObject Globals::dragon("dragon.obj");
//OBJObject Globals::bear("bear.obj");


Vector4 Globals::pl[6];
Matrix4 Globals::perspectiveMatrix;
bool Globals::player1Kicking = false;
bool Globals::player2Kicking = false;

bool Globals::exploreMode = true;
int Globals::player1Score = 0;
int Globals::player2Score = 0;
 Shader Globals::shader("./glowVertex.glsl","./glowPixel.glsl",true);
 bool Globals::blurShaderToggle = true;
 bool Globals::previouslyKicking = false;
 bool Globals::previouslyCollided = false;
 bool Globals::announcing = false;