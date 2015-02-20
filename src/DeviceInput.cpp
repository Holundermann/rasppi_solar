/*
 * DeviceInput.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: clemens
 */

#include "DeviceInput.h"

DeviceInput::DeviceInput( int gpio_pin, Gpio* gpio)
{
  gpio_pin_ = gpio_pin;
  gpio_ = gpio;
}

DeviceInput::~DeviceInput()
{
  // TODO Auto-generated destructor stub
}

void DeviceInput::interrupt()
{
  // do something on state high
}

