#include "IETThread.h"

IETThread::IETThread()
{
}

IETThread::~IETThread()
{
}

void IETThread::start()
{
	std::thread myThread(&IETThread::run, this);
	myThread.detach();
}

void IETThread::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
