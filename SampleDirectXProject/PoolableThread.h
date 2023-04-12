#pragma once
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;

class PoolableThread : public IETThread
{
public:
	PoolableThread(int id, IFinishedTask* finishedTask);
	~PoolableThread();

	int getID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;

	int id = 0;
	IWorkerAction* action; // stream asset loader
	IFinishedTask* finishedTask;
};
