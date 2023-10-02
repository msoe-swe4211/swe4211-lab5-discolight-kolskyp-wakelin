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
			int commandToRun = item.command & 0xFFFF0000;
			
			if (commandToRun == LIGHTPWMADJUSTMENTCMD) {
				// Update PWM Cycle
				int dCycle = item.command & 0x000000FF;
				if (dCycle >= 0 && dCycle <= 100){
					this->dutyCycle = dCycle;
				}
				
			} else if (commandToRun == LIGHTONCMD) {
				// Light on
				this->light->setValue(GPIO::GPIO_LOW);
				
			} else if (commandToRun == LIGHTOFFCMD) {
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

