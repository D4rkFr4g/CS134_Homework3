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

bool* AABB::AABBwhichSideIntersected(AABB* prevBox1, AABB* currBox1, AABB* box2)
{
	bool* sides = new bool[4];

	bool wasAbove = (prevBox1->y + prevBox1->h) < box2->y;
	bool nowAbove = (currBox1->y + currBox1->h) < box2->y;
	bool wasRight = prevBox1->x > (box2->x + box2->w);
	bool nowRight = currBox1->x > (box2->x + box2->w);
	bool wasBelow = prevBox1->y > (box2->y + box2->h);
	bool nowBelow = currBox1->y > (box2->y + box2->h);
	bool wasLeft = (prevBox1->x + prevBox1->w) < box2->x;
	bool nowLeft = (currBox1->x + currBox1->w) < box2->x;

	sides[0] = wasLeft && !nowLeft && !wasAbove && !wasBelow; // Box2 Hit from Left
	sides[1] = wasRight && !nowRight && !wasAbove && !wasBelow; // Box2 Hit from Right
	sides[2] = wasAbove && !nowAbove && !wasRight && !wasLeft; // Box2 Hit from Top
	sides[3] = wasBelow && !nowBelow && !wasRight && !wasLeft; // Box2 Hit from Below

	return sides;
}
