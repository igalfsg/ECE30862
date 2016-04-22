#include "Conditions.h"
#include <iostream>
#include <string>

using namespace std;

Conditions::Conditions(){}


void Conditions::setOwner(Owner jefe){
	this->owner=jefe;
}
void Conditions::setStatus(string estatus)
{
	this->status=estatus;
}


Owner Conditions::getOwner()
{
	return owner;
}
string Conditions::getStatus()
{
	return status;
}


