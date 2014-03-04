#pragma once
class Camera
{
public:
	Camera(void);
	Camera(int x, int y, int minX, int maxX, int minY, int maxY);
	Camera(int x, int y);
	~Camera(void);
	void updateX(int value);
	void updateY(int value);

	int x, y;
	int minX, maxX;
	int minY, maxY;
};

