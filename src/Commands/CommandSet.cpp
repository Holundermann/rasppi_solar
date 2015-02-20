/*
 * CommandSet.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: clemens
 */

#include "CommandSet.h"
#include "../Interpreter.h"

CommandSet::CommandSet(Interpreter* interpreter) : Command(interpreter)
{
  name_ = "set";
}

CommandSet::~CommandSet()
{
}

template<class T>

static T fromString(const std::string& s)
{
  std::istringstream stream (s);
  T t;
  stream >> t;
  return t;
}

bool CommandSet::isZero(string a)
{
  size_t pos = a.find_first_not_of("0", 0);
  if (pos != string::npos && a.at(pos) == '.')
  {
    if (a.find_first_not_of("0", pos + 1) == string::npos)
      return true;
    else
      return false;
  }
  else if (pos == string::npos)
    return true;
  return false;
}

bool CommandSet::execute()
{
  Device* device;
  if((interpreter_->operandStack_.size() > 1) &&
      (device = interpreter_->getDevice(interpreter_->operandStack_.back())))
  {
    interpreter_->operandStack_.pop_back();
    if(!interpreter_->operandStack_.back().compare("on"))
    {
      if (check())
      {
        device->setOn();
      }
      else return false;
    }
    else if(!interpreter_->operandStack_.back().compare("off"))
    {
      if (check())
      {
        device->setOff();
      }
      else return false;
    }
    else if(!interpreter_->operandStack_.back().compare("auto"))
    {
      if (check())
      {
        device->setAuto();
      }
      else return false;
    }
    else if((interpreter_->operandStack_.size() == 2) &&
              !interpreter_->operandStack_.back().compare("thresh"))
    {
      if (!check())
      {
        int x = 0;
        x = fromString<int>(interpreter_->operandStack_.back());
        if (!x)
        {
          if(isZero(interpreter_->operandStack_.back()))
          {
            device->setThreshold(x);
            interpreter_->operandStack_.pop_back();
          }
          else return false;
        }
        else
        {
          if (check())
            device->setThreshold(x);
          else return false;
        }
      }
      else return false;
    }
    return true;
  }
  return false;
}

