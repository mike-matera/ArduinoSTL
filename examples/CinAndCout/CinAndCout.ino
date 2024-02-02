#include <Cpp_Standard_Library.h>
#include <ArduinoSTL.h>
#include<Arduino.h>
using namespace std;

void setup() {
  Serial.begin(9600);
  cout << "Feed me an integers." << endl;
  micros()
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