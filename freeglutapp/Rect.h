#ifndef RECT_H
#define RECT_H
#include "Vec.h"
#include <vector>

class Rect
{
public:
	float x, y, width, height, r, g, b,directionx,directiony;
	bool selected, focus;
	std::vector<Vec*> points;
	Rect()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		r = 0;
		g = 0;
		b = 0;
		selected = false;
		focus = false;
		directionx = 0;
		directiony = 0;
	}
	Rect(float x, float y, float w, float h, float r, float g, float b)
	{
		this->x = x;
		this->y = y;
		width = w;
		height = h;
		this->r = r;
		this->g = g;
		this->b = b;
		selected = false;
		focus = false;
		directionx = 0;
		directiony = 0;
	}
	bool contains(const Vec &vector)
	{
		float left, right, top, bottom;
		if(vector.x == 0 && vector.y == 0)
		{
			return false;
		}
		left = x;
		right = x + width;
		top = y;
		bottom = y - height;
		return (vector.x >= left && vector.x <= right && vector.y <= top && vector.y >=bottom);
	}
	
};
#endif