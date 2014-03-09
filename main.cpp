#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_timer.h>
#include <GL/glew.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <map>
#include "DrawUtils.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "PlayerSprite.h"
#include "Camera.h"
#include "TileLevel.h"
#include "tileLoader.h"
#include "player.h"

using namespace std;

// Forward Declarations
static void keyboard();
static void clearBackground();
static void makeChicken();
static int getSpeed();

// Constants
const int camSpeed = 10;
const int g_numOfLevels = 1;
const int spriteSize = 64;
const int spriteReserve = 50000;
const int initialChickens = 20;
const int chickenSpeed = 50;
const unsigned char* kbState = NULL;
const int g_numOfCheckBuckets = 9;

// Global Variables
SDL_Window* g_window;
float color[] = {0,0,0};
float currentDirection = 1;
int g_windowWidth = 640;
int g_windowHeight = 480;
int g_windowMaxWidth = 0;
int g_windowMaxHeight = 0;
Camera g_cam;
int g_currentLevel = 0;
TileLevel g_level[g_numOfLevels];
std::vector<std::vector<AnimatedSprite>> g_spriteBuckets;
int* g_checkBuckets;
GLuint spriteTexture;
GLuint playerTexture;
int diff_time;
unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};
bool shouldExit = false;
PlayerSprite g_player;
// End Variables

using namespace std;

/*-----------------------------------------------*/
static int initSDL()
{
	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) 
	{
		return 1;
	}
 
	// Create the window, OpenGL context
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	g_window = SDL_CreateWindow(
	"Invincible Chickens",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	g_windowHeight, g_windowHeight,
	SDL_WINDOW_OPENGL);// | SDL_WINDOW_FULLSCREEN );
	glCullFace( GL_BACK );

	if( !g_window ) 
	{
		SDL_Quit();
		return 1;
	}
	SDL_GL_CreateContext( g_window );

	// Make sure we have a recent version of OpenGL
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ) 
	{
		SDL_Quit();
		return 1;
	}
	if( !GLEW_VERSION_1_5 ) 
	{
		SDL_Quit();
		return 1;
	}
	
	return 0;
}
/*-----------------------------------------------*/
static void init2D()
{
	// OpenGL calls
	glViewport(0,0,(GLsizei) g_windowWidth, (GLsizei) g_windowHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, g_windowWidth, g_windowHeight, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);  //Ghost Chickens
}
/*-----------------------------------------------*/
static void initCamera()
{
	//g_cam = Camera(g_windowWidth, g_windowHeight, 0, g_windowMaxWidth, 0, g_windowMaxHeight);
	TileLevel currentLevel = g_level[g_currentLevel];

	g_windowMaxWidth = (currentLevel.width * currentLevel.tilesWidth);
	g_windowMaxHeight = (currentLevel.height * currentLevel.tilesHeight);

	g_cam = Camera(0, 0, 0, g_windowMaxWidth - g_windowWidth, 0, g_windowMaxHeight - g_windowHeight);
	g_cam.updateResolution(g_windowWidth, g_windowHeight);
}
/*-----------------------------------------------*/
static int whichBucket(int x, int y)
{
	int column = (int) floor((float) x / g_windowWidth);
	int row = (int) floor((float) y / g_windowHeight);
	int bucketWidth = (int) floor((float) g_windowMaxWidth / g_windowWidth);

	if (column < 0 || column >= bucketWidth)
		return -1;

	return (row * bucketWidth) + column;
}
/*-----------------------------------------------*/
static void updateCheckBuckets()
{
	g_checkBuckets[0] = whichBucket(g_cam.x - g_windowWidth, g_cam.y + g_windowHeight);
	g_checkBuckets[1] = whichBucket(g_cam.x, g_cam.y + g_windowHeight);
	g_checkBuckets[2] = whichBucket(g_cam.x + g_windowWidth, g_cam.y + g_windowHeight);
	g_checkBuckets[3] = whichBucket(g_cam.x - g_windowWidth, g_cam.y);
	g_checkBuckets[4] = whichBucket(g_cam.x, g_cam.y);
	g_checkBuckets[5] = whichBucket(g_cam.x + g_windowWidth, g_cam.y);
	g_checkBuckets[6] = whichBucket(g_cam.x - g_windowWidth, g_cam.y - g_windowHeight);
	g_checkBuckets[7] = whichBucket(g_cam.x, g_cam.y - g_windowHeight);
	g_checkBuckets[8] = whichBucket(g_cam.x + g_windowWidth, g_cam.y - g_windowHeight);
}
/*-----------------------------------------------*/
static void initBuckets()
{
	g_checkBuckets = new int [g_numOfCheckBuckets];

	// Initialize spriteBuckets
	int bucketWidth = (int) floor((float) g_windowMaxWidth / g_windowWidth);
	int bucketHeight = (int) floor((float) g_windowMaxHeight / g_windowHeight);
	int numOfBuckets = bucketWidth * bucketHeight;
	g_spriteBuckets.reserve(numOfBuckets);
	
	for (int i = 0; i < numOfBuckets; i++)
	{
		vector<AnimatedSprite> temp;
		g_spriteBuckets.push_back(temp);
	}
}
/*-----------------------------------------------*/
static void loadSprites()
{
	spriteTexture = glTexImageTGAFile("./Sprites/spriteSheet_chicken.tga", NULL, NULL);
	int* width = new int;
	int* height = new int;
	playerTexture = glTexImageTGAFile("./Sprites/contra_sheet.tga", width, height);

	// Load the Initial chickens
	for (int i = 0; i < initialChickens; i++)
		makeChicken();

	g_player = player::makePlayer(playerTexture, *width, *height);
}
/*-----------------------------------------------*/
static void makeChicken()
{
	int x = rand() % (g_windowMaxWidth - spriteSize);
	int y = rand() % (g_windowMaxHeight - spriteSize);

	AnimatedSprite sprite_chicken = AnimatedSprite(spriteTexture, x, y, spriteSize, spriteSize, 0, 0, 0.5, 1); 

	// Walking Animation
	int numFrames = 2;
	int timeToNextFrame = 150;
	AnimationFrame* frames_walking = new AnimationFrame[numFrames];
	frames_walking[0] = AnimationFrame(0,0,0.5,1);
	frames_walking[1] = AnimationFrame(0.5,0,0.5,1);
	Animation animation_walking = Animation("Walking", frames_walking, numFrames);
	sprite_chicken.animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);

	// Idle Animation
	numFrames = 1;
	AnimationFrame* frames_idle = new AnimationFrame[numFrames];
	frames_idle[0] = AnimationFrame(0,0,0.5,1);
	Animation animation_idle = Animation("Idle", frames_idle, numFrames);
	sprite_chicken.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);
	sprite_chicken.setAnimation("Walking");
	
	// Set Chicken direction
	sprite_chicken.setSpeed(getSpeed(), getSpeed());

	// Set direction
	if (sprite_chicken.speedX < 0)
		sprite_chicken.isFlippedX = true;
	else if (sprite_chicken.speedX > 0)
		sprite_chicken.isFlippedX = false;

	// Load sprite into bucket
	x = sprite_chicken.x;
	y = sprite_chicken.y;
	g_spriteBuckets[whichBucket(x, y)].push_back(sprite_chicken);
}
/*-----------------------------------------------*/
Uint32 chickenAI(Uint32 interval, void *param)
{
	updateCheckBuckets();
	int numOfBuckets = g_spriteBuckets.size();

	for (int i = 0; i < g_numOfCheckBuckets; i++)
	{
		if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
		{
			int bucket = g_checkBuckets[i];
			for (int j = 0; j < (int) g_spriteBuckets[bucket].size(); j++)
			{
				AnimatedSprite* chicken = &g_spriteBuckets[bucket][j];
				int speedX = chicken->speedX;
				int speedY = chicken->speedY;

				// If stopped Restart Chicken
				if (speedX == 0 && speedY == 0)
				{
					speedX = getSpeed();
					speedY = getSpeed();
					chicken->setAnimation("Walking");

					// Set direction
					if (speedX < 0)
						chicken->isFlippedX = true;
					else if (speedX > 0)
						chicken->isFlippedX = false;
				}
				else
				{
					// Randomly stop chickens
					int willStop = rand() % 2;
					if (willStop)
					{
						speedX = 0;
						speedY = 0;
						chicken->setAnimation("Idle");
					}
				}

				chicken->setSpeed(speedX, speedY);
			}
		}
	}

	return interval;
}
/*-----------------------------------------------*/
Uint32 updateSprites(Uint32 interval, void *param)
{
	updateCheckBuckets();

	int numOfBuckets = g_spriteBuckets.size();
	
	for (int i = 0; i < g_numOfCheckBuckets; i++)
	{
		if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
		{
			int bucket = g_checkBuckets[i];
			int spriteBucketSize = g_spriteBuckets.size();
			int bucketSize = g_spriteBuckets[bucket].size();
			for (int j = 0; j < bucketSize; j++)
			{
				AnimatedSprite* sprite = &g_spriteBuckets[bucket][j];
				sprite->update(diff_time);

				// Rebucket if necessary
				int newBucket = whichBucket(sprite->x, sprite->y);
				if (newBucket >= 0 && newBucket < spriteBucketSize && newBucket != bucket)
				{
					g_spriteBuckets[newBucket].push_back(*sprite);
					g_spriteBuckets[bucket].erase(g_spriteBuckets[bucket].begin() + j);
					j--;
					bucketSize--;
				}
				if (j >= 0)
					g_spriteBuckets[bucket][j].update(diff_time);

				//TODO update/move chicken in a bucket
			}
		}
	}

	// Update player
	g_player.update(diff_time);

	return interval;
}
/*-----------------------------------------------*/
static void drawSprites()
{
	updateCheckBuckets();

	int numOfBuckets = g_spriteBuckets.size();
	
	for (int i = 0; i < g_numOfCheckBuckets; i++)
	{
		if (g_checkBuckets[i] >= 0 && g_checkBuckets[i] < numOfBuckets)
		{
			int bucket = g_checkBuckets[i];
			for (int j = 0; j < (int) g_spriteBuckets[bucket].size(); j++)
			{
				// Only draw if sprite is on screen
				if (g_cam.collider.AABBIntersect(&g_spriteBuckets[bucket][j].collider))
					g_spriteBuckets[bucket][j].drawUV(g_cam.x, g_cam.y);
			}
		}
	}

	g_player.drawUV(g_cam.x, g_cam.y);
}
/*-----------------------------------------------*/
static int getSpeed()
{
	int speed = rand() % 2;
	int negation = rand() % 2;
	if (negation)
		speed *= -1;
	return speed * chickenSpeed;
}
/*-----------------------------------------------*/
static void loadLevel()
{
	g_level[g_currentLevel] = TileLevel();
	tileLoader::loadTiles("./Levels/level1.txt", g_level);
}
/*-----------------------------------------------*/
static void clearBackground()
{
	float r,g,b;
	r = 0;
	g = 0;
	b = 0;
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}
/*-----------------------------------------------*/
static void keyboard()
{
	player::playerKeyboard(&g_player, kbState, kbPrevState);

	if (kbState[ SDL_SCANCODE_LEFT ])
	{
		g_cam.updateX(-camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_RIGHT ])
	{
		g_cam.updateX(camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_UP ])
	{
		g_cam.updateY(-camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_DOWN ])
	{
		g_cam.updateY(camSpeed);
	}
	else if (kbState[ SDL_SCANCODE_ESCAPE ])
	{
		shouldExit = true;
	}
	else if (kbState[ SDL_SCANCODE_EQUALS] || kbState[ SDL_SCANCODE_KP_PLUS ])
	{
		makeChicken();
	}
	else if (kbState[SDL_SCANCODE_MINUS] || kbState[SDL_SCANCODE_KP_MINUS])
	{
		// Remove a random chicken
		int numOfBuckets = g_spriteBuckets.size();
		int choice = rand() % numOfBuckets;

		if (g_spriteBuckets[choice].size() > 0)
			g_spriteBuckets[choice].pop_back();
	}
}
/*-----------------------------------------------*/
int main( void )
{	
	srand((unsigned int) time(NULL));

	// Setup calls
	if (initSDL())
		return 1;

	init2D();
	loadLevel();
	initCamera();
	initBuckets();
	loadSprites();

	SDL_TimerID spriteTimer = SDL_AddTimer(33, updateSprites, (void *) "spriteTimer Callback");
	SDL_TimerID AITimer = SDL_AddTimer(2000, chickenAI, (void *) "chickenAI Callback");
	int last_time = 0;
	int cur_time = 0;
	diff_time = 0;

	// Read keyboard status
	kbState = SDL_GetKeyboardState( NULL );

	// The game loop
	while( !shouldExit ) 
	{
		memcpy (kbPrevState, kbState, sizeof( kbPrevState ));

		// Handle OS message pump
		SDL_Event event;
		while( SDL_PollEvent( &event )) 
		{
			switch( event.type ) 
			{
				case SDL_QUIT:
				return 0;
			}
		}

		// Game logic goes here
		keyboard();

		// Timer updates
		cur_time = SDL_GetTicks();
		diff_time = cur_time - last_time;
		last_time = cur_time;
		
		// All calls to glDrawSprite go here
		clearBackground();
		g_level[g_currentLevel].drawLevel(g_cam.x, g_cam.y, g_windowWidth, g_windowHeight);
		drawSprites();

		SDL_GL_SwapWindow( g_window );
	}

	SDL_Quit();
	return 0;
}