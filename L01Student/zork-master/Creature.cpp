#include <iostream>
#include <string>
#include <vector>
#include "Creature.h"
#include "Attack.h"

Creature::Creature()
{
 
}

void Creature::addAction(string newAction)
{
  actions.push_back(newAction);
}
void Creature::setName(string newName)
{
  this->name = newName;
}
void Creature::setDescription(string newDescription)
{
  this->description = newDescription;
}
void Creature::setStatus(string newStatus)
{
  this->status = newStatus;
}
void Creature::setVulnerability(string newVulnerability)
{
  vulnerability = newVulnerability;
}
void Creature::setAttack(Attack* newAttack)
{
	this->attack = newAttack;
}
void Creature::addTriggers(Triggers* newTriggers){
  (this->triggers).push_back(newTriggers);
}
void Creature::setConditionSatisfy(string newCondition){
  this->satisfy = newCondition;
}

vector<string> Creature::getActions()
{
  return actions;
}
string Creature::getName()
{
  return name;
}
string Creature::getDescription() 
{
  return description;
}
string Creature::getStatus()
  {
    return status;
  }
string Creature::getVulnerability(){
return vulnerability;
}
Attack* Creature::getAttack()
{
return attack;
}
vector<Triggers*> Creature::getTriggers(){
  return triggers;
}
string Creature::getConditionSatisfy(){
  return satisfy;
}




