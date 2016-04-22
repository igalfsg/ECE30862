#include "Container.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Container::Container()
{
 
}

void Container::deleteItem(string passed)
{
  for(int i = 0; i < items.size() ; i++)
    {
      if(items[i]->getName() == passed)
	{
	  items.erase(items.begin() + i);
	}
    }
}
string Container::getName()
  {
    return name;
  }

  void Container::setName(string newName)
  {
    name = newName;
  }
  

string Container::getDescription() 
  {
    return description;
  }

  void Container::setDescription(string newDescription)
  {
    this->description = newDescription;
  }

string Container::getStatus()
  {
    return status;
  }

  void Container::setStatus(string newStatus)
  {
    status = newStatus;
  }

  string Container::getSatisfyCondition()
  {
    return condition;
  }

void Container::setSatisfyCondition(string newCondition)
{
    this->condition = newCondition;
} 

vector<Item*> Container::getItems()
{
  return items;
}

Item* Container::getItem(string target)
{
  int i = 0;
  for(i = 0; i < items.size(); i++ )
    {
      if(items[i]->getName() == target)
	{
	  return items[i];
	}
    }
}

void Container::addItem(Item* newItem)
{
  items.push_back(newItem);
}


vector<Triggers*> Container::getTriggers(){
  return triggers;
}

void Container::addTriggers(Triggers* newTrigger){
  (this->triggers).push_back(newTrigger);
}

  string Container::getAccept(){
  return accept;
}

void Container::setAccept(string newAccept){
  accept = newAccept;
}

void Container::addAction(string newAction)
{
  actions.push_back(newAction);
}

vector<string> Container::getActions()
{
  return actions;
}



