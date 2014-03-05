#include "Sprite.h"
#include <vector>

#pragma once
class TileLevel
{
public:
	TileLevel(void);
	TileLevel(int width, int height, int tileWidth, int tileHeight);
	~TileLevel(void);

	void drawLevel(int camX, int camY, int screenWidth, int screenHeight);

	// Global Variables
	int tilesWidth, tilesHeight;
	int width, height;
	std::vector<Sprite> tileArray;
};

