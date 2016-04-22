#include "Inventory.h"

Inventory::Inventory(string name, string decription,string status)
 :MAX_ITEMS(10)
{
  this->name = name;
  this -> description = description;
  this ->status = status;
}

string Inventory::getName()
  {
    return name;
  }
  
string Inventory::getDescription() 
  {
    return description;
  }
string Inventory::getStatus()
  {
    return status;
  }

/*
This method returns the list of the items and prints them
 */
void Inventory::printItems() const
{
  if(items.empty())
    {
      return "You have no items.";
    }
  else
    {
      string ret = "You have: "; 
    
   list<Item>::const_iterator itr;
   for ( itr = items.begin(); itr != items.end(); ++itr )
     {
       ret += "\n\ta " + itr->toString();
       cout << ret;
     }
   //return ret;
}
}

/*
This method checks to see if the inventory has the item 
 */
bool Inventory::hasA(const string& itemStr) const
{
  list<Item>::const_iterator itr;
  for (itr = items.begin(); (itr != items.end()) && (itr->toString()!= itemStr); ++itr)
    {

    }
  if ( itr != items.end() )
    {
      return true;
    }
  return false;
}

/*
This method adds an item to the inventory if list not full
 */
bool Inventory::put(const Item& item)
{
  if ( !isFull() )
    {
      items.push_back(item);
      return true;
    }
  else
    {
      return false;
    }
}

/*
This method drops the item from the inventory
 */
Item Inventory::drop(const string &nameToRemove) throw (MissingItem)
{
  list<Item>::iterator itr;
  for ( itr = items.begin(); (itr != items.end())&&(itr->getName() != nameToRemove); ++itr )
    {
      ; 
    }
 
  if ( itr != items.end() )
    {
      Item temp = *itr;
    
      items.erase( itr );
      return temp;
    }
  else
    {
      throw MissingItem();
    }
}

/*
This method checks to see if the inventory is full
 */
bool Inventory::isFull() const
{
  return items.size() >= MAX_ITEMS;
}
