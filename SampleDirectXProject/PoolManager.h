#pragma once
#include <SFML/Graphics.hpp>

#include "GameObjectPool.h"
#include <unordered_map>

typedef std::unordered_map<std::string, GameObjectPool*> PoolMap;

class PoolManager
{
public:
	static PoolManager* getInstance();

public:
	//pool names
	static std::string COURIER_POOL_TAG;
	static std::string TREASURE_CHEST_POOL_TAG;
	static std::string BERRY_POOL_TAG;


	void registerObjectPool(GameObjectPool* pool);
	void unregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* getPool(std::string tag);

private:
	PoolManager() {};
	PoolManager(PoolManager const&) {};             // copy constructor is private
	PoolManager& operator=(PoolManager const&) {};  // assignment operator is private
	static PoolManager* sharedInstance;


	PoolMap poolMap;
};

