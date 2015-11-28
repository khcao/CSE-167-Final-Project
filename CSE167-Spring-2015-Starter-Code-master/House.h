#pragma once


#include "Drawable.h"
class House : public Drawable
{
public:
	House();
	~House();

	virtual void draw(DrawData&);
};

