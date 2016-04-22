#ifndef CONDITIONS_H_
#define CONDITIONS_H_
#include "Owner.h"
#include <string>
//#include "Triggers.h"


using namespace std;

class Conditions{ //: public Triggers {
public:
	Conditions();

	Owner getOwner();
	void setOwner(Owner);

	string getStatus();
	void setStatus(string newStatus);

private:
	string status;
	Owner owner;


};
#endif




