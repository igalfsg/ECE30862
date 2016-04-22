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
  // virtual string toString() const;
  void printItems() const;
  bool put(const Item& item); //insert
  Item drop(const string &itemToRemove) throw (MissingItem);
  // string examine( const string &itemString ) const throw (MissingItem);
  bool hasA( const string& itemStr) const;
  bool isFull() const;

 private:
  const unsigned int MAX_ITEMS;
  list<Item> items;
  string name;
  string description;
  string status;
};

#endif

