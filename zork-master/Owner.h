#ifndef OWNER_H_
#define OWNER_H_
#include <string>
using namespace std;

class Owner {
public:
	Owner();

	string getOwner();
	void setOwner(string);

	string getObject();
	void setObject(string);

	void has(int);

private:
	string owner;
	string object;
	int has_object;
};

#endif