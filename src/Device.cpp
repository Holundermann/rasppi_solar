/*
 * DeviceCommand.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include "Device.h"

#include <iostream>

Device::Device(std::string name, int gpio_pin, Gpio* gpio)
{
  gpio_ = gpio;
  name_ = name;
  gpio_pin_ = gpio_pin;
  state_ = AUTO_DEVICE;
  is_on_ = false;
  aktuell_ = 0;
}

Device::~Device()
{
  // TODO Auto-generated destructor stub
}

void Device::execute()
{
  if(state_ == AUTO_DEVICE)
  {
    if(aktuell_ >= threshold_ && !is_on_)
    {
      std::clog << "executing on" << std::endl;
      switchOn();
      is_on_ = true;
    }
    else if (aktuell_ < threshold_ && is_on_)
    {
      std::clog << "executing off" << std::endl;
      switchOff();
      is_on_ = false;
    }
  }
  else if(state_ == ON && !is_on_)
  {
    {
      std::clog << "executing on" << std::endl;
      switchOn();
      is_on_ = true;
    }
  }
  else if (state_ == OFF && is_on_)
  {
    std::clog << "executing off" << std::endl;
    switchOff();
    is_on_ = false;
  }
}

void Device::setOn()
{
  state_ = ON;
  execute();
}

void Device::setOff()
{
  state_ = OFF;
  execute();
}

void Device::setAuto()
{
  state_ = AUTO_DEVICE;
  execute();
}

std::string Device::getState()
{
  switch(state_)
  {
    case ON:
      return "on";
    case OFF:
      return "off";
    case AUTO_DEVICE:
      return "auto";
    default:
      return "unknown";
  }
}
