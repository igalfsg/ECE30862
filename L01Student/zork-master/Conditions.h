#ifndef CONDITIONS_H_
#define CONDITIONS_H_
#include "Owner.h"
#include <string>


using namespace std;

class Conditions{ 
public:
	Conditions();
	void setOwner(Owner);
	void setStatus(string newStatus);
	
	Owner getOwner();
	string getStatus();
	
private:
	string status;
	Owner owner;
};
#endif




