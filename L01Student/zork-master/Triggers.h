#ifndef TRIGGERS_H_
#define TRIGGERS_H_
#include <vector>
#include <string>
using namespace std;
typedef struct _conditions{
  string object;
  string status;
  string owner;
  string has;
} Conditions;

class Triggers{
 public:
  Triggers()
    {
      type = "";
      command = "";
    };
  void setType(string);
  void setCondition(string, string, string, string);
  void addAction(string);
  void setPrint(string);   
  void setCommand(string);
  string getHas();
  string getOwner();
  string getStatus();
  string getObject();  
  string getPrint();
  string getCommand();
  string getType();
  Conditions* getCondition();
  vector<string> getActions();

 private:
  string type;
  string print;
  vector<string> actions;
  string command;
  Conditions* condition;
};
#endif
