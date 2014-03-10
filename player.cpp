#include "player.h"

enum {IDLE, WALKING, RUN_SHOOTING, JUMPING, PRONE, PRONE_SHOOTING, IDLE_SHOOT, WALKING_GUN_UP, WALKING_GUN_DOWN};

PlayerSprite player::makePlayer(GLuint texture, int textureWidth, int textureHeight)
{
	PlayerSprite player;
	float cellSize = 16;
	float uSize = 1 / (textureWidth / cellSize);
	float vSize = 1 / (textureHeight / cellSize);
	int startX = 20;
	int startY = 120;
	int health = 100;

	player = PlayerSprite(texture, startX, startY, 100, 100, 
		0, 8 * vSize, 2 * uSize , 3 * vSize, health);

	int numFrames = 1;
	int timeToNextFrame = 100;

	// Idle Animation
	AnimationFrame* frames_idle = new AnimationFrame[numFrames];
	frames_idle[0] = AnimationFrame(0 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_idle = Animation("Idle", frames_idle, numFrames);
	player.animations[animation_idle.name] = AnimationData(animation_idle, timeToNextFrame, true);

	// Walking Animation
	numFrames = 4;
	AnimationFrame* frames_walking = new AnimationFrame[numFrames];
	frames_walking[0] = AnimationFrame(0 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_walking[1] = AnimationFrame(3 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_walking[2] = AnimationFrame(6 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_walking[3] = AnimationFrame(9 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_walking = Animation("Walking", frames_walking, numFrames);
	player.animations[animation_walking.name] = AnimationData(animation_walking, timeToNextFrame, true);

	// WalkingGunUp Animation
	numFrames = 4;
	AnimationFrame* frames_walkingGunUp = new AnimationFrame[numFrames];
	frames_walkingGunUp[0] = AnimationFrame(0 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunUp[1] = AnimationFrame(3 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunUp[2] = AnimationFrame(6 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunUp[3] = AnimationFrame(9 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_walkingGunUp = Animation("WalkingGunUp", frames_walkingGunUp, numFrames);
	player.animations[animation_walkingGunUp.name] = AnimationData(animation_walkingGunUp, timeToNextFrame, true);

	// WalkingGunDown Animation
	numFrames = 4;
	AnimationFrame* frames_walkingGunDown = new AnimationFrame[numFrames];
	frames_walkingGunDown[0] = AnimationFrame(12 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunDown[1] = AnimationFrame(15 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunDown[2] = AnimationFrame(18 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	frames_walkingGunDown[3] = AnimationFrame(21 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_walkingGunDown = Animation("WalkingGunDown", frames_walkingGunDown, numFrames);
	player.animations[animation_walkingGunDown.name] = AnimationData(animation_walkingGunDown, timeToNextFrame, true);

	// Jumping Animation
	numFrames = 4;
	AnimationFrame* frames_jumping = new AnimationFrame[numFrames];
	frames_jumping[0] = AnimationFrame(9 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_jumping[1] = AnimationFrame(12 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_jumping[2] = AnimationFrame(15 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_jumping[3] = AnimationFrame(18 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_jumping = Animation("Jumping", frames_jumping, numFrames);
	player.animations[animation_jumping.name] = AnimationData(animation_jumping, timeToNextFrame, true);
	
	// Prone Animation
	numFrames = 1;
	AnimationFrame* frames_prone = new AnimationFrame[numFrames];
	frames_prone[0] = AnimationFrame(0 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_prone = Animation("Prone", frames_prone, numFrames);
	player.animations[animation_prone.name] = AnimationData(animation_prone, timeToNextFrame, true);

	// Death Animation
	numFrames = 2;
	timeToNextFrame = 75;
	AnimationFrame* frames_death = new AnimationFrame[numFrames];
	frames_death[0] = AnimationFrame(21 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_death[1] = AnimationFrame(24 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_death = Animation("Death", frames_death, numFrames);
	player.animations[animation_death.name] = AnimationData(animation_death, timeToNextFrame, false);

	// IdleShooting Animation
	numFrames = 3;
	timeToNextFrame = 20;
	AnimationFrame* frames_shooting = new AnimationFrame[numFrames];
	frames_shooting[0] = AnimationFrame(6 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_shooting[1] = AnimationFrame(0 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	frames_shooting[2] = AnimationFrame(3 * uSize, 11 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_shooting = Animation("Shooting", frames_shooting, numFrames);
	player.animations[animation_shooting.name] = AnimationData(animation_shooting, timeToNextFrame, true);

	// RunShooting Animation
	numFrames = 8;
	timeToNextFrame = 50;
	AnimationFrame* frames_runShooting = new AnimationFrame[numFrames];
	frames_runShooting[0] = AnimationFrame(12 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[1] = AnimationFrame(0 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[2] = AnimationFrame(15 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[3] = AnimationFrame(3 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[4] = AnimationFrame(18 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[5] = AnimationFrame(6 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[6] = AnimationFrame(21 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	frames_runShooting[7] = AnimationFrame(9 * uSize, 7 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_runShooting = Animation("RunShooting", frames_runShooting, numFrames);
	player.animations[animation_runShooting.name] = AnimationData(animation_runShooting, timeToNextFrame, true);

	// ProneShooting Animation
	numFrames = 3;
	timeToNextFrame = 20;
	AnimationFrame* frames_proneShooting = new AnimationFrame[numFrames];
	frames_proneShooting[0] = AnimationFrame(6 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	frames_proneShooting[1] = AnimationFrame(0 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	frames_proneShooting[2] = AnimationFrame(3 * uSize, 0 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_proneShooting = Animation("ProneShooting", frames_proneShooting, numFrames);
	player.animations[animation_proneShooting.name] = AnimationData(animation_proneShooting, timeToNextFrame, true);

	// LookUp Animation
	numFrames = 1;
	timeToNextFrame = 100;
	AnimationFrame* frames_lookUp = new AnimationFrame[numFrames];
	frames_lookUp[0] = AnimationFrame(24 * uSize, 3 * vSize, 3 * uSize, 3 * vSize);
	Animation animation_lookUp = Animation("LookUp", frames_lookUp, numFrames);
	player.animations[animation_lookUp.name] = AnimationData(animation_lookUp, timeToNextFrame, true);

	// Initialize animation and return
	player.setAnimation("Idle");
	return player;
}

void player::playerKeyboard(PlayerSprite* player, const unsigned char* kbState, unsigned char* kbPrevState)
{
	// Player Direction
	if (kbState[SDL_SCANCODE_A] && !kbPrevState[SDL_SCANCODE_A])
	{
		player->isFlippedX = true;
		if (player->speedX > 0)
			player->speedX *= -1;
	}
	else if (kbState[SDL_SCANCODE_D] && !kbPrevState[SDL_SCANCODE_D])
	{
		player->isFlippedX = false;
		if (player->speedX < 0)
			player->speedX *= -1;
	}

	// Player States
	// IDLE State
	if (player->state == IDLE)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Idle");
			player->prevState = player->state;

			player->setSpeed(0,0);
		}

		// Check for new Transition
		if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_D])
			player->state = WALKING;
		else if (kbState[SDL_SCANCODE_J])
			player->state = IDLE_SHOOT;
		else if (kbState[SDL_SCANCODE_S])
			player->state = PRONE;
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
	// WALKING State
	else if (player->state == WALKING)	
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Walking");
			player->prevState = player->state;

			player->setSpeed(maxSpeed,0);
			if (player->isFlippedX)
				player->speedX *= -1;
		}

		// Check for new Transition
		if (!kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D])
			player->state = IDLE;
		else if (kbState[SDL_SCANCODE_J])
			player->state = RUN_SHOOTING;
		else if (kbState[SDL_SCANCODE_S])
			player->state = PRONE;
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
	// RUN SHOOTING State
	else if (player->state == RUN_SHOOTING)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("RunShooting");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = IDLE_SHOOT;
			else
				player->state = IDLE;
		}
		else if ((kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_D]) && !kbState[SDL_SCANCODE_J])
			player->state = WALKING;
		else if (kbState[SDL_SCANCODE_S])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = PRONE_SHOOTING;
			else
				player->state = PRONE;
		}
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
	// JUMPING State
	else if (player->state == JUMPING)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Jumping");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = IDLE_SHOOT;
			else
				player->state = IDLE;
		}
		else if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_D])
		{
			if(kbState[SDL_SCANCODE_J])
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (kbState[SDL_SCANCODE_S])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = PRONE_SHOOTING;
			else
				player->state = PRONE;
		}
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
	// PRONE State
	else if (player->state == PRONE)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Prone");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!kbState[SDL_SCANCODE_S] && !kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D] && !kbState[SDL_SCANCODE_SPACE])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = IDLE_SHOOT;
			else
				player->state = IDLE;
		}
		else if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_D])
		{
			// Fix for Gun Up / Gun Down
			if(kbState[SDL_SCANCODE_J])
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (kbState[SDL_SCANCODE_J])
		{
			player->state = PRONE_SHOOTING;
		}
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
	// PRONE SHOOTING State
	else if (player->state == PRONE_SHOOTING)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("ProneShooting");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!kbState[SDL_SCANCODE_S] && !kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D] && !kbState[SDL_SCANCODE_SPACE])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = IDLE_SHOOT;
			else
				player->state = IDLE;
		}
		else if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_D])
		{
			// Fix for Gun Up / Gun Down
			if(kbState[SDL_SCANCODE_J])
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (kbState[SDL_SCANCODE_S] && !kbState[SDL_SCANCODE_J])
		{
			player->state = PRONE;
		}
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
	// IDLE SHOOT State
	else if (player->state == IDLE_SHOOT)
	{
		// Handle State Transition
		if (player->state != player->prevState)
		{
			player->setAnimation("Shooting");
			player->prevState = player->state;
		}

		// Check for new Transition
		if (!kbState[SDL_SCANCODE_J] && !kbState[SDL_SCANCODE_A] && !kbState[SDL_SCANCODE_D] && !kbState[SDL_SCANCODE_SPACE])
		{
			player->state = IDLE;
		}
		else if (kbState[SDL_SCANCODE_A] || kbState[SDL_SCANCODE_D])
		{
			// Fix for Gun Up / Gun Down
			if(kbState[SDL_SCANCODE_J])
				player->state = RUN_SHOOTING;
			else
				player->state = WALKING;
		}
		else if (kbState[SDL_SCANCODE_S])
		{
			if (kbState[SDL_SCANCODE_J])
				player->state = PRONE_SHOOTING;
			else
				player->state = PRONE;
		}
		else if (kbState[SDL_SCANCODE_SPACE])
			player->state = JUMPING;
	}
}
