/*
 * Token.h
 *
 *  Created on: Oct 5, 2012
 *      Author: clemens
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include "string"

const int VALUE = 0;
const int OPERANT = 1;
const int DEVICE = 2;
const int SWITCH = 3;
const int THRESH = 4;

const int AUTO = 20;

using namespace std;

class Token
{
  public:
    Token();
    virtual ~Token();

    short type_;
    string value_s_;
    short opcode_;
};

#endif /* TOKEN_H_ */
