/*
 * Gpio.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: clemens
 */

#include "Gpio.h"
#include "bcm2835.h"
#include <iostream>

Gpio::Gpio()
{
  try
  {
//    if (!bcm2835_init())
//    {
//      throw("can´t initialize gpio port");
//    }
  }
  catch (const char* c)
  {
    std::clog << c << std::endl;
  }
}

Gpio::~Gpio()
{
//  bcm2835_close();
}

bool Gpio::setGpioOut(int pin)
{
//  bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);

  return true;
}

bool Gpio::setGpioIn(int pin)
{
//  bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);

  return true;
}

void Gpio::outHigh(int pin)
{
  // Turn it on
//  bcm2835_gpio_write(pin, HIGH);
}

void Gpio::outLow(int pin)
{
  // Turn it off
//  bcm2835_gpio_write(pin, LOW);
}

bool Gpio::isHigh(int pin)
{
//  uint8_t value = bcm2835_gpio_lev(pin);
//  if(value)
//    return true;
//  return false;
  return false;
}
