#include <SD.h>
#include "INIFile.h"

#define SDPINNO 10

void setup() {
  char buf[256];
  
  Serial.begin(9600);
  while(!Serial) {}

  SD.begin(SDPINNO);
  
  INIFile myFile("config/setting.ini");
  myFile.getParam("[setting]", "param1=", buf);
  
  Serial.println(buf);
}

void loop() {
  
}
