#include "Camera.h"


Camera::Camera(void)
{
}
/*-----------------------------------------------*/
Camera::Camera(int x, int y, int minX, int maxX, int minY, int maxY)
{
	initialize(x, y, minX, maxX, minY, maxY);
}
/*-----------------------------------------------*/
Camera::Camera(int x, int y)
{
	initialize(x, y, 0, sizeof(int), 0, sizeof(int));
}
/*-----------------------------------------------*/
Camera::~Camera(void)
{
}
/*-----------------------------------------------*/
void Camera::initialize(int x, int y, int minX, int maxX, int minY, int maxY)
{
	this->x = x;
	this->y = y;
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
	collider.x = x - overrage;
	collider.y = y - overrage;
	overrage = 64;
	isFollowing = false;
}
/*-----------------------------------------------*/
void Camera::updateResolution(int width, int height)
{
	this->width = width;
	this->height = height;

	collider.w = width + overrage;
	collider.h = height + overrage;
}
/*-----------------------------------------------*/
void Camera::updateX(int value)
{
	x = x + value;

	lockCameraToBoundary();

	updateCollider(this->x, this->y);
}
/*-----------------------------------------------*/
void Camera::updateY(int value)
{
	y = y + value;

	lockCameraToBoundary();

	updateCollider(this->x, this->y);
}
/*-----------------------------------------------*/
void Camera::follow(int x, int y, int width, int height)
{
	if (isFollowing)
	{
		// Put in center of screen
		this->x = (x + (width/2)) - (this->width / 2); 
		this->y = (y + (height/2)) - (this->height / 2);

		lockCameraToBoundary();

		updateCollider(this->x, this->y);
	}
}
/*-----------------------------------------------*/
void Camera::lockCameraToBoundary()
{
	if (x < minX)
		x = minX;
	else if (x > maxX)
		x = maxX;

	if (y < minY)
		y = minY;
	else if (y > maxY)
		y = maxY;
}
/*-----------------------------------------------*/
void Camera::updateCollider(int x, int y)
{
	collider.x = x - overrage;
	collider.y = y - overrage;
}
/*-----------------------------------------------*/