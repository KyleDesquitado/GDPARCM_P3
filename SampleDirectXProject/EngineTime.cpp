#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

float EngineTime::getFPS()
{
	return sharedInstance->fps;
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();
	sharedInstance->fps = 1.0f / sharedInstance->deltaTime;

	sharedInstance->fps = std::clamp<float>(sharedInstance->fps, 0, 60);
	std::cout << sharedInstance->fps << std::endl;
}
