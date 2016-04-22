#include "Conditions.h"
#include <iostream>
#include <string>

using namespace std;

Conditions::Conditions(){}

string Conditions::getStatus()
{
	return status;
}

void Conditions::setStatus(string newStatus)
{
	this->status=newStatus;
}

Owner Conditions::getOwner()
{
	return owner;
}

void Conditions::setOwner(Owner owner){
	this->owner=owner;
}

