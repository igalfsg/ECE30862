#include "/home/shay/a/heath7/zork1/Room.h"
//#include "/home/shay/b/dpahuja/Desktop/ece 308-62/zork/Room.h"
/*
Room::Room()
{
name = "default";
description = "default";
status = "default";
type = "default";
} 
*/
string Room::getName()
{
  return name;
}

string Room::getDescription()
{
  return description;
}

string Room::getStatus()
{
  return status;
}

string Room::getType()
{
  return type;
}

void Room::setName(string newName)
{
name = newName;
}

void Room::setDescription(string newDescription)
{
description = newDescription;
}

void Room::setStatus(string newStatus)
{
status = newStatus;
}

void Room::setType(string newType)
{
type = newType;
}

void Room::addBorder(string dir, string borderRoom)
{
  Border* newBorder = new Border();
  if(dir == "north"){
    dir = "n";
    }
  if(dir == "south"){
    dir = "s";}
  if(dir == "east"){
    dir = "e";
  }
  if(dir == "west")
    {
      dir = "w";
    }


 newBorder->direction = dir;
 newBorder->name = borderRoom;
 borders.push_back(newBorder);
 // cout << borders.size() << endl;
}

void Room::addItem(Item* newItem)
{
items.push_back(newItem);
}

vector<Item*> Room::getItems()
{
  return items;
}

void Room::deleteItem(string passed)
{
  for(int i = 0; i < items.size(); i++)
    {
      if(items[i]->getName() == passed)
	{
	  items.erase(items.begin() + i);
	  break;
	}
    }
 
}

string Room::getBorderName(string dir){
  string temp = "nonexistant";
  for(int i = 0; i < borders.size(); i++)
  {
    if(borders[i]->direction == dir)
      {
	temp = borders[i]->name;
      }
  } 
  return temp;
}


vector<Container*> Room::getContainers(){
  return containers; 

}

void Room::addContainer(Container* newContainer){
  (this->containers).push_back(newContainer);
}

vector<Creature *> Room::getCreatures(){
  return creatures;
}

void Room::addCreature(Creature* newCreature){
  (this->creatures).push_back(newCreature);
}

vector <Triggers*> Room::getTriggers()
{
  return triggers;
}

void Room::addTriggers(Triggers* newTriggers){
  (this->triggers).push_back(newTriggers);
}


/*
main()
{
Room* room1 = new Room();
room1->setName("entrance");
string tempName = room1->getName();
std::cout << tempName << std::endl;
}
*/
