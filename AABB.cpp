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

bool AABBIntersect(const AABB* box1, const AABB* box2)
{
	// box1 to the right
	if( box1->x > box2->x + box2->w ) 
		return false;
	// box1 to the left
	if( box1->x + box1->w < box2->x )
		return false;
	// box1 below
	if( box1->y > box2->y + box2->h )
		return false;
	// box1 above
	if( box1->y + box1->h < box2->y )
		return false;
	
	return true;
}
