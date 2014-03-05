#include "TileLevel.h"


TileLevel::TileLevel(void)
{
}

TileLevel::TileLevel(int width, int height, int tilesWidth, int tilesHeight)
{
	this->width = width; // Columns
	this->height = height; // Rows
	this->tilesWidth = tilesWidth;
	this->tilesHeight = tilesHeight;
	this->tileArray.reserve(width * height);
}


TileLevel::~TileLevel(void)
{
}


void TileLevel::drawLevel(int camX, int camY, int screenWidth, int screenHeight)
{
	// Calculate which tiles to draw
	int tile_x = (int) floor((float) camX / tilesWidth);
	int tile_y = (int) floor((float) camY / tilesHeight);
	int tile_xStop = tile_x + (int) ceil((float) screenWidth / tilesWidth);
	int tile_yStop = tile_y + (int) ceil((float) screenHeight / tilesHeight);

	for (int i = tile_y; i < tile_yStop; i++)
	{
		for (int j = tile_x; j < tile_xStop; j++)
			tileArray[(i * width) + j].drawUV(camX, camY);
	}
}