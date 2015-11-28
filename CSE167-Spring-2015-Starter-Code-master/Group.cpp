#include "Group.h"


Group::Group()
{
}


Group::~Group()
{
}

void Group::addChild(Node* input) {
	this->children.push_back(input);
	input->center = this->newCenter;
}

void Group::removeChild(Node* input) {
	for (int i = 0; i < children.size(); i++) {
		if (children.at(i) == input)
			children.erase(children.begin() + i);
	}
}

void Group::draw(Matrix4 C) {
	for (int i = 0; i < children.size(); i++) {
		children.at(i)->draw(C);
	}
}

void Group::simDraw(Matrix4 C) {

	for (int i = 0; i < children.size(); i++) {
		children.at(i)->simDraw(C);
	}
}

void Group::update() {

}