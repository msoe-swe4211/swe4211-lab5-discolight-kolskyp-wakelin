#include "CommandQueue.h"

using namespace std;
namespace SWE4211RPi {

CommandQueue::CommandQueue() {
	sem_init(&queueCountSemaphore, 0, 0);
}

CommandQueue::~CommandQueue() {
}

bool CommandQueue::hasItem() {
	unique_lock < mutex > lck(queueMutex);
	int semValue;
	sem_getvalue(&queueCountSemaphore, &semValue);

	if (semValue > 0) {
		return true;
	}
	return false;
}

CommandQueueEntry CommandQueue::dequeue() {
	unique_lock < mutex > lck(queueMutex);
	sem_wait(&queueCountSemaphore);
	auto ret = commandQueueContents.front();
	commandQueueContents.pop();
	return ret;
}

void CommandQueue::enqueue(CommandQueueEntry value) {
	unique_lock < mutex > lck(queueMutex);
	commandQueueContents.push(value);
	sem_post(&queueCountSemaphore);
}
}
