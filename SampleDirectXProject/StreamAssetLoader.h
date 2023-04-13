#pragma once
#include "IWorkerAction.h"
#include <iostream>
class IExecutionEvent;
class StreamAssetLoader : public IWorkerAction
{
public:
	enum AssetType
	{
		TEXTURE_ASSETS,
		AUDIO_ASSETS,
	};

private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, AssetType type, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	String streamAssetPath;
	String steamAssetAudioPath;
	IExecutionEvent* executeEvent;
	AssetType assetType;
};