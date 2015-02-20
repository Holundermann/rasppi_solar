/*
 * DeviceFussbodenheizung.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include "DeviceStd.h"
#include <iostream>

DeviceStd::DeviceStd(std::string name, int gpio_pin, Gpio* gpio)
                          : Device(name, gpio_pin, gpio)
{
  threshold_ = 1000;
  gpio_->outLow(gpio_pin_);
}

DeviceStd::~DeviceStd()
{
  if(is_on_)
    gpio_->outLow(gpio_pin_);
}

void DeviceStd::switchOff()
{
  std::clog << name_ << ": Switching off: " << aktuell_ << "W, "
            << threshold_ << " threshold" << std::endl;
  gpio_->outLow(gpio_pin_);
}

void DeviceStd::switchOn()
{
  std::clog << name_ << ": Switching on: " << aktuell_ << "W, "
            << threshold_ << " threshold" << std::endl;
  gpio_->outHigh(gpio_pin_);
}

