/*
 * main.cpp

 *
 *  Created on: Mar 3, 2015
 *      Author: student
 */
#include <iostream>
#include "LightController.h"
#include "NetworkManager.h"

using namespace std;
using namespace SWE4211RPi;

/**
 * This is the main program.  It will instantiate an instance of a Queue, a Network Manager, and a Light Controller.  Start will then be called on each of those classes
 * and the priorities will be set.
 */
int main(int argc, char* argv[]) {
	CommandQueue *myQueue[2];
	myQueue[0] = new CommandQueue();
	myQueue[1] = new CommandQueue();


	/**
	 * Instantiate a network manager and a pair of light controllers.  The light controller should execute every 50 ms.
	 */
	NetworkManager nm(9090, myQueue, "Network Thread");
	LightController lc1(13, 16, myQueue[0], "Light Controller Thread 1", 10000);
	LightController lc2(21, 19, myQueue[1], "Light Controller Thread 2", 10000);

	// Start each of the two threads up.
	nm.start();
	lc1.start();
	lc2.start();


	// Wait for the user to press a key.
	char msg[1024];
	cin >> msg;
	cout << msg;

	// Shutdown the network managers.
	nm.stop();
	lc1.stop();
	lc2.stop();
	
	// Enqueue two zero messages in a row..
	CommandQueueEntry nothing = {0,0};


	myQueue[0]->enqueue(nothing);
	myQueue[1]->enqueue(nothing);
	
	// Wait for the threads to terminate.
	lc1.waitForShutdown();
	lc2.waitForShutdown();
	nm.waitForShutdown();


	/**
	 * Delete the allocated queues.
	 */
	delete myQueue[0];
	delete myQueue[1];
}



