/*
 * gpio_.h
 *
 *  Created on: Sep 15, 2012
 *      Author: clemens
 *      neu schreiben: umstellung auf bcm2835.h!!!!
 */

#ifndef gpio_H_
#define gpio_H_

class Gpio
{
  public:
    Gpio();
    virtual ~Gpio();

    bool setGpioOut(int pin);
    bool setGpioIn(int pin);

    void outHigh(int pin);
    void outLow(int pin);

    bool isHigh(int pin);
};

#endif /* gpio__H_ */
