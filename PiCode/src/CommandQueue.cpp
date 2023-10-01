#include "CommandQueue.h"

using namespace std;
namespace SWE4211RPi {

CommandQueue::CommandQueue() {
	sem_init(&queueCountSemaphore,0, 0);
}

bool CommandQueue::hasItem() {
	unique_lock<mutex>lck (queueMutex);
	return this->commandQueueContents.empty();
}

CommandQueueEntry CommandQueue::dequeue() {
	unique_lock<mutex> lck(queueMutex);
	sem_wait(&queueCountSemaphore);
	return commandQueueContents.front();
}

void CommandQueue::enqueue(CommandQueueEntry value) {
	commandQueueContents.push(value);
	sem_post(&queueCountSemaphore);
}

}
