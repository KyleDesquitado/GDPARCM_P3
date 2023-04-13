#pragma once
#include "AGameObject.h"
class IconObject :    public AGameObject
{
public:
	

	IconObject(String name, int textureIndex, int dir);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	enum DisplayState {
		FADEIN = 0,
		PAUSE = 1,
		FADEOUT = 2,
		IDLE = 3,
		HOLD=4,
		END =5
	};
	sf::Texture* texture;
	int textureIndex = 0;
	sf::Vector2f initialPos;

	DisplayState state = FADEIN;
	 
	float inDelay = .5;
	float pauseDelay = 2;
	float outDelay = 2;
	float fadeTicks =0;
	float xOffset=0;

	int dir = 0;
};

