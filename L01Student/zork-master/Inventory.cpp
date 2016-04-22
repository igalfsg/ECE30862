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


void Inventory::printItems() const
{
	//code this shit
}


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

bool Inventory::hasa(const string& itemStr) const
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


bool Inventory::isFull() const
{
  return items.size() >= MAX_ITEMS;
}
