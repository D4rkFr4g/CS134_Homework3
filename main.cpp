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
#include "DrawUtils.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include "TileLevel.h"
#include "tileLoader.h"

using namespace std;

static void keyboard();
static void clearBackground();
static void makeChicken();
static int getSpeed();

enum {R, G, B};
int currentColor = R;
float color[] = {0,0,0};
float currentDirection = 1;
int g_windowWidth = 640;
int g_windowHeight = 480;
int g_windowMaxWidth = 0;
int g_windowMaxHeight = 0;
Camera g_cam;
int camDelta = 20;
const int g_numOfLevels = 1;
int g_currentLevel = 0;
TileLevel level[g_numOfLevels];
int spriteSize = 64;
int spriteReserve = 50000;
int g_spriteArraySize;
std::vector<AnimatedSprite> spriteList;
GLuint spriteTexture;
int diff_time;
int initialChickens = 20;
int chickenSpeed = 50;

unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};
const unsigned char* kbState = NULL;
bool shouldExit = false;

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

static void initCamera()
{
	//g_cam = Camera(g_windowWidth, g_windowHeight, 0, g_windowMaxWidth, 0, g_windowMaxHeight);
	TileLevel currentLevel = level[g_currentLevel];

	g_windowMaxWidth = (currentLevel.width * currentLevel.tilesWidth) - g_windowWidth;
	g_windowMaxHeight = (currentLevel.height * currentLevel.tilesHeight) - g_windowHeight;

	g_cam = Camera(0, 0, 0, g_windowMaxWidth, 0, g_windowMaxHeight);
}

static void loadSprites()
{
	spriteList.reserve(spriteReserve);
	spriteTexture = glTexImageTGAFile("./Sprites/spriteSheet_chicken.tga", NULL, NULL);
	
	// Load the Initial chickens
	for (int i = 0; i < initialChickens; i++)
		makeChicken();
}

static void makeChicken()
{
	int x = rand() % ((g_windowWidth * 3) - spriteSize);
	int y = rand() % ((g_windowHeight *3) - spriteSize);

	AnimatedSprite sprite_chicken = AnimatedSprite(spriteTexture, x, y, spriteSize, spriteSize, 0, 0, 0.5, 1);
	// Walking Animation
	int numFrames = 2;
	int timeToNextFrame = 150;
	AnimationFrame* frames_walking = new AnimationFrame[numFrames];
	frames_walking[0] = AnimationFrame(0,0,0.5,1);
	frames_walking[1] = AnimationFrame(0.5,0,0.5,1);
	Animation animation_walking = Animation("Walking", frames_walking, numFrames);
	sprite_chicken.walkingAnimation = AnimationData(animation_walking, timeToNextFrame);
	// Idle Animation
	numFrames = 1;
	AnimationFrame* frames_idle = new AnimationFrame[numFrames];
	frames_idle[0] = AnimationFrame(0,0,0.5,1);
	Animation animation_idle = Animation("Idle", frames_idle, numFrames);
	sprite_chicken.idleAnimation = AnimationData(animation_idle, timeToNextFrame);
	sprite_chicken.walking();
	
	// Set Chicken direction
	sprite_chicken.setSpeed(getSpeed(), getSpeed());

	// Set direction
	if (sprite_chicken.speedX < 0)
		sprite_chicken.isFlippedX = true;
	else if (sprite_chicken.speedX > 0)
		sprite_chicken.isFlippedX = false;

	spriteList.push_back(sprite_chicken);
}

Uint32 updateSprites(Uint32 interval, void *param)
{
	for (int i = 0; i < (int) spriteList.size(); i++)
	{
		spriteList[i].update(diff_time);
	}

	return interval;
}

Uint32 chickenAI(Uint32 interval, void *param)
{
	for (int i = 0; i < (int) spriteList.size(); i++)
	{
		AnimatedSprite* chicken = &spriteList[i];
		int speedX = chicken->speedX;
		int speedY = chicken->speedY;

		// If stopped Restart Chicken
		if (speedX == 0 && speedY == 0)
		{
			speedX = getSpeed();
			speedY = getSpeed();
			chicken->walking();

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
				chicken->idle();
			}
		}

		chicken->setSpeed(speedX, speedY);
	}

	return interval;
}

static int getSpeed()
{
	int speed = rand() % 2;
	int negation = rand() % 2;
	if (negation)
		speed *= -1;
	return speed * chickenSpeed;
}

static void drawSprites()
{
	for (int i = 0; i < (int) spriteList.size(); i++)	
		spriteList[i].drawUV(g_cam.x, g_cam.y);
}

static void loadLevel()
{
	level[g_currentLevel] = TileLevel();
	tileLoader::loadTiles("./Levels/level1.txt", level);
}

using namespace std;
int main( void )
{	
	srand(time(NULL));

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) 
	{
		return 1;
	}
 
	// Create the window, OpenGL context
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_Window* window = SDL_CreateWindow(
	"Invincible Chickens",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	g_windowHeight, g_windowHeight,
	SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN );
	glCullFace( GL_BACK );


	if( !window ) 
	{
		SDL_Quit();
		return 1;
	}
	SDL_GL_CreateContext( window );

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

	// Setup calls
	init2D();
	loadSprites();
	loadLevel();
	initCamera();

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
		level[g_currentLevel].drawLevel(g_cam.x, g_cam.y);
		drawSprites();

		SDL_GL_SwapWindow( window );
	}

	SDL_Quit();
	return 0;
}

static void clearBackground()
{
	float r,g,b;
	r = 0;
	g = 0;
	b = 0;
	glClearColor(r,g,b,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

static void keyboard()
{
	if (kbState[ SDL_SCANCODE_LEFT ])
	{
		g_cam.updateX(-camDelta);
	}
	else if (kbState[ SDL_SCANCODE_RIGHT ])
	{
		g_cam.updateX(camDelta);
	}
	else if (kbState[ SDL_SCANCODE_UP ])
	{
		g_cam.updateY(-camDelta);
	}
	else if (kbState[ SDL_SCANCODE_DOWN ])
	{
		g_cam.updateY(camDelta);
	}
	else if (kbState[ SDL_SCANCODE_ESCAPE ])
	{
		shouldExit = true;
	}
	else if (kbState[ SDL_SCANCODE_EQUALS] | kbState[ SDL_SCANCODE_KP_PLUS ])
	{
		makeChicken();
	}
else if (kbState[SDL_SCANCODE_MINUS] || kbState[SDL_SCANCODE_KP_MINUS])
	{
		if (spriteList.size() > 0)
		{
			spriteList.pop_back();
		}
	}
}