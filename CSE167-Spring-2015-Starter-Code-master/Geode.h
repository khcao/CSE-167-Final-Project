#ifndef CSE167_Geode_h
#define CSE167_Geode_h

#include "Node.h"
#include "Color.h"
class Geode : public Node
{
public:
	Color color;

	Geode();
	~Geode();

	void draw(Matrix4);
	void update(void);
	virtual void render() = 0;
	void simDraw(Matrix4);
};

#endif