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

	//this->tileArray = new Sprite[width * height];
	this->tileArray.reserve(width * height);
}


TileLevel::~TileLevel(void)
{
	//delete[] tileArray;
}


void TileLevel::drawLevel(int camX, int camY)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			tileArray[(i * width) + j].drawUV(camX, camY);
	}
}