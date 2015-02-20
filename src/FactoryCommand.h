/*
 * FactoryCommand.h
 *
 *  Created on: Oct 10, 2012
 *      Author: clemens
 */

#ifndef FACTORYCOMMAND_H_
#define FACTORYCOMMAND_H_

#include <vector>

#include "Commands/Command.h"
#include "Interpreter.h"

using namespace std;

class FactoryCommand
{
  private:
    vector<Command*> commands_;
    Interpreter* interpreter_;
    static FactoryCommand* instance_;
    FactoryCommand(FactoryCommand const& F);
  public:
    FactoryCommand(Interpreter* interpreter);
    virtual ~FactoryCommand();

    vector<Command*> getCommands();
};

#endif /* FACTORYCOMMAND_H_ */
