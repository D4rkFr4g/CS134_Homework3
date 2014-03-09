#include "AnimationData.h"


AnimationData::AnimationData(void)
{
}

AnimationData::AnimationData(Animation def, int timeToNextFrame, bool isRepeating)
{
	this->def = def;
	this->timeToNextFrame = timeToNextFrame;
	this->elapsedTime = 0;
	this->currentFrame = 0;
	this->isRepeating = isRepeating;
}

AnimationData::~AnimationData(void)
{
}

void AnimationData::resetElapsedTime()
{
	elapsedTime = 0;
}

void AnimationData::updateTime(int ms)
{
	elapsedTime += ms;

	if (elapsedTime > timeToNextFrame)
	{
		resetElapsedTime();
		advanceFrame();
	}
}

void AnimationData::advanceFrame()
{
	currentFrame++;
	if (currentFrame >= def.numFrames)
	{
		if (isRepeating)
			currentFrame = 0;
		else
			currentFrame = def.numFrames - 1;
	}
}