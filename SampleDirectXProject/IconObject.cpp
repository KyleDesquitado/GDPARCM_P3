#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "GameObjectManager.h"
#include "GameManager.h"

IconObject::IconObject(String name, int textureIndex, int direction): AGameObject(name)
{
	this->textureIndex = textureIndex;
	this->dir = direction;


}

void IconObject::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	texture = TextureManager::getInstance()->getFromTextureMap(name,0);
	this->sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	this->sprite->setTexture(*texture);



	sf::Color color	 = sprite->getColor();
	color.a = 0;

	sprite->setColor(color);

	setScale(1.3, 1.3);
	//cout << "dir: " << dir << "\n";
	this->setPosition(BaseRunner::WINDOW_WIDTH / 2 + (dir*200), BaseRunner::WINDOW_HEIGHT*.60);

	if (AudioManager::getInstance()->getFromSoundMap(name, 0) != NULL)
	{
		AudioManager::getInstance()->getFromSoundMap(name, 0)->play();
	}

	sf::Vector2f scaleFactor;
	if (GameManager::getInstance()->nDisplayedAssets == TextureManager::getInstance()->getStreamingAssetsCount())
	{
		scaleFactor  = sf::Vector2f((float)BaseRunner::WINDOW_WIDTH / texture->getSize().x, (float)BaseRunner::WINDOW_HEIGHT / texture->getSize().y);
		state = HOLD;
		setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT * 0.80);
		setScale(scaleFactor.x/2, scaleFactor.x / 2);
	};
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
	sf::Color fadeColor = sprite->getColor();
	float newAlpha = fadeColor.a;

	switch (state)
	{
		case FADEIN: 
		
			if (fadeTicks < inDelay)
			{
				fadeTicks += deltaTime.asSeconds();
				newAlpha = (fadeTicks / inDelay) * 255;
				fadeColor.a = newAlpha <= 255 ? newAlpha : 255;
			}
			else
			{
				fadeTicks = 0;
				state = PAUSE;
			}
		 break;

		case PAUSE:
		
		if (fadeTicks < pauseDelay)
			{
				fadeTicks += deltaTime.asSeconds();
			}
			else	
			{
				fadeTicks = 0;
				state = FADEOUT;
			}
		 break;

		case FADEOUT:
		
			if (fadeTicks < outDelay)
			{
				fadeTicks += deltaTime.asSeconds();
				newAlpha = 255-(fadeTicks / inDelay) * 255;
				fadeColor.a = newAlpha >= 0 ? newAlpha : 0;
			}
			else
			{
				fadeTicks = 0;
				state = IDLE;
				GameObjectManager::getInstance()->deleteObject(this);
				return;
			}
		 break;


		case HOLD:
			if (fadeTicks < inDelay+3)
			{
				fadeTicks += deltaTime.asSeconds();
				newAlpha = (fadeTicks / (inDelay/2)) * 255;
				fadeColor.a = newAlpha <= 255 ? newAlpha : 255;
				sprite->setColor(fadeColor);
			}
			else
			{
				fadeTicks = 0;
				AudioManager::getInstance()->playSoundOnce("ping_sfx", 0);
				AudioManager::getInstance()->stopSound("main_bgm", 1);
				AudioManager::getInstance()->playSoundOnce("end_bgm", 0);
				
				state = END;
			}
			break;

		case  END:

			
				AudioManager::getInstance()->playSoundOnce("251", 0);
				state = IDLE;

			break;

		default: IDLE;
	}

	if (state < 3)
	{
		//std::cout << "state: " << state << "\n";
		sprite->setColor(fadeColor);

		sf::Vector2f pos = getPosition();
		sf::Vector2f scale = getScale();
		if (pos.y >= BaseRunner::WINDOW_HEIGHT * .20)
		{
			float mid = BaseRunner::WINDOW_WIDTH / 2;



			setPosition(pos.x + (deltaTime.asSeconds() * -dir * 100), pos.y - deltaTime.asSeconds() * 100);
			setScale(scale.x - deltaTime.asSeconds() / 4, scale.y - deltaTime.asSeconds() / 4);
		}
	}
	


	
}
