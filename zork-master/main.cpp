#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include <string>
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Triggers.h"
using std::string;
using namespace std;
using namespace rapidxml;
string tempName;
string tempName2;
string tempName3;
string tempName4;
string tempValue2;
string tempValue3;
string tempValue4;
string tempValue;
string borderDirection;
string borderName;
string trigHas;
string trigStatus;
string trigOwner;
string trigObject;
vector<Room*> rooms;
vector<Item*> items;
vector<Container*> containers;
vector<Creature*> creatures;
vector<Triggers*> triggers;

Room* current_room = NULL;;

int i = 0;
int main()
{
  file<> xmlFile("sample.txt.xml"); // Default template is char
  xml_document<> doc;
  doc.parse<0>(xmlFile.data());
  cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
  xml_node<> *map = doc.first_node();
  //cout << "Node room has value " << node->value() << "\n";
  for (xml_node<> *node1 = map->first_node();
       node1; node1 = node1->next_sibling())
    {
      tempName = node1->name();
      tempValue = node1->value();
      if(tempName == "room")
	{
	  Room* room1 = new Room();//create a room
	  rooms.push_back(room1);
	  // tempValue = room1.getName();
	  // cout << room1.getName() << "/n";
	  for(xml_node<> *node2 = node1->first_node();
	      node2; node2 = node2->next_sibling())
	    {
	      tempName2 = node2->name();
	      tempValue2 = node2->value();
	      if(tempName2 == "name")
		{
		  room1->setName(tempValue2);
		  // cout << rooms[i]->getName() << endl;
		}
	      if(tempName2 == "description")
		{
		  room1->setDescription(tempValue2);
		}
	      if(tempName2 == "status")
		{
		  room1->setStatus(tempValue2);
		}
	      if(tempName2 == "type")
		{
		  room1->setType(tempValue2);
		}
	      if(tempName2 == "border")
		{
		  for(xml_node<> *node3 = node2->first_node();
		      node3; node3 = node3->next_sibling())
		    {
		      tempName3 = node3->name();
		      if(tempName3 == "direction")
			{
			  tempValue3 = node3->value();
			  borderDirection = tempValue3;
			}
		      if(tempName3 == "name")
			{
			  tempValue3 = node3->value();
			  borderName = tempValue3;
			}
		    }
		  room1->addBorder(borderDirection, borderName);
		  cout << borderDirection << endl;
		  cout << room1->getBorderName(borderDirection) << endl;
		}
	      if(tempName2 == "container")
		{
		  Container* newContainer = new Container(); //create new container
		  containers.push_back(newContainer);
		  tempValue2 = node2->value();
		  newContainer->setName(tempValue2); //add container to contianer array
		  room1->addContainer(newContainer); //add container to room
		}
	      if(tempName2 == "creature")
		{
		  Creature* newCreature = new Creature(); //create new creature
		  tempValue2 = node2->value();
		  newCreature->setName(tempValue2);
		  creatures.push_back(newCreature); //add creature to creature array
		  room1->addCreature(newCreature);//add creature to room
		}
	      if(tempName2 == "item")
		{
		  Item* newItem = new Item();//create new item
		  items.push_back(newItem);//add item to item array
		  tempValue2 = node2->value();
		  items.back()->setName(tempValue2);
		  room1->addItem(newItem); //add item to room
		}
	      if(tempName2 == "trigger")
		{
		  Triggers* newTriggers = new Triggers();
		  triggers.push_back(newTriggers);
		  room1->addTriggers(newTriggers);
		  for(xml_node<> *node3 = node2->first_node();
		      node3; node3 = node3->next_sibling())
		    {
		      tempName3 = node3->name();
		      tempValue3 = node3->value();
		      if(tempName3 == "type")
			{
			  cout << tempName3 << endl;
			  newTriggers->setType(tempValue3);
			  cout << newTriggers->getType() << endl;
			}
		      if(tempName3 == "command")
			{
			  cout << tempName3 << endl;
			  newTriggers->setCommand(tempValue3);
			  cout << newTriggers->getCommand() << endl;
			}
		      if(tempName3 == "print")
			{
			  cout << tempName3 << endl;
			  newTriggers->setPrint(tempValue3);
			  cout << room1->getTriggers()[0]->getPrint() << endl;
			}
		      if(tempName3 == "condition")
			{
			  trigHas = "default";
			  trigObject = "default";
			  trigOwner = "default";
			  trigStatus = "default";
			  for(xml_node<> *node4 = node3->first_node();
			      node4; node4 = node4->next_sibling())
			    {
			      tempName4 = node4->name();
			      tempValue4 = node4->value();
			      if(tempName4 == "has" )
				{
				  trigHas = tempValue4;
				}
			      if(tempName4 == "object")
				{
				  trigObject = tempValue4;
				}
			      if(tempName4 == "owner")
				{
				  trigOwner = tempValue4;
				}
			      if(tempName4 == "status")
				{
				  trigStatus = tempValue4;
				}
			    }
			  newTriggers->setCondition(trigObject, trigStatus, trigHas, trigOwner);
			  cout << "trigger" << endl << "object" << endl;
			  cout << rooms[i]->getTriggers()[0]->getCondition()->object << endl;
			  cout << "has" << endl;
			  cout << newTriggers->getCondition()->has << endl;
			  cout << "owner" << endl;
			  cout << newTriggers->getCondition()->owner << endl;
			  cout << "status" << endl;
			  cout << newTriggers->getCondition()->status << endl;
			}
		    }
		}
	      cout << "Node has name2 " << node2->name() << " ";
	      cout << "with value2 " << node2->value() << "\n";
	    }
	}
      if(tempName == "item")
	{
	  xml_node<> *tempNode2 = node1->first_node();
	  Item* tempItem;
	  tempValue2 = tempNode2->value();
	  cout << tempValue2 << "!!!!!!!!!" <<endl;
	  int found = 0;
	  int i = 0;
	  for(i = 0; i < items.size(); i++)
	    {
	      if(items[i]->getName().compare(tempValue2) == 0)
		{
		  found = 1;//item alrdy exists
		  tempItem = items[i];
		}
	    }
	  if(found == 0)//if item not found create one
	    {
	      tempItem = new Item();
	      items.push_back(tempItem);
	      tempItem->setName(tempValue2);
	    }
	  for(xml_node<> *node2 = node1->first_node();
	      node2; node2 = node2->next_sibling())
	    {
	      tempName2 = node2->name();
	      tempValue2 = node2->value();
	      if(tempName2 == "writing")//set writing
		{
		  cout << tempName2 << endl;
		  tempItem->setWriting(node2->value());
		  cout << tempItem->getWriting() << endl;
		}
	      if(tempName2 == "status")//set status
		{
		  cout << tempName2 << endl;
		  tempItem->setStatus(node2->value());
		  cout << tempItem->getStatus() << endl;
		}
	      if(tempName2 == "turnon")
		{
		  for(xml_node<> *node3 = node2->first_node();
		      node3; node3 = node3->next_sibling())
		    {
		      tempName3 = node3->name();
		      tempValue3 = node3->value();
		      if(tempName3 == "print")
			{
			  cout << tempName3 << endl;
			  tempItem->setPrint(tempValue3);
			  cout << tempItem->getPrint() << endl;
			}
		      if(tempName3 == "action")
			{
			  cout << tempName3 << endl;
			  tempItem->addAction(tempValue3);
			  for(int q =0; q < tempItem->getActions().size(); q++)
			    {
			      cout << tempItem->getActions()[q] << endl;
			    }
			}
		    }
		}
	      //create trigger NOT SURE IF ITEMS NEED TRIGGERS
	      if(tempName2 == "trigger")
		{
		  Triggers* newTriggers = new Triggers();
		  triggers.push_back(newTriggers);
		  tempItem->addTriggers(newTriggers);
		  for(xml_node<> *node3 = node2->first_node();
		      node3; node3 = node3->next_sibling())
		    {
		      tempName3 = node3->name();
		      tempValue3 = node3->value();
		      if(tempName3 == "type")
			{
			  cout << tempName3 << endl;
			  newTriggers->setType(tempValue3);
			  cout << newTriggers->getType() << endl;
			}
		      if(tempName3 == "command")
			{
			  cout << tempName3 << endl;
			  newTriggers->setCommand(tempValue3);
			  cout << newTriggers->getCommand() << endl;
			}
		      if(tempName3 == "print")
			{
			  cout << tempName3 << endl;
			  newTriggers->setPrint(tempValue3);
			  cout << rooms[i]->getTriggers()[0]->getPrint() << endl;
			}
		      if(tempName3 == "condition")
			{
			  trigHas = "default";
			  trigObject = "default";
			  trigOwner = "default";
			  trigStatus = "default";
			  for(xml_node<> *node4 = node3->first_node();
			      node4; node4 = node4->next_sibling())
			    {
			      tempName4 = node4->name();
			      tempValue4 = node4->value();
			      if(tempName4 == "has" )
				{
				  trigHas = tempValue4;
				}
			      if(tempName4 == "object")
				{
				  trigObject = tempValue4;
				}
			      if(tempName4 == "owner")
				{
				  trigOwner = tempValue4;
				}
			      if(tempName4 == "status")
				{
				  trigStatus = tempValue4;
				}
			    }
			  newTriggers->setCondition(trigObject, trigStatus, trigHas, trigOwner);
			  cout << "trigger" << endl << "object" << endl;
			  cout << tempItem->getTriggers()[0]->getCondition()->object << endl;
			  cout << "has" << endl;
			  cout << newTriggers->getCondition()->has << endl;
			  cout << "owner" << endl;
			  cout << newTriggers->getCondition()->owner << endl;
			  cout << "status" << endl;
			  cout << newTriggers->getCondition()->status << endl;
			}
		    }
		}
	    }
	}
      if(tempName == "container")
	{
	  //search container vector for container with same name
	  xml_node<> *tempNode2 = node1->first_node();
	  tempValue2 = tempNode2->value();
	  cout << tempValue2 << "!!!!!!!" <<endl;
	  int found = 0;
	  int i = 0;
	  for(i = 0; i < containers.size(); i++)
	    {
	      if(containers[i]->getName().compare(tempValue2) == 0)
		{
		  found = 1;
		  for(xml_node<> *node2 = node1->first_node();
		      node2; node2 = node2->next_sibling())
		    {
		      tempName2 = node2->name();
		      tempValue2 = node2->value();
		      if(tempName2 == "accept")
			{
			  cout << tempName2 << endl;
			  containers[i]->setAccept(node2->value());
			  cout << containers[i]->getAccept() << endl;
			}
		      if(tempName2 == "status")
			{
			  cout << tempName2 << endl;
			  containers[i]->setStatus(node2->value());
			  cout << containers[i]->getStatus() << endl;
			}
		      if(tempName2 == "item")
			{
			  tempValue2 = node2->value();
			  //cout << tempValue2 << endl;
			  int j = 0;
			  for(j = 0; j < items.size(); j++)
			    {
			      //cout << items[j]->getName() << endl;
			      if(items[j]->getName() == tempValue2)
				{
				  //cout << "!!!!!!!!"<< endl;
				  //cout << tempValue2 << endl;
				  containers[i]->addItem(items[j]);//////

				}
			    }
			}
		      //add trigger
		      if(tempName2 == "trigger")
			{
			  Triggers* newTriggers = new Triggers();
			  triggers.push_back(newTriggers);
			  containers[i]->addTriggers(newTriggers);
			  for(xml_node<> *node3 = node2->first_node();
			      node3; node3 = node3->next_sibling())
			    {
			      tempName3 = node3->name();
			      tempValue3 = node3->value();
			      if(tempName3 == "type")
				{
				  cout << tempName3 << endl;
				  newTriggers->setType(tempValue3);
				  cout << newTriggers->getType() << endl;
				}
			      if(tempName3 == "command")
				{
				  cout << tempName3 << endl;
				  newTriggers->setCommand(tempValue3);
				  cout << newTriggers->getCommand() << endl;
				}
			      if(tempName3 == "print")
				{
				  cout << tempName3 << endl;
				  newTriggers->setPrint(tempValue3);
				  cout << rooms[i]->getTriggers()[0]->getPrint() << endl;
				}
			      if(tempName3 == "condition")
				{
				  trigHas = "default";
				  trigObject = "default";
				  trigOwner = "default";
				  trigStatus = "default";
				  for(xml_node<> *node4 = node3->first_node();
				      node4; node4 = node4->next_sibling())
				    {
				      tempName4 = node4->name();
				      tempValue4 = node4->value();
				      if(tempName4 == "has" )
					{
					  trigHas = tempValue4;
					}
				      if(tempName4 == "object")
					{
					  trigObject = tempValue4;
					}
				      if(tempName4 == "owner")
					{
					  trigOwner = tempValue4;
					}
				      if(tempName4 == "status")
					{
					  trigStatus = tempValue4;
					}
				    }
				  newTriggers->setCondition(trigObject, trigStatus, trigHas, trigOwner);
				  cout << "trigger" << endl << "object" << endl;
				  cout << containers[i]->getTriggers()[0]->getCondition()->object << endl;
				  cout << "has" << endl;
				  cout << newTriggers->getCondition()->has << endl;
				  cout << "owner" << endl;
				  cout << newTriggers->getCondition()->owner << endl;
				  cout << "status" << endl;
				  cout << newTriggers->getCondition()->status << endl;
				}
			    }
			}
		    }
		}
	    }
	}
      if(tempName == "creature")
	{
	  xml_node<> *tempNode2 = node1->first_node();
	  tempValue2 = tempNode2->value();
	  cout << tempValue2 << "!!!!!!!" <<endl;
	  //search creature vector for creature with same name
	  int i = 0;
	  for(i= 0 ; i < creatures.size(); i ++)
	    {
	      if(creatures[i]->getName() == tempValue2)
		{
		  for(xml_node<> *node2 = node1->first_node();
		      node2; node2 = node2->next_sibling())
		    {
		      tempName2 = node2->name();
		      tempValue2 = node2->value();
		      if(tempName2 == "vulnerability")
			{
			  cout << tempName2 << endl;
			  creatures[i]->setVulnerability(tempValue2);
			  cout << creatures[i]->getVulnerability() << endl;
			}
		      if(tempName2 == "attack")
			{
			  cout << tempName2 << endl;
			  creatures[i]->setAttack(new Attack());
			  for(xml_node<> *node3 = node2->first_node();
			      node3; node3 = node3->next_sibling())
			    {
			      tempName3 = node3->name();
			      tempValue3 = node3->value();
			      if(tempName3 == "print")
				{
				  cout << tempName3 << endl;
				  creatures[i]->getAttack()->setPrint(tempValue3);
				  cout << creatures[i]->getAttack()->getPrint() << endl;
				}
			      if(tempName3 == "action")
				{
				  cout << tempName3 << endl;
				  creatures[i]->getAttack()->addAction(tempValue3);
				  for(int q = 0; q < (creatures[i]->getAttack())->getActions().size(); q++)
				    {
				      cout << ((creatures[i]->getAttack())->getActions())[q] << endl;
				    }
				}
			      if(tempName3 == "condition")
				{
				  for(xml_node<> *node4 = node3->first_node();node4; node4 = node4->next_sibling())
				    {
				      tempName4 = node4->name();
				      tempValue4 = node4->value();
				      if(tempName4 == "object")
					{
					  cout << tempName4 << endl;
					  creatures[i]->getAttack()->setObject(tempValue4);
					  cout << creatures[i]->getAttack()->getObject() << endl;
					}
				      if(tempName4 == "status")
					{
					  cout << tempName4 << endl;
					  creatures[i]->getAttack()->setStatus(tempValue4);
					  cout << creatures[i]->getAttack()->getStatus() << endl;
					}
				    }
				}
			    }
			}
		      //triggers
		      if(tempName2 == "trigger")
			{
			  Triggers* newTriggers = new Triggers();
			  triggers.push_back(newTriggers);
			  creatures[i]->addTriggers(newTriggers);
			  for(xml_node<> *node3 = node2->first_node();
			      node3; node3 = node3->next_sibling())
			    {
			      tempName3 = node3->name();
			      tempValue3 = node3->value();
			      if(tempName3 == "type")
				{
				  cout << tempName3 << endl;
				  newTriggers->setType(tempValue3);
				  cout << newTriggers->getType() << endl;
				}
			      if(tempName3 == "command")
				{
				  cout << tempName3 << endl;
				  newTriggers->setCommand(tempValue3);
				  cout << newTriggers->getCommand() << endl;
				}
			      if(tempName3 == "print")
				{
				  cout << tempName3 << endl;
				  newTriggers->setPrint(tempValue3);
				  cout << creatures[i]->getTriggers()[0]->getPrint() << endl;
				}
			      if(tempName3 == "condition")
				{
				  trigHas = "default";
				  trigObject = "default";
				  trigOwner = "default";
				  trigStatus = "default";
				  for(xml_node<> *node4 = node3->first_node();
				      node4; node4 = node4->next_sibling())
				    {
				      tempName4 = node4->name();
				      tempValue4 = node4->value();
				      if(tempName4 == "has" )
					{
					  trigHas = tempValue4;
					}
				      if(tempName4 == "object")
					{
					  trigObject = tempValue4;
					}
				      if(tempName4 == "owner")
					{
					  trigOwner = tempValue4;
					}
				      if(tempName4 == "status")
					{
					  trigStatus = tempValue4;
					}
				    }
				  newTriggers->setCondition(trigObject, trigStatus, trigHas, trigOwner);
				  cout << "trigger" << endl << "object" << endl;
				  cout << creatures[i]->getTriggers()[0]->getCondition()->object << endl;
				  cout << "has" << endl;
				  cout << newTriggers->getCondition()->has << endl;
				  cout << "owner" << endl;
				  cout << newTriggers->getCondition()->owner << endl;
				  cout << "status" << endl;
				  cout << newTriggers->getCondition()->status << endl;
				}
			    }
			}
		    }
		}
	    }
	}
      i++;
    }
  //init starting room
  for(i = 0; i < rooms.size(); i++)
    {
      if(rooms[i]->getName() == "Entrance")
	{
	  current_room = rooms[i];
	  break;
	}
    }


  //welcome()
  if(current_room != NULL)
    {
      cout << current_room->getDescription() << endl;
    }


    vector<Item*> inventory;
   // vector<Room*>::iterator room_iter = rooms.begin();
    //vector<Item*>::iterator item_iter = items.begin();
   // vector<Container*>::iterator container_iter = containers.begin();
    //vector<Creature*>::iterator creature_iter = creatures.begin();

    string command;
	int game_end = 0;

    while(game_end == 0) 
    {
    	string stay = "";
    
  
    	getline(cin,command);
		

    		int valid;
    		string input_command[6] = {"n","s", "e", "w", "i", "open exit"};
    		int return_val = 0; //ret
    		int check_has = 0;
    		int error = 1;
    		int has_check = 0;
    		int trigger_true = 0;

    		vector<Triggers*> current_room_trigger = current_room->getTriggers();
    		//read user input


    		int a = 0;
    		int command_flag = 0;






    		for(a = 0 ; a < current_room_trigger.size(); a++)
    		{
    			string tempObject = current_room_trigger[a]->getObject();
    			string tempStatus = current_room_trigger[a]->getStatus();
    			string tempHas = current_room_trigger[a]->getHas();
    			string tempOwner = current_room_trigger[a]->getOwner();
    			if(current_room_trigger[a]->getCommand() == command )
    			{
    				command_flag = 1;

    			}
    			else if(current_room_trigger[a]->getCommand() == "")
    			{
    				command_flag = 1;
    				
    			}
    			//cout << command_flag << endl;
    			if(command_flag == 1)
    			{

    			for(int b = 0; b < items.size(); b++)
				{
					if(tempObject == items[b]->getName())
					{
						//cout << tempObject << endl;;
						//find matching item
				
						if((items[b]->getStatus()) == tempStatus)
						{
							cout << current_room_trigger[a]->getPrint() << endl;
							//action
						}
						else
						{


							//FIND ITEM LOCATION
							//check containers for item
							if(tempOwner == "inventory")
							{
							
								if(tempHas == "yes")
								{		
									for(int c = 0; c < inventory.size(); c++)
									{
										if(inventory[c]->getName() == tempObject)
										{
											cout << current_room_trigger[a]->getPrint() << endl;
											trigger_true  = 1;
										}
									}
								}
								else if(tempHas == "no")
								{
									for(int c = 0; c < inventory.size(); c++)
									{
										if(inventory[c]->getName() == tempObject)
										{
											has_check = 1;
										}
									}
									if(!has_check)
									{
									cout << current_room_trigger[a]->getPrint() << endl;
									trigger_true  = 1;
									}
								}		

							}

							
							//FIND ITEM LOCATION
							//check check if container is trigger owner
							for(int c = 0; c < containers.size() ; c++)
							{
								if(containers[c]->getName() == tempOwner)
								{

									//check if container holds the item in question
									vector<Item*> tempItems =  containers[c]->getItems();
									if(tempHas == "yes")
									{
									for(int d = 0; d < tempItems.size() ; d++)
									{
										if(tempItems[d]->getName() == tempObject)
										{
											
											cout << current_room_trigger[a]->getPrint();
											trigger_true = 1;
											//perform action
										}	
									}

									}
									else if(tempHas == "no") 
										{
											for(int d = 0; c < tempItems.size(); d++)
											{
												if(tempItems[d]->getName() == tempObject)
												{
													has_check = 1;
												}
											}
											if(!has_check)
											{
												cout << current_room_trigger[a]->getPrint() << endl;
												trigger_true  = 1;
											}
										}

								}
							}
							//check rooms for item
							for(int c = 0; c < rooms.size() ; c++)
							{
								if(rooms[c]->getName() == tempOwner)
								{
									//check if room holds the item in question
									vector<Item*> tempItems =  rooms[c]->getItems();
									if(tempHas == "yes")
									{
									for(int d = 0; d < tempItems.size() ; d++)
									{
										if(tempItems[d]->getName() == tempObject)
										{
											
											cout << current_room_trigger[a]->getPrint();
											trigger_true = 1;
											//perform action
											
										}
									}
									}
									else if(tempHas == "no")
											{	
											for(int d = 0; c < tempItems.size(); d++)
											{
												if(tempItems[d]->getName() == tempObject)
												{
													has_check = 1;
												}
											}
											if(!has_check)
											{
												cout << current_room_trigger[a]->getPrint() << endl;
												trigger_true  = 1;
											}
											}	
								}
							}
						}

						/////
					}
				}

				}
    			//check if command mastches


    			//if(type == single) delete trigger
    			//current_room_trigger[a]->getType()

	    	}//ENDOFTRIGGER

    		   if(command == "n" || command== "s" || command == "e" || command == "w")
		  {

		    int roomExistFlag = 0;
		    if(!trigger_true)
		      {
	    		string temp_border = current_room->getBorderName(command);
	    		//cout << temp_border << endl;
	    		for(int g = 0; g< rooms.size(); g++)
			  	{
			    if(rooms[g]->getName() == temp_border)
			      {
					current_room = rooms[g];
					roomExistFlag = 1;
					cout << current_room->getDescription() << endl;
			      }
			     
			  	}
	    		if(roomExistFlag == 0)
			  	{
			    cout << "Can't go that way!" << endl;
			  	}
			
		      }
		  }	   
		  
    	else if(command =="i")
	  {
	    cout << "Inventory : ";
	    for(int a = 0; a < inventory.size(); a++)
	    {
	    	cout << inventory[a]->getName() << ", ";
	    }
	    cout << endl;
	    
	  }
	  else if( command == "open exit")
	  {
	  	if(current_room->getType() == "exit")
	  	{
	  		cout << "Game Over" << endl;
	  		game_end = 1;
	  	}
	  }



	  else
	  {
	  	string delim = " ";
	  	size_t pos = command.find(delim);
	  	string actionCommand = command.substr(0,pos);
	  	string item;
	  	string container;
	  	string creature;
	  	
	  	if(actionCommand == "take")
	  	{
	  		int found = 0;
	  		int i = 0;
	  		vector<Item*>::iterator it;
	  		item = command.erase(0,pos + delim.length());
	  		for(i = 0 ; i < current_room->getItems().size(); i++ )
	  		{

	  			if(current_room->getItems()[i]->getName() == item)
	  			{

	  				inventory.push_back(current_room->getItems()[i]);
	  				cout << "Item " << item << " added to inventory." << endl;
	  				current_room->deleteItem(item);
   					 
	  				found = 1;
	  				break;
	  			}
	  			
	  		}

	  		if(found == 0)
	  		{
	  			cout << item << " not found in room." << endl;
	  		}
	  	}

	  	else if(actionCommand == "open")
	  	{
	  		int found = 0;
	  		int i = 0;
	  		container = command.erase(0,pos + delim.length());
	  		
	  		for(i = 0;i < current_room->getContainers().size(); i++)
	  		{
	  			if(current_room->getContainers()[i]->getName() == container)
	  			{
	  				if(current_room->getContainers()[i]->getItems().size() == 0)
	  				{
	  					cout << "container is empty" << endl;
	  					break;
	  				}


	  				cout << container << " contains: ";
	  				for(int b = 0; b < current_room->getContainers()[i]->getItems().size() ; b++)
	  				{
	  					cout << current_room->getContainers()[i]->getItems()[b]->getName() << " " ;
	  					current_room->addItem(current_room->getContainers()[i]->getItems()[b]);
	  				}
	  				cout << endl;

	  			}

	  		}

	  	}

	  	else if(actionCommand == "read")
	  	{
	  		int found = 0;
	  		int i = 0;
	  		item = command.erase(0,pos + delim.length());
	  		for(i = 0; i < inventory.size() ; i++)
	  		{
	  			if(inventory[i]->getName() == item)
	  			{
	  				cout << inventory[i]->getWriting() << endl;
	  				found = 1;
	  			}

	  		}
	  		if(found == 0)
	  		{
	  			cout << item << "not in inventory" << endl;
	  		}

	  	}

		///DROP
		else if(actionCommand == "drop")
		  {
		    int found = 0;
		    int i = 0;
		    item = command.erase(0,pos + delim.length());
		    cout << item << endl;
		    for(i = 0 ; i < inventory.size(); i++ )
		      {
			if(inventory[i]->getName() == item)
			  {
			    current_room->addItem(inventory[i]);
			    cout << "Item " << item << " dropped to ground." << endl;
			    inventory.erase(inventory.begin() + i);
			    found = 1;
			    break;
			  }
	  		
		      }
		    if(found == 0)
		      {
			cout << item << " not found in inventory." << endl;
		      }
		  }


//TURN ON 
	  	else if(actionCommand == "turn")
	  	{
	  		int found = 0;
	  		int i = 0;
	  		item = command.erase(0,pos + delim.length());
	  		pos = command.find(delim);
	  		item = command.erase(0, pos + delim.length());
	  		for(i = 0; i < inventory.size() ; i++)
	  		{
	  			if(inventory[i]->getName() == item)
	  			{
	  				cout << inventory[i]->getPrint() << endl;
	  				found = 1;
	  				//ACTION
	  				vector <string> commands = inventory[i]->getActions();
	  				for(int b = 0; b < commands.size(); b++)
	  				{
	  					command = commands[b];
						//	cout << command << endl;

	  					delim = " ";
	  					pos = command.find(delim);
	  					string actionCommand = command.substr(0,pos);
	  					//cout << actionCommand << endl;
						if(actionCommand == "Update")
						{

							command.erase(0,pos +delim.length());
							pos = command.find(delim);
	  						item = command.substr(0, pos);
							//cout << item << endl;
		  					for(int a = 0; a < items.size(); a++)
	  						{
	  							if(items[a]->getName() == item)
	  							{
	  								string stat = command.erase(0,pos + delim.length());
	  								pos = command.find(delim);
	  								stat = command.erase(0, pos + delim.length());
	  								items[a]->setStatus(stat);
	  								//cout << stat << endl;
	  							}
	  						}
						}
					//end update
					//add
						if(actionCommand == "Add")
						{
							command.erase(0,pos +delim.length());
							pos = command.find(delim);
	  						item = command.substr(0, pos);
	  						//cout << item << endl;
	  						for(int a = 0; a < items.size(); a++)
	  						{
	  							if(items[a]->getName() == item)
	  							{
	  								string roo = command.erase(0,pos + delim.length());
	  								pos = command.find(delim);
	  								roo = command.erase(0, pos + delim.length());
	  								for(int c = 0; c < rooms.size(); c++)
	  								{
	  									if(rooms[c]->getName() == roo)
	  									{
	  										rooms[c]->addItem(items[a]);
	  										cout << items[a]->getName() << " added to " << rooms[c]->getName() << endl;
	  									}

	  								}
	  								//items[a]->setStatus(stat);
	  								//cout << stat << endl;
	  							}
	  						}

						}


					}
					


	  			}

	  		}
	  		if(found == 0)
	  		{
	  			cout << item << "not in inventory" << endl;
	  		}

	  	}///////////

	  	else if(actionCommand == "attack")
	  	{
	  		int i = 0;
	  		int j = 0;
	  		int k = 0;
	  		int l = 0;

	  		pos = command.find(delim);
			command.erase(0, pos + delim.length());
			
			pos = command.find(delim);
			creature = command.substr(0,pos);
		
			command.erase(0, pos + delim.length());
			pos = command.find(delim);
			if(command.substr(0, pos) == "with")
			{
				command.erase(0, pos + delim.length());
				item = command;

				for(i = 0; i < inventory.size() ; i++)
				{
					if(inventory[i]->getName() == item)
					{
						for(j = 0; j < current_room->getCreatures().size() ; j++)
						{
							if(current_room->getCreatures()[j]->getName() == creature)
							{
									for(k = 0; k < creatures.size() ; k++)
									{
										if(creatures[k]->getName() == creature)
										{
											
												if(current_room->getCreatures()[k]->getVulnerability() == item)
												{
													//valid = 1;
													
													cout << "You assault the " << current_room->getCreatures()[k]->getName() << " with the "  << item << endl;
													//current_room->addItem()
												}

											
											
										}

									}						

							}
						}

					}
				}
			}
	  	}
	  
	  	else
	  	{
	  		cout << "error" << endl;
	  	}
	  }
		//END ................!!!!!!!!


		   /////////
    	
    }
    
}
