#include "PlayerSprite.h"


PlayerSprite::PlayerSprite(void) : AnimatedSprite()
{
}

PlayerSprite::PlayerSprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY, int health)
	: AnimatedSprite(texture, x, y, width, height, tu, tv, tSizeX, tSizeY)
{
	isAlive = true;
	this->health = health;
	score = 0;
}

PlayerSprite::~PlayerSprite(void)
{
}
