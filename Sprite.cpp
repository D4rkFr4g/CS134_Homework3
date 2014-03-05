#include "Sprite.h"

Sprite::Sprite(void)
{
	initialize(0, 0, 0, 0, 0, 0, 0, 1, 1);
}

Sprite::Sprite(GLuint texture, int width, int height)
{
	initialize(texture, 0, 0, width, height, 0, 0, 1, 1);
}

Sprite::Sprite(GLuint texture, int x, int y, int width, int height)
{
	initialize(texture, x, y, width, height, 0, 0, 1, 1);
}

Sprite::Sprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY)
{
	initialize(texture, x, y, width, height, tu, tv, tSizeX, tSizeY);
}

Sprite::~Sprite(void)
{
}

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
}

void Sprite::draw(void)
{
	glDrawSprite(texture, x, y, width, height);
}

void Sprite::draw(int camX, int camY)
{
	glDrawSprite(texture, x - camX, y - camY, width, height);
}

void Sprite::drawUV(int camX, int camY)
{
	if (isFlippedX && tSizeX > 0 || !isFlippedX && tSizeX < 0)
		tSizeX *= -1;
	if (isFlippedY && tSizeY > 0 || !isFlippedY && tSizeY < 0)
		tSizeY *= -1;

	glDrawSprite(texture, x - camX, y - camY, width, height, tu, tv, tSizeX, tSizeY);
}

void Sprite::update(int ms)
{
}
	
void Sprite::setSpeed(int speedX, int speedY)
{
	this->speedX = speedX;
	this->speedY = speedY;
}

void Sprite::flipX()
{	
	isFlippedX = !isFlippedX;
}

void Sprite::flipY()
{	
	isFlippedY = !isFlippedY;
}
		
void Sprite::print()
{
	using namespace std;
	cout << "x = " << x << "\t y = " << y << endl;
}
