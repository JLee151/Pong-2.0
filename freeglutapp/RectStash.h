#ifndef RECTSTASH_H
#define RECTSTASH_H
#include <vector>
#include "Rect.h"
#include <iostream>
using namespace std;
class RectStash {
public:
	vector<Rect*> rect;
	RectStash() 
	{

	}
	Rect * first() 
	{
		return rect[0];
	}
	void add(Rect* rekt) 
	{
		rect.push_back(rekt);
	}
	void del()
	{
			rect.clear();
	}
	~RectStash() 
	{
		for(std::vector<Rect*>::iterator i = rect.begin(); i != rect.end(); ++i) 
		{
			delete *i;
		}
	}
};

#endif