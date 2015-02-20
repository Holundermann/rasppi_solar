/*
 * ServerCommand.cpp
 *
 *  Created on: Oct 5, 2012
 *      Author: clemens
 */

#include "Command.h"
#include "../Interpreter.h"

Command::Command(Interpreter* interpreter) :
                  interpreter_(interpreter)
{
}

Command::~Command()
{
  // TODO Auto-generated destructor stub
}

bool Command::check()
{
  interpreter_->operandStack_.pop_back();
  return interpreter_->operandStack_.empty();
}

