#ifndef _CONTAINER_H
#define _CONTAINER_H
#include <string>
#include <vector>

#include <list>
using std::list;

#include "Exceptions.h"
//#include "Status.h"
#include "Item.h"
#include "Creature.h"
#include "Triggers.h"

class Container
{
 public:
  Container();
  string getName();
  void setName(string);

  string getDescription();
  void setDescription(string);

  string getStatus();
  void setStatus(string);
  
  string getSatisfyCondition();
  void setSatisfyCondition(string);

  vector<Item*> getItems(); //getItemList
  void addItem(Item*);

  Item* getItem(string target);
  void setItem(Item*);

  vector<Triggers*> getTriggers();
  void addTriggers(Triggers*);

  string getAccept();
  void setAccept(string);

  void addAction(string newAction);
  vector<string> getActions();

  void deleteItem(string);

 private:
  //const unsigned int MAX_ITEMS;
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
