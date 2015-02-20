/*
 * InputDevice.h
 *
 *  Created on: Nov 30, 2012
 *      Author: clemens
 */

#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_

#include <string>
#include "Gpio.h"
#include "Device.h"

class InputDevice : public Device
{
  private:
    float current_usage_;
  public:
    InputDevice(std::string name, int gpio_pin, Gpio* gpio_);
    virtual ~InputDevice();

    void execute();
};

#endif /* INPUTDEVICE_H_ */
