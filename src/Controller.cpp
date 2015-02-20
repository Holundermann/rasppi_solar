/*
 * Controller.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: clemens
 */

#include "Controller.h"

#include "DeviceStd.h"

#include <iostream>
#include "bcm2835.h"

Controller::Controller()
{
  gpio_ = new Gpio();
  // bekommt als Argument den Namen, den gpio Pin sowie eine Referenz auf den
  // initialisierten gpio Port
  gpio_->setGpioOut(RPI_GPIO_P1_11);
  output_devices_.push_back(new DeviceStd("fuss", RPI_GPIO_P1_11, gpio_));
  //gpio_->setGpioIn(RPI_GPIO_P1_03);
}

Controller::~Controller()
{
  for (vector<Device*>::iterator it = output_devices_.begin();it != output_devices_.end(); it++)
  {
    delete (*it);
  }
}

void Controller::run()
{
  for (vector<Device*>::iterator it = output_devices_.begin();it != output_devices_.end(); it++)
  {
    (*it)->setAktuell(aktuell_);
    (*it)->execute();
  }
}

bool Controller::setDeviceOn(string name)
{
  for (vector<Device*>::iterator it = output_devices_.begin();it != output_devices_.end(); it++)
  {
    if((*it)->getName() == name)
    {
      (*it)->switchOn();
      return true;
    }
  }
  return false;
}

bool Controller::setDeviceOff(string name)
{
  for (vector<Device*>::iterator it = output_devices_.begin();it != output_devices_.end(); it++)
  {
    if((*it)->getName() == name)
    {
      (*it)->switchOff();
      return true;
    }
  }
  return false;
}

