#include "LightController.h"
#include <unistd.h>

using namespace std;
using namespace SWE4211RPi;

#define PRIORITY 50

LightController::LightController(int gpioOutPin, int gpioInPin,
		SWE4211RPi::CommandQueue *queue, std::string threadName,
		uint32_t period): PeriodicTask (threadName, period, PRIORITY){

	this->light = new GPIO(gpioOutPin, GPIO::GPIO_OUT);
	this->pushbutton = new GPIO(gpioInPin, GPIO::GPIO_IN);
	this->referencequeue = queue;
}

LightController::~LightController() {
	delete light;
	delete pushbutton;
}

void LightController::taskMethod() {
	while (true) {
		usleep(10);

		//Read command from the queue
		if (this->referencequeue->hasItem()) {

			auto item = referencequeue->dequeue();

			switch (item.command) {

			//Update PWM cycle
			case 0x01000000:

				break;

				//Turns on the light
			case 0x00100000:
				this->light->setValue(GPIO::GPIO_LOW);
				break;

				//Turns the light off
			case 0x00010000:
				this->light->setValue(GPIO::GPIO_HIGH);
				break;

				//Invalid command
			default:
				break;
			}
		}

		//Check the button
		if (this->pushbutton->getValue() == GPIO::GPIO_LOW) {
			this->light->setValue(GPIO::GPIO_LOW);
		}
	}
}

