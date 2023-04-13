#include "ThreadPool.h"
#include "PoolWorkerThread.h"


ThreadPool::ThreadPool(String name, int numThreads)
{
	this->name = name;
	this->numThreads = numThreads;

	for (int i = 0; i < this->numThreads; i++)
	{
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();
	this->activeThreads.clear();

	while (this->inactiveThreads.empty() == false)
	{
		this->inactiveThreads.pop();
	}
}

void ThreadPool::startScheduler()
{

	this->running = true;

	this->start();
}

void ThreadPool::stopScheduler()
{
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}



void ThreadPool::run()
{
	while (this->running)
	{
		if (this->pendingActions.empty() == false)
		{
			if (this->inactiveThreads.empty() == false)
			{
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				workerThread->start();
				this->pendingActions.pop();

				std::cout << "[ThreadPool " << this->name << "] Scheduling task to: " << workerThread->getThreadID() << std::endl;
			}
		}
	}
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID] != nullptr)
	{
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));

	}
}