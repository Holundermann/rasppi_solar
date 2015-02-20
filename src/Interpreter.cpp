/*
 * Interpreter.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: clemens
 */

#include "Interpreter.h"
#include "Server/Session.h"

#include "Commands/CommandSet.h"
#include "Commands/CommandGet.h"
#include "FactoryCommand.h"

#include <vector>
#include <iostream>

Interpreter::Interpreter(vector<Device*> d)
{
  devices_ = d;
  session_ = NULL;

  vector<Command*> commands;

  f_commands_ = new FactoryCommand(this);
  commands = f_commands_->getCommands();
  registerCommands(commands);
}

Interpreter::~Interpreter()
{}

void Interpreter::registerCommands(vector<Command*> commands)
{
  commands_ = commands;
  for(size_t i = 0; i < commands.size(); i++)
  {
    commands_map_[i] = commands.at(i)->getName();
  }

}

Device* Interpreter::getDevice(string name)
{
  for(vector<Device*>::iterator it = devices_.begin(); it != devices_.end(); it++)
  {
    if(!(*it)->getName().compare(name))
      return (*it);
  }
  return NULL;
}

void Interpreter::clearOperands()
{
  operandStack_.clear();
}

bool Interpreter::execute(vector<Token*>::iterator prgBegin, vector<Token*>::iterator prgEnd)
{
  for(vector<Token*>::iterator it = prgBegin; it != prgEnd; it++)
  {
    if ((*it)->type_ == VALUE)
    {
      operandStack_.push_back((*it)->value_s_);
      delete (*it);
    }
    else
    {
      if(commands_[(*it)->opcode_]->execute())
      {
        return true;
      }
    }
  }
  clearOperands();
  return false;
}

void Interpreter::setFeedback(string f)
{
  session_->setFeedback(f);
}
