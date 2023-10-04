#include "CommandQueue.h"

using namespace std;
namespace SWE4211RPi {

CommandQueue::CommandQueue() {
	sem_init(&queueCountSemaphore, 0, 0);
}

CommandQueue::~CommandQueue() {
	sem_destroy(&queueCountSemaphore);
}

bool CommandQueue::hasItem() {
	int semValue;
	sem_getvalue(&queueCountSemaphore, &semValue);

	if (semValue > 0) {
		return true;
	}
	return false;
}

CommandQueueEntry CommandQueue::dequeue() {
	sem_wait(&queueCountSemaphore);
	unique_lock < mutex > lock(queueMutex);
	auto ret = commandQueueContents.front();
	commandQueueContents.pop();
	return ret;
}

void CommandQueue::enqueue(CommandQueueEntry value) {
	unique_lock < mutex > lock(queueMutex);
	commandQueueContents.push(value);
	sem_post(&queueCountSemaphore);
}
}
