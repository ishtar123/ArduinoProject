#include <SD.h>
#include <MsTimer2.h>
#include "INIFile.h"
#include "CSVFile.h"

#define SDPINNO 10

void setup() {
  char buf[256];
  
  Serial.begin(9600);
  while(!Serial) {}

  SD.begin(SDPINNO);
  
  INIFile myFile("config/setting.ini");
  myFile.getParam("[setting]", "param1=", buf);
  
  Serial.println(buf);

  // タイマーを設定
  MsTimer2::set(500, timer_tick);
  MsTimer2::start();
}

void loop() {
  
}

void timer_tick(){
  CSVFile mycsv("data.csv");
  char buf[64];

  mycsv.addField("00:00:00");
  sprintf(buf, "%d", analogRead(0));
  mycsv.addField(buf);
  mycsv.nextLine();
}
