#pragma once
#include <queue>
#include <unordered_map>
#include "IETThread.h"

class PoolableThread;
class IWorkerAction;
class IFinishedTask
{
public:
	virtual void onFinished(int threadID) = 0;
};

/// <summary>
/// Class that can hold N workers/threads that can be reused. This is a thread itself, because it needs to constantly schedule tasks.
/// </summary>
class ThreadPoolManager : public IETThread, public IFinishedTask
{
private:
	typedef std::string String;
	typedef std::queue<PoolableThread*> ThreadListQueue;
	typedef std::unordered_map<int, PoolableThread*> ThreadMap;
	typedef std::queue<IWorkerAction*> PendingThreadQueue;

public:
	ThreadPoolManager(String name, int numWorkers);
	~ThreadPoolManager();

	void startScheduler();
	void stopScheduler();
	void addTask(IWorkerAction* action);

private:
	void run() override;
	void onFinished(int threadID) override;

	String name;
	bool running = false;
	int numWorkers = 0;
	ThreadMap activeThreads;
	ThreadListQueue inactiveThreads;
	PendingThreadQueue pendingTasks;
};