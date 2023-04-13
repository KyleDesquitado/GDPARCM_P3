#include "PoolManager.h"

std::string PoolManager::COURIER_POOL_TAG = "CourierPool";
std::string PoolManager::TREASURE_CHEST_POOL_TAG = "TreasureChestPool";
std::string PoolManager::BERRY_POOL_TAG = "BerryPool";


PoolManager* PoolManager::sharedInstance = NULL;

PoolManager* PoolManager::getInstance()
{
	if (sharedInstance == nullptr) 
	{
		sharedInstance = new PoolManager();
	}

	return sharedInstance;
}

void PoolManager::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}

void PoolManager::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
	delete pool;
}

GameObjectPool* PoolManager::getPool(std::string tag)
{
	return this->poolMap[tag];
}