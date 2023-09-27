#include <"CommandQueue.h">

using namespace SWE4211RPi;
using namespace std;

  CommandQueue::CommandQueue(){
	  sem_init(&queueCountSemaphore, 0);
  }

  CommandQueue::hasItem(){
	  unique_lock(queueMutex);
	  return this->commandQueueContents.empty();
  }

  CommandQueueEntry CommandQueue::dequeue(){
	  unique_lock(queueMutex);
	  sem_wait(&queueCountSemaphore);
	  return commandQueueContents.front();
  }

 void CommandQueue::enqueue(CommandQueryEntry value){
	 commandQueueContents.push(value);
	 sem_post(&queueCountSemaphore);
 }


