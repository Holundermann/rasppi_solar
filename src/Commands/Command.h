/*
 * ServerCommand.h
 *
 *  Created on: Oct 5, 2012
 *      Author: clemens
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>

using namespace std;

class Interpreter;
class Command
{
  protected:
    Interpreter* interpreter_;
    string name_;
    bool check();

  private:
    Command(const Command& orig);


  public:
    Command(Interpreter* interpreter);
    virtual ~Command();

    string getName(){return name_;};

    virtual bool execute() = 0;
};

#endif /* SERVERCOMMAND_H_ */
