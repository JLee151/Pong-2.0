#ifndef VEC_H
#define	VEC_H
#include <iostream>
using namespace std;
class Vec
{
	public:
	float x,y;
	Vec()
	{
		x = 0;
		y = 0;
	}
	Vec(float a, float b)
	{
		x = a;
		y = b;
		
	}
	void add(Vec u)
	{
		x += u.x;
		y += u.y;
	}
	void print()
	{
		cout << "(" << x << ", " << y << ")"<< endl;
	}
};
#endif