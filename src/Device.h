/*
 * DeviceCommand.h
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <string>

#include "Gpio.h"

const char OFF = 0;
const char ON = 1;
const char AUTO_DEVICE = 2;

class Device
{
  protected:
    char state_;
    bool is_on_;
    int gpio_pin_;
    int threshold_;
    int aktuell_;
    std::string name_;
    Gpio* gpio_;

  public:
    Device(std::string name, int gpio_pin_, Gpio* gpio_);
    virtual ~Device();

    void execute();

    virtual void switchOn() = 0;
    virtual void switchOff() = 0;

    std::string getState();
    int getGpioPin(){return gpio_pin_;};
    int getThreshold() {return threshold_;};
    std::string getName() {return name_;};

    void setAktuell(int a) {aktuell_ = a;};
    void setThreshold(int t) {threshold_ = t; execute();};
    void setGpioPin(int gpio_pin){gpio_pin_ = gpio_pin;};
    void setOn();
    void setOff();
    void setAuto();
};

#endif /* DEVICECOMMAND_H_ */
