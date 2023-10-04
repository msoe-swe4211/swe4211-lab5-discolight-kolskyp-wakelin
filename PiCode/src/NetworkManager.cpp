#include "NetworkManager.h"
#include <strings.h>
#include <iostream>

namespace SWE4211RPi {
NetworkManager::NetworkManager(unsigned short port, CommandQueue *queue[],
		std::string threadName) :
		RunnableClass(threadName, 1) {
	this->portNumber = port;
	this->referencequeue = queue;
}

NetworkManager::~NetworkManager() {
}

void NetworkManager::run() {

	//Create new socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket failed");
		exit(1);
	}

	//Set the socket options
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt))) {
		perror("Failed to set the socket options.");
		exit(1);
	}

	//Declare the port and the address
	sockaddr_in address = { 0 };
	address.sin_family = AF_INET;
	address.sin_port = htons(portNumber);
	address.sin_addr.s_addr = INADDR_ANY;

	//Bind the socket to the given port
	if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
		perror("Binding failed");
		exit(1);
	}
	// Listen for connections
	listen(server_fd, 1);
	unsigned int addrlen = sizeof(address);

	//Accept new connection
	if ((connectedSocket = accept(server_fd, (struct sockaddr*) &address,
			&addrlen)) < 0) {

		perror("Error while accepting connection.");
		exit(1);
	}

	while (keepGoing) {

		struct networkMessageStruct message;
		networkMessageStruct *buffer = &message;

		ssize_t bytesRead = recvfrom(connectedSocket, (void*) &buffer[0],
				sizeof(struct networkMessageStruct), MSG_WAITALL, nullptr,
				nullptr);

		if (bytesRead == 0) {
			this->stop();
		}

		//Got full message
		else {

			//Convert endiannes
			message.securityMode = ntohl(message.securityMode);
			message.messageID = ntohl(message.messageID);
			message.timestampHigh = ntohl(message.timestampHigh);
			message.timestampLow = ntohl(message.timestampLow);
			message.messageType = ntohl(message.messageType);
			message.messageDestination = ntohl(message.messageDestination);
			message.message = ntohl(message.message);
			message.parameter1 = ntohl(message.parameter1);
			message.parameter2 = ntohl(message.parameter2);
			message.xorChecksum = ntohl(message.xorChecksum);

			// Send to processer
			processReceivedMessage(message);
		}
	}
}

void NetworkManager::stop() {

	//Call parrent method
	RunnableClass::stop();

	//Close the socket server
	shutdown(server_fd, SHUT_RDWR);
}

int NetworkManager::getSocketID() {
	return this->connectedSocket;
}

int NetworkManager::processReceivedMessage(
		networkMessageStruct &receivedMessage) {

//Verify checksum
	int checksum = receivedMessage.securityMode ^ receivedMessage.messageID
			^ receivedMessage.timestampHigh ^ receivedMessage.timestampLow
			^ receivedMessage.messageType ^ receivedMessage.messageDestination
			^ receivedMessage.message ^ receivedMessage.parameter1
			^ receivedMessage.parameter2;

	if (checksum == receivedMessage.xorChecksum) {
//Parse the message into queue entry
		CommandQueueEntry entry;
		entry.commandType = 0;
		entry.command = receivedMessage.message;

		if (receivedMessage.messageDestination == 1) {
			referencequeue[0]->enqueue(entry);

		} else if (receivedMessage.messageDestination == 2) {
			referencequeue[1]->enqueue(entry);
		}
	}
}
void NetworkManager::reportNewClientConnection(
		const struct sockaddr_in &clientAddress) {

}
}
