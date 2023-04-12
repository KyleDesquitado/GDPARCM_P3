#include "AssetLoader.h"
#include <iostream>
#include "TextureManager.h"
#include "AudioManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "MathUtils.h"
#include "GameManager.h"

AssetLoader::AssetLoader(): AGameObject("AssetLoader")
{
	
}

void AssetLoader::initialize()
{
	
}

void AssetLoader::processInput(sf::Event event)
{
	
}

void AssetLoader::update(sf::Time deltaTime)
{

	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();
	

	if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->numLoadedTexture, this);
		this->numLoadedTexture++;

		AudioManager::getInstance()->loadSingleStreamAsset(this->numLoadedAudio, this);
		this->numLoadedAudio++;
	}

}


void AssetLoader::onFinishedExecution()
{
	GameManager::getInstance()->nLoadedAssets++;

	
}
