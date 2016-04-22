#include "Item.h"

Item::Item()
{
  name = "default";
  description = "default";
  status = "default";
  writing = "default";
}

void Item::addAction(string newAction)
{
  actions.push_back(newAction);
}

vector <string> Item::getActions()
{
  return actions;
}

void Item::setName(string newName)
{
name = newName;
}

void Item::setDescription(string newDescription)
{
description = newDescription;
}

void Item::setStatus(string newStatus)
{
status = newStatus;
}

void Item::setWriting(string newWriting )
{
writing = newWriting;
}

string Item::getName()
  {
    return name;
  }
  
string Item::getDescription() 
  {
    return description;
  }
string Item::getStatus()
  {
    return status;
  }

string Item::getWriting()
{
  return writing;
}

string Item::getIsOn()
{
  return on;
} 

void Item::setIsOn(string newOn)
{
  this->on = newOn;
}

void Item::turnOn(){
  onFlag = 1;
}

void Item::turnOff(){
  onFlag = 0;
}

vector <Triggers*> Item::getTriggers()
{
  return triggers;
}

void Item::addTriggers(Triggers* newTriggers){
  this->triggers.push_back(newTriggers);
}

void Item::setPrint(string newPrint)
{
  print = newPrint;
}

string Item::getPrint()
{
  return print;
}
