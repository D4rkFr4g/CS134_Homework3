#pragma once
class AABB
{
public:
	// Constructors
	AABB(void);
	AABB(int x, int y, int w, int h);
	~AABB(void);

	// Functions
	bool AABBIntersect(AABB* box);
	static bool* AABBwhichSideIntersected(AABB* prevBox, AABB* currBox, AABB* prevBox2, AABB* currBox2);

	// Variables
	int x, y, w, h;
};

