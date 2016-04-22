#include "Triggers.h"
#include <iostream>
#include <string>
using namespace std;
void Triggers::setType(string newType){
  this->type=newType;
}
void Triggers::setCondition(string object, string status, string has, string owner) {
  condition = new Conditions();
  condition->status = status;
  condition->has = has;
  condition->owner = owner;
  condition->object=object;
}
void Triggers::addAction(string newAction){
  (this->actions).push_back(newAction);
}
void Triggers::setPrint(string newPrint){
  this->print = newPrint;
}
void Triggers::setCommand(string newCommand){
  this->command = newCommand;
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
string Triggers::getObject() 
{
  return condition->object;
}
string Triggers::getPrint(){
  return print;
}
string Triggers::getCommand(){
  return command;
}
string Triggers::getType(){
  return type;
}
Conditions* Triggers::getCondition() {
  return condition;
}
vector<string> Triggers::getActions() {
  return actions;
}
