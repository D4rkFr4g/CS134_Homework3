#pragma once
#include <map>
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
	void setAnimation(std::string animation);

	// Variables
	bool isAnimated;
	AnimationData curAnimation;
	std::map<std::string, AnimationData> animations;
};

