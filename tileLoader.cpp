#include "tileLoader.h"

void tileLoader::loadTiles(const char* filename, TileLevel *level)
{
	using namespace std;
	string line = "";
	int x, y, width, height, tileWidth, tileHeight;
	string tileFile = "";
	int *tilesRead = NULL;
	int tileIndex = 0;
	GLfloat tu, tv;

	// Opens a Flare map file .txt
	ifstream infile;
	infile.open(filename);

	getline(infile, line);
	if (!line.compare("[header]\n"))
	{
		cout << "Header information not found" << endl;
		return;
	}
	
	// Read Width
	getline(infile, line);
	line = line.substr(6);
	width = atoi(line.c_str());

	// Read Height
	getline(infile, line);
	line = line.substr(7);
	height = atoi(line.c_str());

	// Read Tile Width
	getline(infile, line);
	line = line.substr(10);
	tileWidth = atoi(line.c_str());

	// Read Tile Height
	getline(infile, line);
	line = line.substr(11);
	tileHeight = atoi(line.c_str());

	getline(infile, line); // Blank line

	// Read tileset filename Format: "./optionalFolder/filename.tga"
	getline(infile, line); // [tilesets]
	getline(infile, line);
	int start = line.find('.');
	int offset = start + 1;
	// Look for .. instead of .
	string nextChar = line.substr(offset, 1);
	if (nextChar.compare("."))
	{
	  offset++;
	  start++;
	}
	int end = line.find('.', offset+1);
	int extension = end - offset;
	line = line.substr(offset,extension);
	tileFile = line + ".tga";

	getline(infile, line); // Blank line
	getline(infile, line); // [layer]
	getline(infile, line); // type=Tile Layer 1
	getline(infile, line); // data = 

	// Debug Checks
	if (0)
	{
		cout << "width = " << width << endl;
		cout << "heigth = " << height << endl;
		cout << "tileWidth = " << tileWidth << endl;
		cout << "tileHeight = " << tileHeight << endl;
		cout << "tileSet = " << tileFile << endl;
	}

	// Create array for tile data
	tilesRead = new int [width * height];

	// Read Data
	while(!infile.eof())
	{
		getline(infile, line, ',');
		if (line.compare("\n"))
		{
			tilesRead[tileIndex] = atoi(line.c_str());
			tileIndex++;

			// Debug Check
			if (0)
				cout << line << endl;
		}
	}
	
	// Debug Check all tiles read
	if (0)
	{
		for (int i = 0; i < width * height; i++)
			cout << "tile[" << i << "] = " << tilesRead[i] << endl;
		cout << "Tiles Read = " << tileIndex << endl;
	}

	// Load Tileset Texture
	int *tileMapWidth = new int;
	int *tileMapHeight = new int;
	GLuint tileSet = glTexImageTGAFile(tileFile.c_str(), tileMapWidth, tileMapHeight);

	// Load tiles to level
	tileIndex = 0;
	int tileMapRows = *tileMapHeight / tileHeight;
	int tileMapCols = *tileMapWidth / tileWidth;
	GLfloat tSizeX = (GLfloat) 1.0 / tileMapCols;
	GLfloat tSizeY = (GLfloat) 1.0 / tileMapRows;

	*level = TileLevel(width, height, tileWidth, tileHeight);

	for (int i = 0; i < height; i++) // Row
		for (int j = 0; j < width; j++) // Column
		{
			// Find Row / Column texture coords
			int tilePos = tilesRead[tileIndex];
			int row = (tileMapRows-1) - ((tilePos-1) / tileMapCols); // Flip Y for UV coords
			int column = (tilePos-1) % tileMapCols;
			tu = column * tSizeX;
			tv = row * tSizeY;

			// Convert to x,y coords
			x = j * tileWidth;
			y = i * tileHeight;

			//level->tileArray[i * width + j] = Sprite(tileSet, x, y, tileWidth, tileHeight, tu, tv, tSizeX, tSizeY);
			level->tileArray.push_back(Sprite(tileSet, x, y, tileWidth, tileHeight, tu, tv, tSizeX, tSizeY));
			tileIndex++;
		}

	// Cleanup
	infile.close();
	delete[] tilesRead;
}