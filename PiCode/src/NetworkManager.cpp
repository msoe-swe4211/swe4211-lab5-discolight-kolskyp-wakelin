#include "NetworkManager.h"
#include "networkMessage.h"
#include <sys/socket.h>

namespace SWE4211RPi {
	NetworkManager::NetworkManager(unsigned short port, CommandQueue *queue[], std::string threadName):
		this->portNumber = port;
		this->referencequeue=queue;
	}

	void NetworkManager::run() {
		// create socket
		struct sockaddr_in address;
		address.sin_family = AF_INET;
    		address.sin_addr.s_addr = INADDR_ANY;
    		address.sin_port = htons(portNumber);
		int addrlen = sizeof(address);

		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		int bind(sockfd, (struct sockaddr*)&address, addrlen);

		// Listen
		listen(sockfd, 2); 
		
		while (keepGoing) {
			int conn = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen));

			NetworkMessage message;
            		ssize_t bytesRead = recv(connectedSocket, &message, sizeof(NetworkMessage), 0);
			message = htonl(message);
			
			// Send to processer
			processReceivedMessage(message);
		}
	}

	void NetworkManager::stop() {

	}

	int NetworkManager::getSocketID() {
	}

	int NetworkManager::processReceivedMessage(networkMessageStruct &receivedMessage) {
		if (&receivedMessage.messageDestination = 1) {  // get from cfg instead
			// go to 0th queue
		} else if (&receivedMessage.messageDestination = 2) {
			// go to 1st queue
		}
	}

	void NetworkManager::reportNewClientConnection(
			const struct sockaddr_in &clientAddress) {

	}
}
