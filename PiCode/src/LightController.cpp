#include <"LightController.h">

using namespace SWE4211Rpi;

LightController::LightController(int gpioOutPin, int gpioInPin,
		SWE4211RPi::CommandQueue *queue, std::string threadName,
		uint32_t period) {

		this->light = new GPIO(gpioOutPin,GPIO::VALUE_LOW);
		this->pushbutton = new GPIO(gpioInPin, GPIO::VALUE_LOW);
		this->referenceQueue = queue;


}

LightController::~LightController() {
		delete light;
		delete pushbutton;
}

void LightController::taskMethod() {

}
