/*
 * DeviceInput.h
 *
 *  Created on: Apr 14, 2013
 *      Author: clemens
 */

#ifndef DEVICEINPUT_H_
#define DEVICEINPUT_H_


#include "Gpio.h"

class DeviceInput
{
    int gpio_pin_;
    Gpio* gpio_;

    /*
     * Pinbelegung: pin nach dem output bin für Fussbodenheizung
     *
     * x x
     * x x
     * x x
     * x x
     * x x
     * o x
     * i x
     * x x
     * ...
     * o...output pin fussbodenheizung
     * i...input pin stromzähler
    */
  public:
    DeviceInput(int gpio_pin_, Gpio* gpio_);
    virtual ~DeviceInput();
    void interrupt();
};

#endif /* DEVICEINPUT_H_ */
