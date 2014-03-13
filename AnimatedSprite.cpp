#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void) : Sprite()
{
}
/*-----------------------------------------------*/
AnimatedSprite::AnimatedSprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
	: Sprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
	//walkingAnimation = AnimationData();
	//idleAnimation = AnimationData();
	this->curAnimation = AnimationData();
	this->isAnimated = true;
	maxSpeedX = 0;
	maxSpeedY = 0;
}
/*-----------------------------------------------*/
AnimatedSprite::~AnimatedSprite(void)
{
}
/*-----------------------------------------------*/
void AnimatedSprite::update(int ms)
{
	// Store previous position information
	prevPosX = posX;
	prevPosY = posY;

	// Update Position
   float time = (float)ms / 1000;
	float deltaX = time * speedX;
	float deltaY = time * speedY;
	posX += deltaX;
	posY += deltaY;
	x = (int) floor(posX);
	y = (int) floor(posY); // Bottom left coord adjustment
	
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

	// Update Colliders
	prevCollider.x = collider.x;
	prevCollider.y = collider.y;
	collider.x = this->x + colliderXOffset;
	collider.y = this->y + colliderYOffset;
}
/*-----------------------------------------------*/
void AnimatedSprite::setAnimation(std::string animation)
{
	curAnimation = animations[animation];
	tu = curAnimation.def.frames[0].tu;
	tv = curAnimation.def.frames[0].tv;
	tSizeX = curAnimation.def.frames[0].tWidth;
	tSizeY = curAnimation.def.frames[0].tHeight;
}
/*-----------------------------------------------*/
void AnimatedSprite::updatePosition(float x , float y)
{
	// Given in absolute position

	prevPosX = posX;
	prevPosY = posY;
	//float deltaX = x - this->x;
	//float deltaY = y - this->y;
	this->posX = x;
	this->posY = y;
	this->x = (int) floor(posX);
	this->y = (int) floor(posY);
	
	// Update Colliders
	prevCollider.x = collider.x;
	prevCollider.y = collider.y;
	collider.x = this->x + colliderXOffset;
	collider.y = this->y + colliderYOffset;
}