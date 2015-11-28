#ifndef CSE167_Group_h
#define CSE167_Group_h

#include <stdlib.h>
#include <vector>
#include "Node.h"

class Group : public Node
{
public:
	std::vector<Node*> children;

	Group();
	~Group();

	void addChild(Node*);
	void removeChild(Node*);
	void draw(Matrix4);
	void update(void);

	void simDraw(Matrix4);
};

#endif