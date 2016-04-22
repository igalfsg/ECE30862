#include "Triggers.h"
#include <iostream>
#include <string>
using namespace std;

string Triggers::getType(){
  return type;
}
void Triggers::setType(string newType){
  this->type=newType;
}
Conditions* Triggers::getCondition() {
  return condition;
}
void Triggers::setCondition(string object, string status, string has, string owner) {
  condition = new Conditions();
  condition->status = status;
  condition->has = has;
  condition->owner = owner;
  condition->object=object;
}
vector<string> Triggers::getActions() {
  return actions;
}
void Triggers::addAction(string newAction){
  (this->actions).push_back(newAction);
}
string Triggers::getCommand(){
  return command;
}
void Triggers::setCommand(string newCommand){
  this->command = newCommand;
}
string Triggers::getPrint(){
  return print;
}

void Triggers::setPrint(string newPrint){
  this->print = newPrint;
}

string Triggers::getObject() 
{
  return condition->object;
}

string Triggers::getHas () {
  return condition->has;
}

string Triggers::getOwner() {
  return condition->owner;
}

string Triggers::getStatus() {
  return condition->status;
}
