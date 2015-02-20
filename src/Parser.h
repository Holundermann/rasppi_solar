/*
 * parsePage.h
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "Token.h"
#include "Device.h"

#ifndef PARSEPAGE_H_
#define PARSEPAGE_H_

using namespace std;

class Parser
{
  private:
    string content_;
    size_t findString(string find, size_t pos);
    vector<Device*> devices_;

    bool isZero(string a);

  public:
    Parser();
    virtual ~Parser();

    vector<Token*> getTokens(vector<string>& params, map<int,string> operator_map);
    vector<string> getParams(string a);

    int getAktuell();
    int getGesamt();
    int getValue(string value);

    void setContent(string content){content_ = content;};
    void setDevices(vector<Device*> devices){devices_ = devices;};
};



#endif /* PARSEPAGE_H_ */
