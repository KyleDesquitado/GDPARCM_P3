#include "PoolableThread.h"
#include "IWorkerAction.h"
#include "ThreadPoolManager.h"

PoolableThread::PoolableThread(int id, IFinishedTask* finishedTask)
{
	this->id = id;
	this->finishedTask = finishedTask;
}

PoolableThread::~PoolableThread()
{
}

int PoolableThread::getID()
{
	return this->id;
}

void PoolableThread::assignTask(IWorkerAction* action)
{
	this->action = action;
}

void PoolableThread::run()
{
	// excecute action
	this->action->onStartTask();
	this->finishedTask->onFinished(this->id);
}