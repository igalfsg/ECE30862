#include "Set.h"
#include <iostream>
using namespace std;

Set
{

 
 Set::Set (int len){
   int set_thing[len];
   int current_l = 0;
   
 }
 Set::Set (const Set &obj){
  int count = 1; 
 }
 
 
 Set operator+(int b)
 {
   int test = 0;
   int loop = 0;
   for(loop = 0; loop < current_l; loop++){
     if(set_thing[loop] == b){
       test = 1;
     }
   }
   if(test == 0){
    this-> set_thing[current_l]
    current_l ++;
   }
   count++;
 }
 
  Set operator-(int b)
 {
   int test = 0;
   int loop = 0;
   for(loop = 0; loop < current_l; loop++){
     if(set_thing[loop] == b){
       this-> set_thing[loop] = this-> set_thing[loop + 1]
       test = 1;
       current_l -= 1;
     }
     else if (test == 1){
       this-> set_thing[loop] = this-> set_thing[loop + 1]
     }
   }
   count++;
 }

  Set operator&(int b)
 {
  count++;
 }
   Set operator~(int b)
 {
   if (current_l == len){
     current_l = 1;
   }
   else
   {
     int loop;
     for(loop = 0; loop < len; loop++){
       this-> set_thing[loop] = loop;
     }
   }
   count++;
 }
 
 
}

int main(int argc, char * argv[]) {

   Set a = Set(63);
   Set b = Set(63);

   a = a + 4;
   a = a + 8;
   cout << "a w/4, 8: " << a << endl;

   b = b + 8;
   b = b + 16;
   cout << "b w/8, 16: " << b << endl;

   a = a / b;
   cout << "a / b: " << a << endl;

   a = a + 12;
   a = a + 16;
   a = a - 12;
   a = a - 7;
   cout << "a w/4, 16: " << a << endl;

   cout << "~a: " << ~a << endl;
   cout << "a copy count: " << a.getCopyCount( ) << endl;
   cout << "b copy count: " << b.getCopyCount( ) << endl;
}
