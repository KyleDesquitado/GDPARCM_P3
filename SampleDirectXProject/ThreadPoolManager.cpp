#include "ThreadPoolManager.h"
#include "PoolableThread.h"


ThreadPoolManager::ThreadPoolManager(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	// create thread workers and add this class as the lister
	for (int i = 0; i < this->numWorkers; i++)
	{
		this->inactiveThreads.push(new PoolableThread(i, this));
	}
}

ThreadPoolManager::~ThreadPoolManager()
{
	this->stopScheduler();
	this->activeThreads.clear();
	while (this->inactiveThreads.empty() == false)
	{
		this->inactiveThreads.pop();
	}
}

void ThreadPoolManager::startScheduler()
{
	// start scheduler
	this->running = true;
	this->start();
}

void ThreadPoolManager::stopScheduler()
{
	this->running = false;
}

void ThreadPoolManager::addTask(IWorkerAction* action)
{
	this->pendingTasks.push(action);
}

void ThreadPoolManager::run()
{
	while (this->running)
	{
		//check if there are pending actions to perform
		if (this->pendingTasks.empty() == false)
		{
		
			// check if there are avaiolable threads
			if (this->inactiveThreads.empty() == false)
			{
				//create thread worker and assign the first inactive thread = available
				PoolableThread* workerThread = this->inactiveThreads.front(); 
				// remove the first element
				this->inactiveThreads.pop(); 
				// add the used thread to the map of active threads using id
				this->activeThreads[workerThread->getID()] = workerThread; 
				
				// add actions (stream asset loader action) to pending actions queue
				workerThread->assignTask(this->pendingTasks.front());
				// start the thread
				workerThread->start();
				// remove the excexuted thread
				this->pendingTasks.pop();
			}
			else
			{
				//std::cout << "No Available thread" << std::endl;
			}

		}
		else
		{
			//std::cout << "No tasks scheduled" << std::endl;
		}
	}
}

void ThreadPoolManager::onFinished(int threadID)
{
	//delete and create new thread when finished
	if (this->activeThreads[threadID] != nullptr)
	{
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolableThread(threadID, this));

	}
}