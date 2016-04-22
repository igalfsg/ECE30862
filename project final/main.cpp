
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Triggers.h"
#include "Inventory.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include <string>
#include <sstream>

using std::string;
using namespace std;
using namespace rapidxml;
int ind;
bool found_exist_creature;
string tagName;
string tagName2;
string tagName3;
string tagName4;
string valName;
string valName2;
string valName3;
string valName4;
string direction;
string borderName;
vector<Room*> rooms;
vector<Item*> items;
Inventory inventory;
vector<Container*> containers;
vector<Creature*> creatures;
vector<Triggers*> triggers;

string has;
string object;
string owner;
string status;

vector <string> fixed_vector;
vector <Triggers *> temp_trigg;

Room* current_room = NULL;;

xml_node<> * head_node;
xml_node<> * name_node;
xml_node<> * sub_node;
xml_node<> * value_node;

xml_node<> * temp;

std::vector<std::string> split(const std::string &s, char delim);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

int main(int argc, char ** argv){
    if (argc != 2) {
      cout << "Enter 1 XML file name!" << endl;
      return 1;
    }
    
    
    
    file<> xmlfile(argv[1]);
    xml_document<> document;
    document.parse<0>(xmlfile.data());
    //cout << "Name of node: " << document.first_node()->name() << endl;
    xml_node<> * map = document.first_node();
    
    // Go through all header nodes (room, item, container, etc)
    for (head_node = map->first_node(); head_node != NULL; head_node = head_node->next_sibling())
    {
      tagName = head_node->name();
      valName = head_node->value();
      
      //cout << "Read head node: " << tagName << endl;
      
      if(tagName == "room")
	{
	  Room* room_read = new Room();
	  rooms.push_back(room_read);
	  
	  //cout << "Making Room..." << endl;
	  // Go through each room properties
	  for(name_node = head_node->first_node();name_node != NULL; name_node = name_node->next_sibling())
	    {
	      tagName2 = name_node->name();
	      valName2 = name_node->value();
	      
	      if(tagName2 == "name")
		{
		  room_read->setName(valName2);
		  if (valName2 == "Entrance")  
		  {
		    current_room = room_read;
		  }
		   //cout << "\tName: " << room_read->getName() << endl;
		}
	      else if(tagName2 == "description")
		{
		  room_read->setDescription(valName2);
		  //cout << "\tDescription: " << room_read->getDescription() << endl;
		}
	      else if(tagName2 == "status")
		{
		  room_read->setStatus(valName2);
		  //cout << "\tStatus: " << room_read->getStatus() << endl;
		}
	      else if(tagName2 == "type")
		{
		  room_read->setType(valName2);
		  //cout << "\tType: " << room_read->getType() << endl;
		}
	      else if(tagName2 == "border")
		{
		  //cout << "\tBorder: " << endl;
		  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node->next_sibling())
		    {
		      tagName3 = sub_node->name();
		      if(tagName3 == "direction")
			{
			  valName3 = sub_node->value();
			  direction = valName3;
			}
		      else if(tagName3 == "name")
			{
			  valName3 = sub_node->value();
			  borderName = valName3;
			}
		    }
		  room_read->addBorder(direction, borderName);
		  //cout << "\t\t" << direction << ":  " << room_read->getBorderName(direction) << endl;
		}
	      else if(tagName2 == "container")
		{
		  
		  Container * container_thingy = new Container();
		  containers.push_back(container_thingy);
		  valName2 = name_node->value();
		  container_thingy -> setName(valName2);
		  room_read -> addContainer(container_thingy);
		  //cout << "\tAdding Container: " << valName2 << endl;
		}
	      else if(tagName2 == "creature")
		{
		  Creature * creature_thingy = new Creature(); 
		  valName2 = name_node->value();
		  creature_thingy->setName(valName2);
		  creatures.push_back(creature_thingy); 
		  room_read->addCreature(creature_thingy);
		  //cout << "\tAdding Creature: " << valName2 << endl;
		}
	      else if(tagName2 == "item")
		{
		  Item * item_thingy = new Item();
		  items.push_back(item_thingy);
		  valName2 = name_node->value();
		  items.back()->setName(valName2);
		  room_read->addItem(item_thingy);
		  //cout << "\tAdding Item: " << valName2 << endl;
		}
	      else if(tagName2 == "trigger")
		{
		  Triggers * trigger_thingy = new Triggers();
		  triggers.push_back(trigger_thingy);
		  room_read->addTriggers(trigger_thingy);
		  
		  
		  //cout << "\tAdding Trigger: " << endl;
		  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node->next_sibling())
		    {
		      tagName3 = sub_node->name();
		      valName3 = sub_node->value();
		      
		      if(tagName3 == "type")
			{
			  
			  trigger_thingy->setType(valName3);
			  //cout << "\t\tType: " << trigger_thingy->getType() << endl;
			}
		      else if(tagName3 == "command")
			{
			  trigger_thingy->setCommand(valName3);
			  //cout << "\t\tCommand: " << trigger_thingy->getCommand() << endl;
			}
		      else if(tagName3 == "print")
			{
			  trigger_thingy->setPrint(valName3);
			  //cout << "\t\tPrint: " << trigger_thingy->getPrint() << endl;
			}
		      else if(tagName3 == "condition")
			{
			  //cout << "\t\tCondition: " << endl;
			  has = "";
			  owner = "";
			  status = "";
			  object = "";
			  
			  for(value_node = sub_node->first_node(); value_node != NULL; value_node = value_node->next_sibling())
			    {
			      tagName4 = value_node->name();
			      valName4 = value_node->value();
			      //cout << "value: " << tagName4 << endl;
			      if(tagName4 == "has" )
				{
				  has = valName4;
				  //cout << "\t\t\tHas: " << valName4 << endl;
				}
			      else if(tagName4 == "owner" )
				{
				  owner = valName4;
				  //cout << "\t\t\tOwner: " << valName4 << endl;
				}
			      else if(tagName4 == "status" )
				{
				  status = valName4;
				  //cout << "\t\t\tStatus: " << valName4 << endl;
				}
			      else if(tagName4 == "object" )
				{
				  object = valName4;
				  //cout << "\t\t\tObject: " << valName4 << endl;
				}
			    }
			  trigger_thingy->setCondition(object, status, has, owner);

			}
		    }
		}
	    }
	}
      if(tagName == "item")
	{
	  bool exists = false;
	  //cout << "Making Item.." << endl;
	  temp = head_node->first_node();
	  Item * item_thingy;
	  valName2 = temp->value();
	  
	  for(ind = 0; ind < items.size(); ind++)
	    {
	      if(items[ind]->getName().compare(valName2) == 0)
		{
		  //cout << "found match" << endl;
		  exists = true;
		  item_thingy = items[ind];
		}
	    }
	  if(!exists)
	    {
	      item_thingy = new Item();
	      items.push_back(item_thingy);
	      item_thingy->setName(valName2);
	    }
	    //cout << "\tName: " << item_thingy -> getName() << endl;
	  for(name_node = head_node->first_node(); name_node != NULL; name_node = name_node->next_sibling())
	    {
	      tagName2 = name_node->name();
	      valName2 = name_node->value();
	      if(tagName2 == "writing")
		{
		  item_thingy->setWriting(valName2);
		  //cout << "\tWriting: " << item_thingy->getWriting() << endl;  
		}
		  
	      else if(tagName2 == "status")//set status
	      {
		  item_thingy->setStatus(valName2);
		  //cout << "\tStatus: " << valName2 << endl;
	      }
	      else if(tagName2 == "turnon")
		{
		  //cout << "\tTurn on:" << endl;
		  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node->next_sibling())
		    {
		      tagName3 = sub_node->name();
		      valName3 = sub_node->value();
		      if(tagName3 == "print")
			{
			  item_thingy->setPrint(valName3);
			  //cout << "\t\tPrint: " << valName3 << endl;
			}
		      else if(tagName3 == "action")
			{
			  item_thingy->addAction(valName3);
			  //cout << "\t\tAction: " << valName3 << endl;
			}
		    }
		}
	    }
	}
      if(tagName == "container")
	{
	  //cout << "Making container.. " << endl;
	  name_node = head_node->first_node();
	  valName2 = name_node->value();
	  for(ind = 0; ind < containers.size(); ind++)
	    {
	      if(containers[ind]->getName().compare(valName2) == 0)
		{
		  //cout << "\tName: " << containers[ind]->getName() << endl;
		  for(name_node = head_node->first_node(); name_node != NULL; name_node = name_node->next_sibling())
		    {
		      tagName2 = name_node->name();
		      valName2 = name_node->value();
		      if(tagName2 == "accept")
			{
			  
			  containers[ind]->setAccept(name_node->value());
			  //cout << "\tAccept: " << containers[ind]->getAccept() << endl;
			}
		      if(tagName2 == "status")
			{
			  containers[ind]->setStatus(name_node->value());
			  //cout << "\tStatus: " << containers[ind]->getStatus() << endl;
			}
		      if(tagName2 == "item")
			{
			  valName2 = name_node->value();
			  //cout << tempValue2 << endl;
			  int j = 0;
			  for(j = 0; j < items.size(); j++)
			    {
			      if(items[j]->getName() == valName2)
				{
				  containers[ind]->addItem(items[j]);
				}
			    }
			    //cout << "\tItem: " << valName2 << endl;
			}
		      if(tagName2 == "trigger")
			{
			  Triggers * trigger_thingy = new Triggers();
			  triggers.push_back(trigger_thingy);
			  containers[ind]->addTriggers(trigger_thingy);
			  //cout << "\tTrigger:" << endl;
			  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node->next_sibling())
			    {
			      tagName3 = sub_node->name();
			      valName3 = sub_node->value();
			      if(tagName3 == "type")
				{
				  trigger_thingy->setType(valName3);
				  //cout << "\t\tType: " << trigger_thingy->getType() << endl;
				}
			      if(tagName3 == "command")
				{
				  trigger_thingy->setCommand(valName3);
				  //cout << "\t\tCommand: "<< trigger_thingy->getCommand() << endl;
				}
			      if(tagName3 == "print")
				{
				  trigger_thingy->setPrint(valName3);
				  //cout << rooms[i]->getTriggers()[0]->getPrint() << endl;
				  //cout << "\t\tPrint: " << trigger_thingy->getPrint() << endl;
				}
			      if(tagName3 == "condition")
				{
				  //cout << "\t\tCondition: " << endl;
				  has = "";
				  owner = "";
				  status = "";
				  object = "";
				  for(value_node = sub_node->first_node(); value_node != NULL; value_node = value_node->next_sibling())
				  {
				  tagName4 = value_node->name();
				  valName4 = value_node->value();
				  if(tagName4 == "has" )
				  {
				    has = valName4;
				    //cout << "\t\t\tHas: " << valName4 << endl;
				  }
				  else if(tagName4 == "owner" )
				  {
				    owner = valName4;
				    //cout << "\t\t\tOwner: " << valName4 << endl;
				  }
				else if(tagName4 == "status" )
				  {
				    status = valName4;
				    //cout << "\t\t\tStatus: " << valName4 << endl;
				  }
				else if(tagName4 == "object" )
				  {
				    object = valName4;
				    //cout << "\t\t\tObject: " << valName4 << endl;
				  }
				}
				  trigger_thingy->setCondition(object, status, has, owner);
				}
				  else if(tagName3 == "action")
				{
				  trigger_thingy->addAction(valName3);
				  //cout << "\t\tAction: " << valName3 << endl;
				}
			    }
			}
		    }
		}
	    }
	}
      if(tagName == "creature")
	{
	  name_node = head_node->first_node();
	  valName2 = name_node->value();
	  found_exist_creature = false;
	  //cout << "Making creature.." << endl;
	  for(ind = 0 ; ind < creatures.size(); ind++)
	    {
	      if(creatures[ind]->getName() == valName2)
		{
		  found_exist_creature = true;
		  //cout << "\tName: " <<  creatures[ind]->getName() << endl;
		  for(name_node = head_node->first_node(); name_node != NULL; name_node = name_node->next_sibling())
		    {
		      tagName2 = name_node->name();
		      valName2 = name_node->value();
		      if(tagName2 == "vulnerability")
			{
			  creatures[ind]->setVulnerability(valName2);
			  //cout << "\tVulnerability: " << creatures[ind]->getVulnerability() << endl;
			}
		      if(tagName2 == "attack")
			{
			  //cout << "\tAttack: "<<endl;
			  creatures[ind]->setAttack(new Attack());
			  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node ->next_sibling())
			    {
			      tagName3 = sub_node->name();
			      valName3 = sub_node->value();
			      if(tagName3 == "print")
				{
				  creatures[ind]->getAttack()->setPrint(valName3);
				  //cout << "\t\tPrint: " << creatures[ind]->getAttack()->getPrint() << endl;
				}
			      else if(tagName3 == "action")
				{
				  creatures[ind]->getAttack()->addAction(valName3);
				  for(int q = 0; q < (creatures[ind]->getAttack())->getActions().size(); q++)
				    {
				      //cout << "\t\tAction: " << ((creatures[ind]->getAttack())->getActions())[q] << endl;
				    }
				}
			      else if(tagName3 == "condition")
				{
				  //cout << "\t\tCondition: " << endl;
				  for(value_node = sub_node->first_node();value_node != NULL; value_node = value_node->next_sibling())
				    {
				      tagName4 = value_node->name();
				      valName4 = value_node->value();
				      if(tagName4 == "object")
					{
					  creatures[ind]->getAttack()->setObject(valName4);
					  //cout << "\t\t\tObject: " <<creatures[ind]->getAttack()->getObject() << endl;
					}
				      if(tagName4 == "status")
					{
					  creatures[ind]->getAttack()->setStatus(valName4);
					  //cout << "\t\t\tStatus: " << creatures[ind]->getAttack()->getStatus() << endl;
					}
				    }
				}
			    }
			}
		      //triggers
		      if(tagName2 == "trigger")
			{
			  //cout << "\tTrigger: " << endl;
			  Triggers * trigger_thingy = new Triggers();
			  triggers.push_back(trigger_thingy);
			  creatures[ind]->addTriggers(trigger_thingy);
			  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node->next_sibling())
			    {
			      tagName3 = sub_node->name();
			      valName3 = sub_node->value();
			      if(tagName3 == "type")
				{
				  trigger_thingy->setType(valName3);
				  //cout << "\t\tType: " << trigger_thingy->getType() << endl;
				}
			      if(tagName3 == "command")
				{
				  trigger_thingy->setCommand(valName3);
				  //cout << "\t\tCommand: " << trigger_thingy->getCommand() << endl;
				}
			      if(tagName3 == "action"){
				trigger_thingy->addAction(valName3);
			      }
			      if(tagName3 == "print")
				{
				  trigger_thingy->setPrint(valName3);
				  //cout << "\t\tPrint: " << creatures[ind]->getTriggers()[0]->getPrint() << endl;
				}
			      if(tagName3 == "condition")
				{
				  //cout << "\t\tCondition: " << endl;
				  has = "";
				  owner = "";
				  status = "";
				  object = "";
				  for(value_node = sub_node->first_node(); value_node != NULL; value_node = value_node->next_sibling())
				  {
				  tagName4 = value_node->name();
				  valName4 = value_node->value();
				  if(tagName4 == "has" )
				  {
				    has = valName4;
				    //cout << "\t\t\tHas: " << valName4 << endl;
				  }
				  else if(tagName4 == "owner" )
				  {
				    owner = valName4;
				    //cout << "\t\t\tOwner: " << valName4 << endl;
				  }
				else if(tagName4 == "status" )
				  {
				    status = valName4;
				    //cout << "\t\t\tStatus: " << valName4 << endl;
				  }
				else if(tagName4 == "object" )
				  {
				    object = valName4;
				    //cout << "\t\t\tObject: " << valName4 << endl;
				  }
				  }
				  trigger_thingy->setCondition(object, status, has, owner);
				  //cout << trigger_thingy->getObject() << endl;
				}
			    }
			}
		    }
		}
	    }
	    if (found_exist_creature == false) {
		  Creature * creature_thingy = new Creature(); 
		  creature_thingy->setName(valName2);
		 // cout << "ADDED GIANT" << valName2 << endl;
		  creatures.push_back(creature_thingy); 
		  
	       
	       for(name_node = head_node->first_node(); name_node != NULL; name_node = name_node->next_sibling())
		    {
		      tagName2 = name_node->name();
		      valName2 = name_node->value();
		      if(tagName2 == "vulnerability")
			{
			  creature_thingy->setVulnerability(valName2);
			  //cout << "\tVulnerability: " << creatures[ind]->getVulnerability() << endl;
			}
		      if(tagName2 == "attack")
			{
			  //cout << "\tAttack: "<<endl;
			  creature_thingy->setAttack(new Attack());
			  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node ->next_sibling())
			    {
			      tagName3 = sub_node->name();
			      valName3 = sub_node->value();
			      if(tagName3 == "print")
				{
				  creature_thingy->getAttack()->setPrint(valName3);
				  //cout << "\t\tPrint: " << creatures[ind]->getAttack()->getPrint() << endl;
				}
			      else if(tagName3 == "action")
				{
				  creature_thingy->getAttack()->addAction(valName3);
				  for(int q = 0; q < (creatures[ind]->getAttack())->getActions().size(); q++)
				    {
				      //cout << "\t\tAction: " << ((creatures[ind]->getAttack())->getActions())[q] << endl;
				    }
				}
			      else if(tagName3 == "condition")
				{
				  //cout << "\t\tCondition: " << endl;
				  for(value_node = sub_node->first_node();value_node != NULL; value_node = value_node->next_sibling())
				    {
				      tagName4 = value_node->name();
				      valName4 = value_node->value();
				      if(tagName4 == "object")
					{
					  creature_thingy->getAttack()->setObject(valName4);
					  //cout << "\t\t\tObject: " <<creatures[ind]->getAttack()->getObject() << endl;
					}
				      if(tagName4 == "status")
					{
					  creature_thingy->getAttack()->setStatus(valName4);
					  //cout << "\t\t\tStatus: " << creatures[ind]->getAttack()->getStatus() << endl;
					}
				    }
				}
			    }
			}
		      //triggers
		      if(tagName2 == "trigger")
			{
			  //cout << "\tTrigger: " << endl;
			  Triggers * trigger_thingy = new Triggers();
			  triggers.push_back(trigger_thingy);
			  creature_thingy->addTriggers(trigger_thingy);
			  for(sub_node = name_node->first_node(); sub_node != NULL; sub_node = sub_node->next_sibling())
			    {
			      tagName3 = sub_node->name();
			      valName3 = sub_node->value();
			      if(tagName3 == "type")
				{
				  trigger_thingy->setType(valName3);
				  //cout << "\t\tType: " << trigger_thingy->getType() << endl;
				}
			      if(tagName3 == "command")
				{
				  trigger_thingy->setCommand(valName3);
				  //cout << "\t\tCommand: " << trigger_thingy->getCommand() << endl;
				}
			      if(tagName3 == "action"){
				trigger_thingy->addAction(valName3);
			      }
			      if(tagName3 == "print")
				{
				  trigger_thingy->setPrint(valName3);
				  //cout << "\t\tPrint: " << creatures[ind]->getTriggers()[0]->getPrint() << endl;
				}
			      if(tagName3 == "condition")
				{
				  //cout << "\t\tCondition: " << endl;
				  has = "";
				  owner = "";
				  status = "";
				  object = "";
				  for(value_node = sub_node->first_node(); value_node != NULL; value_node = value_node->next_sibling())
				  {
				  tagName4 = value_node->name();
				  valName4 = value_node->value();
				  if(tagName4 == "has" )
				  {
				    has = valName4;
				    //cout << "\t\t\tHas: " << valName4 << endl;
				  }
				  else if(tagName4 == "owner" )
				  {
				    owner = valName4;
				    //cout << "\t\t\tOwner: " << valName4 << endl;
				  }
				else if(tagName4 == "status" )
				  {
				    status = valName4;
				    //cout << "\t\t\tStatus: " << valName4 << endl;
				  }
				else if(tagName4 == "object" )
				  {
				    object = valName4;
				    //cout << "\t\t\tObject: " << valName4 << endl;
				  }
				  }
				  trigger_thingy->setCondition(object, status, has, owner);
				  //cout << trigger_thingy->getObject() << endl;
				}
			    }
			}
		    }
		}
	
	      
	      
	      
	      
	    
	}
      
    }
    
    
    // STARTING THE GAME BOYZ
    
    bool found_exit = false;
    bool hasstuff = false;
    string input;
    Item * item_take;
    Item * t_item;
    string border_name;
    vector<string> input_vector;
    vector<Triggers *> room_triggers;
    vector<Creature*> room_creatures;
    string ch;
    std::vector<Triggers * >::iterator itr_tr;
    std::vector<Room * >::iterator itr_rm;
    std::list<Item * >::iterator itr_it;
    
    vector<Container *> temp_cont;
    
    string get_owner;
    string get_object;
    string get_has;
    string get_status;
    string current_creature;
    
    vector<string> action_list;

    cout << current_room->getDescription() << endl;
    while (found_exit == false) {
      
      if (action_list.size() != 0) {
	input = action_list.back();
	action_list.pop_back();
      }else {
      // Get input
      std::getline(std::cin, input);
      }
      if (input == "n"){
	ch = input;
	input = "north";
	border_name = current_room->getBorderName(input);
	if (border_name == "nonexistant") {//north is not an option
	  cout << "Can't go that way" << endl;
	}
	else {//might be able to go
	  room_triggers = current_room->getTriggers();
	  bool found_trigger = false;
	  for (itr_tr = room_triggers.begin(); itr_tr != room_triggers.end(); itr_tr++ )
	  {
	    if ((*itr_tr)->getCommand() == ch) {//a trigger must be activated
	      found_trigger = true;
	      get_has = (*itr_tr)->getHas();
	      get_object = (*itr_tr)->getObject();
	      get_owner = (*itr_tr)->getOwner();
	      get_status = (*itr_tr)->getStatus();
	   
	      
	      if (get_owner == "inventory") {
		if(get_has == "no"){
		  hasstuff = true;
		}
		else{
		  hasstuff = false;
		}
		if (inventory.hasa(get_object) ){//== hasstuff) {
	
		  // iterate rooms find one that matches
		  for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		}
		
		else {
		  cout << (*itr_tr)->getPrint() << endl;
		}
	      }
	      else if (get_status == "locked") {
		cout << (*itr_tr)->getPrint() << endl;
	      }
	      else if (get_status == "unlocked") {
		for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		
		}	
	      }
	      
	    
	    }
	  
	  
	  if (found_trigger == false) {// no trigger is needed fly away my son
	    for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
	    {
	      if ((*itr_rm)->getName() == border_name) {
		 current_room = (*itr_rm);
		 cout << current_room->getDescription() << endl;
	      }
		    
	    }
	   }
	}
	
      }//end if north
      else if (input == "s"){
	ch = input;
	input = "south";
	border_name = current_room->getBorderName(input);
	if (border_name == "nonexistant") {//north is not an option
	  cout << "Can't go that way" << endl;
	}
	else {//might be able to go
	  room_triggers = current_room->getTriggers();
	  bool found_trigger = false;
	  for (itr_tr = room_triggers.begin(); itr_tr != room_triggers.end(); itr_tr++ )
	  {
	    if ((*itr_tr)->getCommand() == ch) {//a trigger must be activated
	      found_trigger = true;
	      get_has = (*itr_tr)->getHas();
	      get_object = (*itr_tr)->getObject();
	      get_owner = (*itr_tr)->getOwner();
	      get_status = (*itr_tr)->getStatus();
	   
	      
	      if (get_owner == "inventory") {
		if(get_has == "no"){
		  hasstuff = true;
		}
		else{
		  hasstuff = false;
		}
		if (inventory.hasa(get_object) ){//== hasstuff) {
	
		  // iterate rooms find one that matches
		  for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		}
		
		else {
		  cout << (*itr_tr)->getPrint() << endl;
		}
	      }
	      else if (get_status == "locked") {
		cout << (*itr_tr)->getPrint() << endl;
	      }
	      else if (get_status == "unlocked") {
		for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		
		}	
	      }
	      
	    
	  }
	  
	  if (found_trigger == false) {// no trigger is needed fly away my son
	    for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
	    {
	      if ((*itr_rm)->getName() == border_name) {
		 current_room = (*itr_rm);
		 cout << current_room->getDescription() << endl;
	      }
		    
	    }
	   }
	}
      }//end if south
      else if (input == "e"){
	ch = input;
	input = "east";
	border_name = current_room->getBorderName(input);
	if (border_name == "nonexistant") {//north is not an option
	  cout << "Can't go that way" << endl;
	}
	else {//might be able to go
	  room_triggers = current_room->getTriggers();
	  bool found_trigger = false;
	  for (itr_tr = room_triggers.begin(); itr_tr != room_triggers.end(); itr_tr++ )
	  {
	    if ((*itr_tr)->getCommand() == ch) {//a trigger must be activated
	      found_trigger = true;
	      get_has = (*itr_tr)->getHas();
	      get_object = (*itr_tr)->getObject();
	      get_owner = (*itr_tr)->getOwner();
	      get_status = (*itr_tr)->getStatus();
	   
	      
	      if (get_owner == "inventory") {
		if(get_has == "no"){
		  hasstuff = true;
		}
		else{
		  hasstuff = false;
		}
		if (inventory.hasa(get_object) ){//== hasstuff) {
	
		  // iterate rooms find one that matches
		  for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		}
		
		else {
		  cout << (*itr_tr)->getPrint() << endl;
		}
	      }
	      else if (get_status == "locked") {
		cout << (*itr_tr)->getPrint() << endl;
	      }
	      else if (get_status == "unlocked") {
		for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		
		}	
	      }
	      
	    
	    }
	  
	  
	  if (found_trigger == false) {// no trigger is needed fly away my son
	    for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
	    {
	      if ((*itr_rm)->getName() == border_name) {
		 current_room = (*itr_rm);
		 cout << current_room->getDescription() << endl;
	      }
		    
	    }
	   }
	}
      }//end if east
      else if (input == "w"){
	ch = input;
	input = "west";
	border_name = current_room->getBorderName(input);
	if (border_name == "nonexistant") {//north is not an option
	  cout << "Can't go that way" << endl;
	}
	else {//might be able to go
	  room_triggers = current_room->getTriggers();
	  bool found_trigger = false;
	  for (itr_tr = room_triggers.begin(); itr_tr != room_triggers.end(); itr_tr++ )
	  {
	    if ((*itr_tr)->getCommand() == ch) {//a trigger must be activated
	      found_trigger = true;
	      get_has = (*itr_tr)->getHas();
	      get_object = (*itr_tr)->getObject();
	      get_owner = (*itr_tr)->getOwner();
	      get_status = (*itr_tr)->getStatus();
	   
	      
	      if (get_owner == "inventory") {
		if(get_has == "no"){
		  hasstuff = true;
		}
		else{
		  hasstuff = false;
		}
		if (inventory.hasa(get_object) ){//== hasstuff) {
	
		  // iterate rooms find one that matches
		  for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		}
		
		else {
		  cout << (*itr_tr)->getPrint() << endl;
		}
	      }
	      else if (get_status == "locked") {
		cout << (*itr_tr)->getPrint() << endl;
	      }
	      else if (get_status == "unlocked") {
		for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
		  {
		    if ((*itr_rm)->getName() == border_name) {
		      current_room = (*itr_rm);
		      cout << current_room->getDescription() << endl;
		      
		    }
		    
		  }
		
		}	
	      }
	      
	    
	    }
	  
	  
	  if (found_trigger == false) {// no trigger is needed fly away my son
	    for (itr_rm = rooms.begin(); itr_rm != rooms.end(); itr_rm++ )
	    {
	      if ((*itr_rm)->getName() == border_name) {
		 current_room = (*itr_rm);
		 cout << current_room->getDescription() << endl;
	      }
		    
	    }
	   }
	}
      }//end if west
      else if (input ==""){}//fix seg fault	
      else if(input == "i"){
	cout << "Inventory:  " ;
	inventory.getItems();
	cout << endl;
      }//end inventory
      else if (input == "open exit"){
	if (current_room->getType() == "exit") {
	  cout << "Game Over" << endl;
	  return 0;
	}
	else {
	  cout << "Error" << endl;
	}
      }
      else{
      input_vector = split(input, ' '); 
      if (input_vector[0] == "read" && input_vector.size() == 2){
	inventory.read(input_vector[1]);
      }
      else if (input_vector[0] == "drop" && input_vector.size() == 2){
	inventory.drop(input_vector[1],current_room);
      }
      else if (input_vector[0] == "put" && input_vector.size() == 4){
	t_item = inventory.getItem(input_vector[1]);
	if (t_item != NULL) {
	  temp_cont = current_room->getContainers();
	  for (int i = 0; i < temp_cont.size(); i++) {
	    if (temp_cont[i]->getName() == input_vector[3]) { // find the container that matches what you are trying to insert item into
	      if (temp_cont[i]->getAccept() == t_item->getName() || temp_cont[i]->getAccept() == "") {
	      temp_cont[i]->addItem(t_item);
	      inventory.removeItem(t_item->getName());
	      cout << "Item " <<t_item->getName() << " added to " << temp_cont[i]->getName() << endl;
	       temp_trigg = temp_cont[i]->getTriggers();
		for (int j = 0; j < temp_trigg.size(); j++) {
		    if (temp_trigg[j]->getObject() == t_item->getName()) {
		      fixed_vector = temp_trigg[j]->getActions();
		      int size = fixed_vector.size();
			for (int l = 0; l < size; l++) {
			action_list.push_back( fixed_vector.back());
			fixed_vector.pop_back();
		      }
			cout << temp_trigg[j]->getPrint() << endl;
			
		    }
		}
		
		
	      }
	    }
	  }
	}
	else {
	  cout << "Error" << endl;
	}
	
      }
      else if (input_vector[0] == "Game" && input_vector[1] == "Over") {
	found_exit = true;
      }
      else if (input_vector[0] == "turn" && input_vector[1] == "on" && input_vector.size() == 3){
	if (inventory.hasa(input_vector[2])) {
	  Item * temp_item = inventory.getItem(input_vector[2]);
	    fixed_vector = temp_item->getActions();
		      int size = fixed_vector.size();
			for (int l = 0; l < size; l++) {
			action_list.push_back( fixed_vector.back());
			fixed_vector.pop_back();
		      }
	    if (action_list.size() != 0) {
	     cout << "You activate the " << temp_item->getName() << endl;
	     cout << temp_item->getPrint() << endl;
	     
	    }
	}
	    else {
	      cout << "Error" << endl;
	    }
	     
      }
      
      else if (input_vector[0] == "attack" && input_vector.size() == 4){
	t_item = inventory.getItem(input_vector[3]);
	hasstuff = false;
	if(t_item != NULL){
	  current_creature = current_room->getCreature(input_vector[1]);
	  if(current_creature != "nonexistant"){
	    for(int i = 0 ; i < creatures.size(); i++){
	     if  (creatures[i]->getName() == input_vector[1]) {
	       if (creatures[i]->getVulnerability(input_vector[3])) {
		 if(creatures[i]->getAttack()!=  NULL ){
		 if (creatures[i]->getAttack()->getStatus() == t_item->getStatus()) {
		    hasstuff = true;
		    cout << "You assault the " << input_vector[1] << " with the " <<input_vector[3] << endl;
		    cout << creatures[i]->getAttack()->getPrint() << endl;
		    fixed_vector = creatures[i]->getAttack()->getActions();
		    int size = fixed_vector.size();
		      for (int l = 0; l < size; l++) {
			action_list.push_back( fixed_vector.back());
			fixed_vector.pop_back();
		      }
		 }
		 }
		 else if (creatures[i]->getTriggers().size() != 0){
		   temp_trigg = creatures[i]->getTriggers();
		   for (int j = 0; j < temp_trigg.size(); j++ ) {
		    if (temp_trigg[j]->getObject() == input_vector[3]  && t_item->getStatus() == temp_trigg[j]->getStatus()){
		      cout << "You assault the " << input_vector[1] << " with the " <<input_vector[3] << endl;
		      cout << temp_trigg[j]->getPrint() << endl;
		      hasstuff = true;
		      if (triggers[j]->getType() == "single") {
		      triggers.erase(triggers.begin() + j);
		      }
		      //add actions
		      fixed_vector = temp_trigg[j]->getActions();
		      
		      for (int l = 0; l < fixed_vector.size(); l++) {
			if(fixed_vector.back() == "Game Over")
			{
			 while (action_list.size() > 0){
			   action_list.pop_back();
			}
			action_list.push_back("Game Over");
			break;
			}
			action_list.push_back( fixed_vector.back());
			fixed_vector.pop_back();
		      }
		    }
		  }
		 }
	       }
	     }
	    }
	  }
	}
	if (hasstuff == false) {
	  if (input_vector[1] == "giant" && (input_vector[3] == "axe" || input_vector[3] == "sword")){
	    cout << "You assault the giant with" <<input_vector[3]<<endl;
	    while (action_list.size() > 0){
		action_list.pop_back();
	    }
	    action_list.push_back("Game Over");
	  }
	  else{
	  cout << "Error" << endl;
	  }
	}
      }
		 
		
       else if (input_vector[0] == "open" && input_vector.size() == 2){
	//current_room
	hasstuff = false;
	temp_cont = current_room->getContainers();
	
	for(int i = 0; i < temp_cont.size(); i++) {
	  
	  if (temp_cont[i]->getName() == input_vector[1]) {
	    if (temp_cont[i]->items.size() == 0) {
	      cout << temp_cont[i]->getName() << " is empty"; 
	      hasstuff = true;
	    }
	    for (int jk = 0; jk < items.size(); jk++ ) {
	      
	      for (int j2 = 0; j2 < temp_cont[i]->items.size(); j2++) {
		
		   if (items[jk]->getName() == temp_cont[i]->items[j2]->getName()) {
		     cout << temp_cont[i]->getName() << " contains: " << temp_cont[i]->items[j2]->getName() << ", ";
		     current_room->addItem(items[jk]);
		     //temp_cont[i]->deleteItem(items[jk]->getName());
		     hasstuff = true;
		   }
		   
		 }
	    }
	  }
	  
	}
	cout << endl;
	if (hasstuff == false) {
	  cout << "Error" << endl;
	}
	
	    
	
      }
       else if (input_vector[0] == "take" && input_vector.size() == 2){
	 if (!inventory.hasa(input_vector[1])) {
	    item_take = current_room->take(input_vector[1]);
	    if (item_take != NULL) {
	      cout << "Item " << input_vector[1] << " added to inventory." << endl;
	      inventory.put(item_take);
	      current_room->deleteItem(input_vector[1]);
	      temp_cont = current_room->getContainers();
	      for (int i = 0; i < temp_cont.size(); i++) {
		for (int jk = 0; jk < temp_cont[i]->items.size(); jk++) {
		  if (temp_cont[i]->items[jk]->getName() == item_take->getName())
		  {
		    //cout << "got to delete" << endl;
		    temp_trigg = triggers;
		    for (int j = 0; j < temp_trigg.size(); j++) {
		      if (temp_trigg[j]->getObject() == item_take->getName()) {
			fixed_vector = temp_trigg[j]->getActions();
			int size = fixed_vector.size();
			for (int l = 0; l < size; l++) {
			  action_list.push_back( fixed_vector.back());
			  fixed_vector.pop_back();
			}
			  cout << temp_trigg[j]->getPrint() << endl;
			
			}
		      }
		    temp_cont[i]->deleteItem(temp_cont[i]->items[jk]->getName());
		  }
		}
	      }
	    }
	    else{
	      cout << "Error item not found" << endl;
	    }
	 }
	 else {
	   cout << "Already have this item" << endl;
	 }
       }
       else if (input_vector[0] == "Add" && input_vector.size() == 4){
	 hasstuff = false;
	 for (int i = 0; i < items.size(); i++) {
	   if (items[i]->getName() == input_vector[1]) {
	     
	     for (int jk = 0; jk < rooms.size(); jk++) {
		if (rooms[jk]->getName() == input_vector[3]) {
		  hasstuff = true;
		  rooms[jk]->addItem(items[i]);
		}
	     }
	     if (hasstuff == false) {
	       for (int jk = 0; jk < containers.size(); jk++) {
		 if (containers[jk]->getName() == input_vector[3]) {
		   containers[jk]->addItem(items[i]);
		   hasstuff = true;
		 }
	       }
	     }
	    }
	     
	     
       }
       for (int i = 0; i < creatures.size(); i++) {
	 if (creatures[i]->getName() == input_vector[1]) {
	   for (int j = 0; j < rooms.size(); j ++) {
	     if (rooms[j]->getName() == input_vector[3]) {
	       hasstuff = true;
	       rooms[j]->addCreature(creatures[i]);
	     }
	   }
	 }
       }
	   
       if (hasstuff == false) {
	 cout << "Error" << endl;
       }
       else {
	 cout << "Added "<<input_vector[1] << " to " << input_vector[3] << endl; 
       }
       }else if (input_vector[0] == "Delete" && input_vector.size() == 2){
	  hasstuff = false;
	  for (int i = 0; i < rooms.size(); i++) {
	    rooms[i]->deleteBorder(input_vector[1]);
	    rooms[i]->deleteItem(input_vector[1]);
	    if (rooms[i]->getName() == input_vector[1])
	    {
	      rooms.erase(rooms.begin() + i);
	    }
		 
	       
	  }
	  }else if (input_vector[0] == "Update" && input_vector.size() == 4){
	    hasstuff = false;  
	    for (int i = 0; i < items.size(); i++) {
		if (items[i]->getName() == input_vector[1]) {
		  items[i]->setStatus(input_vector[3]);
		  for (int j = 0; j < triggers.size(); j++ ) {
		    if (triggers[j]->getObject() == items[i]->getName() && items[i]->getStatus() == triggers[j]->getStatus()){
		      cout << triggers[j]->getPrint() << endl;
		      hasstuff = true;
		      if (triggers[j]->getType() == "single") {
		      triggers.erase(triggers.begin() + j);
		      }
		    }
		  }
		}
	      }
	      if(hasstuff ==  false){
		temp_cont = current_room->getContainers();
		for (int i = 0; i < temp_cont.size(); i++) {
		  if (temp_cont[i]->getName() == input_vector[1]) {
		    temp_cont[i]->setStatus(input_vector[3]);
	
		    for (int j = 0; j < triggers.size(); j++ ) {
		      if (triggers[j]->getObject() == input_vector[1]){
			triggers[j]->setStatus(input_vector[3]);
			if (temp_trigg[j]->getType() == "single") {
			temp_trigg.erase(temp_trigg.begin() + j);
			}
		      }
		    }
		  }
		}
	      }
	      
	  }
		 
	 
	  
       else{//not a valid input
	 cout << "Error Invalid Input" << endl;
       }
       
       
	 
        
      
      }//end multiword else (user input valitdation is donzo)

      // Check triggers if override command
      
      // Execute command if not overridden
      
      // Check if effects of command activate trigger_thingy
      
      // If command activates trigger, perform indicated actions and check new status if new triggers should happen
      
      
      
      
      
      
      
    }//end while
    cout << "Victory!" << endl;
    




  return 0;
}//end main

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
