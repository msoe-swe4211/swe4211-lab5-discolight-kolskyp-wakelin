#include "LightController.h"
#include "NetworkCommands.h"
#include <unistd.h>

using namespace std;
using namespace SWE4211RPi;

#define PRIORITY 50

LightController::LightController(int gpioOutPin, int gpioInPin,
		SWE4211RPi::CommandQueue *queue, std::string threadName,
		uint32_t period) :
		PeriodicTask(threadName, period, PRIORITY) {

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
			
			if (item.command & LIGHTPWMADJUSTMENTCMD == LIGHTPWMADJUSTMENTCMD) {
				// Update PWM Cycle
				this->setTaskPeriod(item.command & 0x000000FF);
				
			} else if (item.command & LIGHTONCMD == LIGHTONCMD) {
				// Light on
				this->light->setValue(GPIO::GPIO_LOW);
				
			} else if (item.command & LIGHTOFFCMD == LIGHTOFFCMD) {
				// Light off
				this->light->setValue(GPIO::GPIO_HIGH);
			}
		}

		//Check the button
		if (this->pushbutton->getValue() == GPIO::GPIO_LOW) {
			this->light->setValue(GPIO::GPIO_LOW);
		}
	}
}

