#include "AABB.h"


AABB::AABB(void)
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

AABB::AABB(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}


AABB::~AABB(void)
{
}

bool AABB::AABBIntersect(AABB* box)
{
	// This box to the right
	if( this->x > box->x + box->w ) 
		return false;
	// This box to the left
	if( this->x + this->w < box->x )
		return false;
	// This box below
	if( this->y > box->y + box->h )
		return false;
	// This box above
	if( this->y + this->h < box->y )
		return false;
	
	return true;
}

bool* AABB::AABBwhichSideIntersected(AABB* prevBox1, AABB* currBox1, AABB* prevBox2, AABB* currBox2)
{
	bool* yo;
	return yo;
}
