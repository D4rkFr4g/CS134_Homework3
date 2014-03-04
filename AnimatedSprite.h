#pragma once
#include "sprite.h"
#include "AnimationData.h"

class AnimatedSprite :
	public Sprite
{
public:
	// Constructors
	AnimatedSprite(void);
	AnimatedSprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
	~AnimatedSprite(void);
	
	// Functions
	void update(int ms);
	void walking();
	void idle();

	// Variables
	bool isAnimated;
	AnimationData curAnimation;
	AnimationData walkingAnimation;
	AnimationData idleAnimation;
};

