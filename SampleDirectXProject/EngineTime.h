#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class Window;
class LoadingScreen;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
	static float getFPS();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const) {};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;

	static void LogFrameStart();
	static void LogFrameEnd();
	float fps = 0.0f;

	friend class Window;
	friend class LoadingScreen;
};

