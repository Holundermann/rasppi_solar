/*
 * DeviceFussbodenheizung.h
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#ifndef DEVICESTD_H_
#define DEVICESTD_H_

#include "Device.h"

class DeviceStd : public Device
{
  public:
    DeviceStd(std::string name, int gpio_pin, Gpio* gpio);
    virtual ~DeviceStd();

    void execute();

    void switchOn();
    void switchOff();
};

#endif /* DEVICEFUSSBODENHEIZUNG_H_ */
