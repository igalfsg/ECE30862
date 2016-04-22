
#ifndef _ROOM_H
#define _ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Creature.h"
#include "Triggers.h"
#include "Container.h"


using std::vector;
using std::string;

using namespace std;

class Room {
typedef struct _border
{
  string direction;
  string name;
}Border;

public:
  Room()
  {
    name = "default";
    description = "default";
    status = "default";
    type = "default";
    bordersIndex = 0;
  };
  
  string getName();
  void setName(string newName);
  
  string getDescription();
  void setDescription(string newDescription);
  
  string getStatus();
  void setStatus(string newStatus);
  
  string getType();
  void setType(string newType);
 
  void addBorder(string newDirection, string newName);
  string getBorderName(string);
  vector <Border*> getBorders();

  vector<Item*> getItems();
  void addItem(Item* newItem);

  vector<Container*> getContainers();
  void addContainer(Container*);

  vector<Creature*> getCreatures();
  void addCreature(Creature*);

  vector <Triggers*> getTriggers();
  void addTriggers(Triggers*);

  void deleteItem(string);


  // void removeItem(string itemName);
  // Room* const getNextRoom(const string &dirName);
  //string getDescription();
  /*
  string getName()
  {
  return name;
  };
  string getType();
  */
private:
  vector<Item*> items;
  vector<Creature*> creatures;
  vector<Triggers*> triggers;
  vector<Container*> containers;
  vector<Border*> borders;
  string description;
  string name;
  string type;
  string status;
  int bordersIndex;
};
#endif


