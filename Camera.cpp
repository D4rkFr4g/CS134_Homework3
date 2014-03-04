#include "Camera.h"


Camera::Camera(void)
{
}

Camera::Camera(int x, int y, int minX, int maxX, int minY, int maxY)
{
	this->x = x;
	this->y = y;
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

Camera::Camera(int x, int y)
{
	this->x = x;
	this->y = y;
	this->minX = 0;
	this->maxX = sizeof(int);
	this->minY = 0;
	this->maxY = sizeof(int);
}

Camera::~Camera(void)
{
}

void Camera::updateX(int value)
{
	x = x + value;

	if (x < minX)
		x = minX;
	else if (x > maxX)
		x = maxX;
}

void Camera::updateY(int value)
{
	y = y + value;

	if (y < minY)
		y = minY;
	else if (y > maxY)
		y = maxY;
}
