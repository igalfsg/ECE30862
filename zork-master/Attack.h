#ifndef ATTACK_H_
#define ATTACK_H_
#include <string>
#include <vector>
#include <iostream>

using namespace std;
//using namespace rapidxml;


class Attack {
public:
  Attack();
  string getPrint();
  void setPrint(string newPrint);

  string getObject();
  void setObject(string newObject);

  void setStatus(string newStatus);
  string getStatus();
  
  void addAction(string);
  vector<string> getActions();

 private:
  string status;
  string object;
  string print;
  vector <string> actions;
};

#endif
