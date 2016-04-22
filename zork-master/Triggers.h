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
      type = "single";
      command = "";
    };
  string getType();
  void setType(string);

  Conditions* getCondition();
  void setCondition(string, string, string, string);

  vector<string> getActions();
  void addAction(string);

  string getCommand();
  void setCommand(string);

  string getPrint();
  void setPrint(string);

  string getObject();
  //void setObject(string newType);

  string getHas();

  string getOwner();

  string getStatus();

 private:
  string type;
  string print;
  vector<string> actions;
  string command;
  Conditions* condition;
};
#endif
