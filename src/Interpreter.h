  /*
 * Interpreter.h
 *
 *  Created on: Sep 29, 2012
 *      Author: clemens
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "string.h"
#include <vector>
#include <map>

#include "Parser.h"
#include "Device.h"
#include "Token.h"
#include "Commands/Command.h"

using namespace std;

class Session;

#include <vector>
#include <string>

#include "FactoryCommand.h"

class FactoryCommand;

class Interpreter
{
  private:
    Session* session_;

    vector<Device*> devices_;
    vector<Command*> commands_;
    map<int,string> commands_map_;
    FactoryCommand* f_commands_;
    bool switch_;
    bool thresh_;
    int switcher_;

    void clearOperands();

  public:
    vector<string> operandStack_;

    Interpreter(vector<Device*> device);
    virtual ~Interpreter();

    void registerCommands(vector<Command*> commands);

    bool execute(vector<Token*>::iterator prgBegin, vector<Token*>::iterator prgEnd);
    void setSession(Session* s) {session_ = s;};


    map<int,string>   getCommandsMap() {return commands_map_;};
    bool              getSwitch(){return switch_;};
    bool              getSwitcher(){return switcher_;};
    bool              getThresh(){return thresh_;};
    Device*           getDevice(string name);
    vector<Device*>   getDevices(){return devices_;};

    void             setFeedback(string f);
};

#endif /* INTERPRETER_H_ */
