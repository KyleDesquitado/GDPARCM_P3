#include "StreamAssetLoader.h"
#include <iostream>
#include "TextureManager.h"
#include "AudioManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

StreamAssetLoader::StreamAssetLoader(String path, AssetType type, IExecutionEvent* executionEvent)
{
	this->streamAssetPath = path;
	this->executeEvent = executionEvent;
	this->assetType = type;
}

StreamAssetLoader::~StreamAssetLoader()
{

}


void StreamAssetLoader::onStartTask()
{
	//simulate loading of very large file
	IETThread::sleep(200);

	std::vector<String> tokens = StringUtils::split(streamAssetPath, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	if (assetType == TEXTURE_ASSETS)
	{
		TextureManager::getInstance()->instantiateAsTexture(streamAssetPath, assetName, true);

		std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	}
	if (assetType == AUDIO_ASSETS)
	{
		AudioManager::getInstance()->instantiateAsSound(streamAssetPath, assetName, true);

		std::cout << "[AudioManager] Loaded streaming audio: " << assetName << std::endl;

	}

	this->executeEvent->onFinishedExecution();
	//delete after being done
	delete this;
}