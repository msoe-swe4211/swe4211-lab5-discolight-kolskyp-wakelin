#include <"NetworkManger.h">

using namespace SWE4211Rpi;

NetworkManager::NetworkManager(unsigned short port, CommandQueue *queue[],
		std::string threadName) {

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
		const struct sockaddr_in &clientAddress){

}
