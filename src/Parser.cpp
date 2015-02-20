/*
 *  Parser.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include "Parser.h"


Parser::Parser()
{
}

Parser::~Parser()
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

size_t Parser::findString(string find, size_t pos)
{
  return content_.find(find, pos);
}

int Parser::getValue(string value)
{
  size_t pos = findString(value, 0);
  for (int i = 0; i < 2; i++)
  {
    pos = findString(">", pos + 1);
  }
  // to easy, first find the string, then from the string positon 2 times  ">"
  // +3 to get to the wanted value
  string gesamt = content_.substr(pos + 3, 6);
  if(gesamt.find('x') != string::npos)
    return 0;

  return fromString<int>(gesamt);
}

int Parser::getGesamt()
{
  return getValue("Gesamtenergie");
}

int Parser::getAktuell()
{
  return getValue("aktuell");
}

bool Parser::isZero(string a)
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

vector<string> Parser::getParams(string input)
{
  size_t pos = 0;
  vector<string> param;
  while(string::npos != (pos = input.find_first_of(' ', 0)))
  {
    if(pos >= 1)
    {
      param.push_back(input.substr(0, pos));
    }
    input.erase(0, pos+1);
  }
  if(input.size())
  {
    param.push_back(input.substr(0, input.find_first_of('\r', 0)));
  }
  return param;
}

vector<Token*> Parser::getTokens(vector<string>& params, map<int,string> operator_map)
{
  vector<Token*> tokens;

  while(params.size() > 1)
  {
    Token* tmp_token = new Token();
    tmp_token->value_s_ = params.back();
    tmp_token->type_ = VALUE;
    tokens.push_back(tmp_token);
    params.pop_back();
  }
  for(unsigned int j = 0; j < operator_map.size(); j++)
  {
    if(!operator_map[j].compare((params.back())))
    {
      Token* tmp_token = new Token();
      tmp_token->type_ = OPERANT;
      tmp_token->opcode_ = j;
      tokens.push_back(tmp_token);
      params.pop_back();
      break;
    }
  }
  if(!params.size())
    return tokens;

  // Program termination - wrong argument!
  for(vector<Token*>::iterator it = tokens.begin(); it != tokens.end(); it++)
  {
    delete *it;
    tokens.erase(it);
    it--;
  }
  return tokens;
}
