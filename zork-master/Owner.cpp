#include "Owner.h"
#include <iostream>
#include <string>

using namespace std;

Owner::Owner()
{
	
}

string Owner::getOwner(){
	return owner;
}

void Owner::setOwner(string newOwner){
	this->owner=newOwner;
}

string Owner::getObject(){
	return owner;
}

void Owner::setObject(string newObject)
{
	this->object=newObject;
}

void Owner::has(int newHas){
	this->has_object= newHas;
}
