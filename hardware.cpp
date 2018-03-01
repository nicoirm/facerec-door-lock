// Grayson Pike, 2018

#include "hardware.hpp"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string.h>

/*
	http://answers.opencv.org/question/29957/highguivideocapture-buffer-introducing-lag/post-id-38217/
	Hack to clear capture buffer
	Setting buffer size to 0 is not supported with Raspberry Pi Camera
	Clearing the buffer is also not supported with the Raspberry Pi Camera
*/
void flush_capture_buffer(cv::VideoCapture& capture) {

	// Begin measuring time
	std::clock_t start_time;
	double duration;

	// Frame buffer holds five frames, grab and dispose of them all
	for(int i = 0; i < 10; i++) {
		start_time = std::clock();
		capture.grab();
		duration = (std::clock() - start_time) / (double)CLOCKS_PER_SEC;
		i++;
	}

}

/*
	Returns an instance of the default camera as a VideoCapture object
	or exits on failure.

	Open the default camera
    If this fails, make sure you've run
    sudo modprobe bcm2835-v4l2
    ^ PLACE THIS IN YOUR ~/.bash_profile
    which creates a device for the camera at /dev/video0
*/
cv::VideoCapture get_camera() {

	cv::VideoCapture camera(0);

	if (!camera.isOpened()) {
        std::cerr << "Failed to open the camera. Have you run 'sudo modprobe bcm2835-v4l2'?" << std::endl;
        return 1;
    }

    return camera;
}


/*
	Create a GPIO object to control a GPIO pin
	Pin is automatically exported on creation, and unexported on deletion
*/
GPIO::GPIO(std::string pin, std::string dir) {

	this->pin = pin;
	this->export_pin();
	this->set_dir(dir);

}



/*
	When deleting a GPIO object, we unexport the pin
*/
GPIO::~GPIO() {

	this->unexport_pin();

}


/*
	Export the pin with /sys/class/gpio/export
	This must be done before using the pin
*/
void GPIO::export_pin() {

	std::ofstream exportgpio("/sys/class/gpio/export");
	if(exportgpio < 0) {
		std::cerr << "Error: Failed to export GPIO" << this->pin << "." << std::endl;
		exit(-1);
	}

	// Write pin to output
	exportgpio << this->pin;

	exportgpio.close();

}


/*
	Unexport the pin with /sys/class/gpio/unexport
*/
void GPIO::unexport_pin() {

	std::ofstream unexportgpio("/sys/class/gpio/unexport");
	if(unexportgpio < 0) {
		std::cerr << "Error: Failed to unexport GPIO" << this->pin << "." << std::endl;
		exit(-1);
	}

	// Write pin to output
	unexportgpio << this->pin;

	unexportgpio.close();

}


/*
	Set the direction of the pin (in or out)
*/
void GPIO::set_dir(std::string dir) {

	std::string set_path ="/sys/class/gpio/gpio" + this->pin + "/direction";
	std::ofstream setgpiodir(set_path.c_str());
	if(setgpiodir < 0) {
		std::cerr << "Error: Failed to set GPIO" << this->pin << " direction." << std::endl;
		exit(-1);
	}

	setgpiodir << dir;

	setgpiodir.close();

}


/*
	Set the value of the pin (1 or 0)
*/
void GPIO::set_value(std::string value) {

	std::string set_value ="/sys/class/gpio/gpio" + this->pin + "/value";
	std::ofstream setgpiovalue(set_path.c_str());
	if(setgpiodir < 0) {
		std::cerr << "Error: Failed to set GPIO" << this->pin << " value." << std::endl;
		exit(-1);
	}

	setgpiovalue << value;

	setgpiovalue.close();

}


/*
	Read the value from the pin (0 for no voltage and 1 for 3.3v)
*/
int GPIO::read_value() {

	std::string get_value ="/sys/class/gpio/gpio" + this->pin + "/value";
	std::ofstream getgpiovalue(set_path.c_str());
	if(getgpiovalue < 0) {
		std::cerr << "Error: Failed to get GPIO" << this->pin << " value." << std::endl;
		exit(-1);
	}

	string &value;
	getgpiovalue >> value;

	getgpiovalue.close();

	return strcmp(value, "0") ? 0 : 1;

}