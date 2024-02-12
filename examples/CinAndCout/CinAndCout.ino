#include <Cpp_Standard_Library.h>
#include <iostream>

using namespace std;

void setup() {
  Serial.begin(9600);
  cout << "Feed me an integer." << endl;
}

void loop() {
  int foo;
  if (cin >> foo) { 
    cout << "You fed me " << foo << endl;
  }else{
    cin.clear();
    cin.ignore();
  }
}