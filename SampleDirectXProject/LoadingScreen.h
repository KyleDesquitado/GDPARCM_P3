#pragma once
#include "UIScreen.h"
#include <iostream>

using namespace std;

class LoadingScreen : public UIScreen
{
public:
	LoadingScreen();
	~LoadingScreen();
	void DrawUI() override;
	bool isEnabled[5] = { 0,0,0,0,0 };
	bool isAllEnabled = 0;
	float progress[5] = { 0,0,0,0,0 };
	float progressSummary = 0;

};

