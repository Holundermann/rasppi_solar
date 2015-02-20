/*
 * Controller.h
 *
 *  Created on: Sep 15, 2012
 *      Author: clemens
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>

#include "Device.h"
#include "Gpio.h"
#include "string.h"

using namespace std;

class Controller
{
  private:
    int aktuell_;
    vector<Device*> output_devices_;
    vector<Device*> input_devices_;
    Gpio* gpio_;

  public:
    Controller();
    virtual ~Controller();
    void run();

    void setAktuell(int a) {aktuell_ = a;};
    bool setDeviceOn(string name);
    bool setDeviceOff(string name);

    vector<Device*> getDevices() {return output_devices_;};
};

#endif /* CONTROLLER_H_ */
