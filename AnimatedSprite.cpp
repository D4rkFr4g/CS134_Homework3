#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void) : Sprite()
{
}

AnimatedSprite::AnimatedSprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
	: Sprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
	//walkingAnimation = AnimationData();
	//idleAnimation = AnimationData();
	this->curAnimation = AnimationData();
	this->isAnimated = true;
}

AnimatedSprite::~AnimatedSprite(void)
{
}

void AnimatedSprite::update(int ms)
{
	// Update Position
   float time = (float)ms / 1000;
	float deltaX = time * speedX;
	float deltaY = time * speedY;
	posX += deltaX;
	posY += deltaY;
	x = (int) floor(posX);
	y = (int) floor(posY);
	
	// Update Animation
	curAnimation.updateTime(ms);
	int currentFrame = curAnimation.currentFrame;
	AnimationFrame frame = curAnimation.def.frames[currentFrame];
	if (isAnimated)
	{
		tu = frame.tu;
		tv = frame.tv;
		tSizeX = frame.tWidth;
		tSizeY = frame.tHeight;
	}

	// Update Collider
	collider.x = x;
	collider.y = y;
}

void AnimatedSprite::setAnimation(std::string animation)
{
	curAnimation = animations[animation];
}