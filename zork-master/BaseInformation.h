#ifndef _BASEINFORMATION_H
#define	_BASEINFORMATION_H
#include <string>

using std::string;

class BaseInformation
{
 public:
  BaseInformation()
    {
      name = "";
      description = "";
      //examineStr = "";
      status = "";
    }
  BaseInformation( string n, string desc, string status = "" ) //inspec = "" )
    {
      name = n;
      description = desc;
      //examineStr = inspec;
      status = status;
    }
 
  virtual ~BaseInformation() {};
 
 virtual string toString() const = 0;
  
  virtual string getName() const
  {
    return name;
  }
  
  virtual string getDescription() const
  {
    return description;
  }
  virtual string getStatus() const
  {
    return status;
  }
  /* virtual string examineString() const
  {
    return examineStr;
    }*/

 private:
  string name;
  string description;
  //string examineStr;
  string status;
};
#endif
