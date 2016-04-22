#ifndef _INVENTORY_H
#define _INVENTORY_H

#include <list>
using std::list;

#include "Exceptions.h"

#include "Item.h"

class Inventory
{
 public:
  Inventory(string name, string description, string status);
  string getName();
  string getDescription();
  string getStatus();
  Item drop(const string &itemToRemove) throw (MissingItem);
  void printItems() const;
  bool put(const Item& item);
  bool hasa( const string& itemStr) const;
  bool isFull() const;

 private:
  const unsigned int MAX_ITEMS;
  list<Item> items;
  string name;
  string description;
  string status;
};

#endif

