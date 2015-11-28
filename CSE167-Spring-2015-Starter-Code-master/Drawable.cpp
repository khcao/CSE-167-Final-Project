#include "Drawable.h"
#include "Window.h"

Drawable::Drawable()
{
    this->toWorld.identity();
	//this->centerAndScale();
}

Drawable::~Drawable()
{
    //
}

void Drawable::draw(DrawData& data)
{
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data)
{
    std::cout << "Warning: update() is not implemented" << std::endl;
}

void Drawable::centerAndScale() {
	// Translate to the origin
	Matrix4 trans;
	trans.makeTranslate(
		 (minX + ((maxX - minX) / 2)) * -1, 
		 (minY + ((maxY - minY) / 2)) * -1, 
		 (minZ + ((maxZ - minZ) / 2)) * -1);
	this->toWorld = trans * this->toWorld;

	float pi = 3.14159265358979323846;
	float largeAxisScale = 12.91 * tan(pi / 6);
	// Scale it from there
	if ((maxX - minX) > (maxY - minY)) {
		// X is largest axis
		if ((maxX - minX) > (maxZ - minZ)) {
			
		}
		// Z is the largest axis
		else {

		}
	}
	else {
		// Y is the largest axis
		if ((maxY - minY) > (maxZ - minZ)) {

		}
		// Z is the largest axis
		else {

		}
	}

	trans.makeScale(largeAxisScale);
	this->toWorld = trans * this->toWorld;
}
