/*
 * CommandGet.h
 *
 *  Created on: Oct 14, 2012
 *      Author: clemens
 */

#ifndef COMMANDGET_H_
#define COMMANDGET_H_

#include "Command.h"

class CommandGet : public Command
{
  private:
    string inttoString(int a);
  public:
    CommandGet(Interpreter* interpreter);
    virtual ~CommandGet();

    bool execute();
};

#endif /* COMMANDGET_H_ */
