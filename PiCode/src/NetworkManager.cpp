#include "NetworkManager.h"
#include <sys/socket.h>

namespace SWE4211RPi {
	NetworkManager::NetworkManager(unsigned short port, CommandQueue *queue[], std::string threadName):
		this->portNumber = port;
		this->referencequeue=queue;
	}

	void NetworkManager::run() {
		// create thread
		
		// create socket
		struct sockaddr_in address;
		address.sin_family = AF_INET;
    		address.sin_addr.s_addr = INADDR_ANY;
    		address.sin_port = htons(8000); // how do i know the #?
		int addrlen = sizeof(address);

		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		int bind(sockfd, (struct sockaddr*)&address, sizeof(address));
		
		while (keepGoing) {
			// Listen
			listen(sockfd, 10);  // Unsure on 10
			int conn = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen));
				
			// Convert to networkMessage
			struct networkMessageStruct networkMessage;
			int32_t message, messageDestination, messageID, param1, param2, securityMode, timestampHigh, timestampLow, xorChecksum;
			
			// Send to processer
			processReceivedMessage(&netowkrMessage);
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
