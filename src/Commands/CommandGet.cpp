/*
 * CommandGet.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: clemens
 */

#include "CommandGet.h"
#include "../Interpreter.h"
#include "../Device.h"

#include "sstream"

CommandGet::CommandGet(Interpreter* interpreter) : Command(interpreter)
{
  name_ = "get";
}

CommandGet::~CommandGet()
{}

string CommandGet::inttoString(int a)
{
  std::stringstream out;
  out << a;
  return out.str();
}

bool CommandGet::execute()
{
  Device* device;
  if((interpreter_->operandStack_.size() > 1) &&
      (device = interpreter_->getDevice(interpreter_->operandStack_.back())))
  {
    if(!check() && !interpreter_->operandStack_.back().compare("thresh"))
    {
      if (check())
      {
        interpreter_->setFeedback(inttoString(device->getThreshold()));
        std::clog << inttoString(device->getThreshold()) << endl;
      } else return false;
    }
    else if (!interpreter_->operandStack_.back().compare("state"))
    {
      if(check())
      {
        interpreter_->setFeedback(device->getState());
        std::clog << "Current State is: " << device->getState() << endl;
      } else return false;
    }
    else return false;
    return true;
  }
  return false;
}

