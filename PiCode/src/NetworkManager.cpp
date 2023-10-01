#include "NetworkManager.h"

namespace SWE4211RPi {
	NetworkManager::NetworkManager(unsigned short port, CommandQueue *queue[],
			std::string threadName):
				RunnableClass(threadName,50){
		this->portNumber = port;
		this->referencequeue=queue;

	}

	void NetworkManager::run() {

	}

	void NetworkManager::stop() {

	}

	int NetworkManager::getSocketID() {

	}

	int NetworkManager::processReceivedMessage(
			networkMessageStruct &receivedMessage) {

	}

	void NetworkManager::reportNewClientConnection(
			const struct sockaddr_in &clientAddress) {

	}
}
