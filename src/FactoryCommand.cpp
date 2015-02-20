/*
 * FactoryCommand.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: clemens
 */

#include "FactoryCommand.h"

#include "Commands/CommandSet.h"
#include "Commands/CommandGet.h"

FactoryCommand::FactoryCommand(Interpreter* interpreter)
{
  interpreter_ = interpreter;
  commands_.push_back(new CommandSet(interpreter_));
  commands_.push_back(new CommandGet(interpreter_));
}

FactoryCommand::~FactoryCommand()
{
  for(vector<Command*>::iterator it= commands_.begin(); it != commands_.end(); it++)
  {
    delete(&it);
  }
}

vector<Command*> FactoryCommand::getCommands()
{
  return commands_;
}
