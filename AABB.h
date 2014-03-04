#pragma once
class AABB
{
public:
	// Constructors
	AABB(void);
	AABB::AABB(int x, int y, int w, int h);
	~AABB(void);

	// Functions
	bool AABBIntersect(const AABB* box1, const AABB* box2);

	// Variables
	int x, y, w, h;
};

