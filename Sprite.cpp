#include "Sprite.h"


Sprite::Sprite(void)
{
	initialize(0, 0, 0, 0, 0, 0, 0, 1, 1);
}
/*-----------------------------------------------*/
Sprite::Sprite(GLuint texture, int width, int height)
{
	initialize(texture, 0, 0, width, height, 0, 0, 1, 1);
}
/*-----------------------------------------------*/
Sprite::Sprite(GLuint texture, int x, int y, int width, int height)
{
	initialize(texture, x, y, width, height, 0, 0, 1, 1);
}
/*-----------------------------------------------*/
Sprite::Sprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
{
	initialize(texture, x, y, width, height, tu, tv, tSizeX, tSizeY);
}
/*-----------------------------------------------*/
Sprite::~Sprite(void)
{
}
/*-----------------------------------------------*/
void Sprite::initialize(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->tu = tu;
	this->tv = tv;
	this->tSizeX = tSizeX;
	this->tSizeY = tSizeY;
	posX = (float)x;
	posY = (float)y;
	this->isFlippedX = false;
	this->isFlippedY = false;
	collider = AABB(x, y, width, height);
	prevCollider = AABB(x, y, width, height);
	speedX = 0;
	speedY = 0;
	type = 0;
	prevPosX = 0;
	prevPosY = 0;
}
/*-----------------------------------------------*/
void Sprite::draw(void)
{
	glDrawSprite(texture, x, y, width, height);
}
/*-----------------------------------------------*/
void Sprite::draw(int camX, int camY)
{
	glDrawSprite(texture, x - camX, y - camY, width, height);
}
/*-----------------------------------------------*/
void Sprite::drawUV(int camX, int camY)
{
	GLfloat u = tu;
	GLfloat v = tv;
	GLfloat uSize = tSizeX;
	GLfloat vSize = tSizeY;

	if (isFlippedX)
	{
		u += uSize;
		uSize *= -1;
	}
	if (isFlippedY)
	{
		v += vSize;
		vSize *= -1;
	}

	glDrawSprite(texture, x - camX, y - camY, width, height, u, v, uSize, vSize);
}
/*-----------------------------------------------*/
void Sprite::update(int ms)
{
}
/*-----------------------------------------------*/
void Sprite::setSpeed(float speedX, float speedY)
{
	this->speedX = speedX;
	this->speedY = speedY;
}
/*-----------------------------------------------*/
void Sprite::flipX()
{	
	isFlippedX = !isFlippedX;
}
/*-----------------------------------------------*/
void Sprite::flipY()
{	
	isFlippedY = !isFlippedY;
}
/*-----------------------------------------------*/		
void Sprite::print()
{
	using namespace std;
	cout << "x = " << x << "\t y = " << y << endl;
}
