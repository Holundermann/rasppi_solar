/*
 * InputDevice.cpp
 *
 *  Created on: Nov 30, 2012
 *      Author: clemens
 */

#include "InputDevice.h"
#include <iostream>

InputDevice::InputDevice(std::string name, int gpio_pin, Gpio* gpio) :
               Device(name, gpio_pin, gpio)
{
}

InputDevice::~InputDevice()
{
}

void InputDevice::execute()
{
  if(gpio_->isHigh(gpio_pin_))
  {
    // timer einbauen, errechnet stromleistung und speichert sie in current_usage_
  }
}

