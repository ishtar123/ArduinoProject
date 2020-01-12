#include "INIFile.h"

void setup() {
  char buf[256];
  
  Serial.begin(9600);
  while(!Serial) {}

  INIFile::initSD();

  INIFile myFile("test.ini");
  myFile.getParam("[setting]", "param1=", buf);
  
  Serial.println(buf);
}

void loop() {
  // put your main code here, to run repeatedly:

}
