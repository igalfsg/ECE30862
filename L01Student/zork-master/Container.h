#ifndef _CONTAINER_H
#define _CONTAINER_H
#include <string>
#include <vector>

#include <list>
using std::list;

#include "Exceptions.h"
#include "Item.h"
#include "Creature.h"
#include "Triggers.h"

class Container
{
 public:
  Container();
  void setName(string);
  void setDescription(string);
  void setStatus(string);
  void setSatisfyCondition(string);
  void addItem(Item*);
  void addTriggers(Triggers*);
  void setAccept(string);
  void addAction(string newAction);
  void deleteItem(string);
  
  string getName();
  string getDescription();
  string getStatus();
  string getSatisfyCondition();
  string getAccept();
  vector<Item*> getItems(); 
  vector<Triggers*> getTriggers();
  vector<string> getActions();
  Item* getItem(string target);
  
  
 private:
  string name;
  string description;
  string status;
  string condition;
  vector<Triggers*> triggers;
  vector<Item*> items;
  string accept;
  vector <string> actions;
};

#endif
