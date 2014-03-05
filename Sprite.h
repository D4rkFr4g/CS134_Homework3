#pragma once
#include <GL/glew.h>
#include <iostream>
#include "DrawUtils.h"

class Sprite
{
public:
	// Constructors
	Sprite(void);
	Sprite::Sprite(GLuint texture, int width, int height);
	Sprite::Sprite(GLuint texture, int x, int y, int width, int height);
	Sprite::Sprite(GLuint texture, int x, int y, int width, int height, GLfloat tu, GLfloat tv, GLfloat tSizeX, GLfloat tSizeY);
	~Sprite(void);

	//Functions
	void Sprite::draw(void);
	void Sprite::draw(int camX, int camY);
	void Sprite::drawUV(int camX, int camY);
	virtual void Sprite::update(int ms);
	virtual void Sprite::setSpeed(int speedX, int speedY);
	void Sprite::flipX();
	void Sprite::flipY();
	void Sprite::print();

	// Variables
	GLuint texture;
	int width, height;
	int x, y;
	GLfloat tu, tv;
	GLfloat tSizeX, tSizeY;
	int speedX, speedY;
	float posX, posY;
	bool isFlippedX;
	bool isFlippedY;

private:

};

