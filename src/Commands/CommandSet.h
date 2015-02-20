/*
 * CommandSet.h
 *
 *  Created on: Oct 10, 2012
 *      Author: clemens
 */

#ifndef COMMANDSET_H_
#define COMMANDSET_H_

#include "Command.h"

class CommandSet : public Command
{
  private:
    bool isZero(string a);
  public:
    CommandSet(Interpreter* interpreter);
    virtual ~CommandSet();

    bool execute();
};

#endif /* COMMANDSET_H_ */
