#include <string>
#include <iostream>
using namespace std;

class Base {
public:
   Base( ) { }
   virtual ~Base() { };
   virtual void f1( ) {cout << "B::f1 void" << endl;}
   void f2( ) {cout << "B::f2 void" << endl;}
   void f2(int) {cout << "B::f2 int" << endl;}
   void f3(int) {cout << "B::f3 int" << endl;}
   virtual void callF1( ) {this->f1( );}
private: 
};

class Derived : public Base {
public:
   Derived( ) { }
   virtual ~Derived() { };
   virtual void f1( ) {cout << "D::f1 void" << endl;}
   void f2( ) {cout << "D::f2 void" << endl;}
   virtual void f3(int) {cout << "D::f3 int" << endl;}
   virtual void callF1( ) {this->f1( );}
};

class Derived2 : public Derived {
public:
   Derived2( ) { }
   virtual ~Derived2() { };
   void f3(int) {cout << "D2::f3 int" << endl;}
};

int main(int argc, char * argv[ ]) {
   Base* bP = new Base( );
   Base bO = Base( );
   Derived* dP = new Derived( );
   Derived dO = Derived( );
   Derived2* d2P = new Derived2( );
   Derived2 d2O = Derived2( );

   bP->f1( );
   bP->f2( );
   bP->f2(1);
   bP->callF1( );
   bO.f1( );
   bO.f2( );
   bO.f2(1);
   bO.callF1( );

   bP = dP;
   bO = dO;
   bP->f1( );
   bP->f2( );
   bP->f2(1);
   bP->callF1( );
   bO.f1( );
   bO.f2( );
   bO.f2(1);
   bO.callF1( );

   dP->f1( );
   dP->f2( );
   // dP->f2(1);
   dP->callF1( );
   dO.f1( );
   dO.f2( );
   // dO.f2(1);
   dO.callF1( );

   bP = d2P;
   dP = d2P;
   bO = d2O;
   dO = d2O;

   bP->f3(1);
   dP->f3(1);
   d2P->f3(1);
   bO.f3(1);
   dO.f3(1);
   d2O.f3(1);
}
