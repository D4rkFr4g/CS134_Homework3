#pragma once
#include "AnimationFrame.h"

class Animation
{
public:
	Animation(void);
	Animation(char* name, AnimationFrame* frames, int numFrames);
	~Animation(void);

	// Variables
	const char* name;
	AnimationFrame* frames;
	int numFrames;
};

