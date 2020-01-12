#include "INIFile.h"
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define PINNO 10

INIFile::INIFile(char *filename){
  strcpy(this->filename, filename);
}

INIFile::~INIFile(){
}

bool INIFile::getLine(const int row, char *line, const unsigned int bufsize, bool clearEscape=false){
  File file;
  int i = 0;
  int rowcount = 1;
  bool found_row = row == 1 ? true : false;

  // ファイルオープン
  file = SD.open(this->filename, FILE_READ);
  if(!file){
    Serial.println("INIFile::getLine\nFile open failed.");
    Serial.println(this->filename);
    return false;
  }
  
  while(file.available()){
    // バッファオーバーフロー回避
    if(bufsize + 1 <= i){
      Serial.println("INIFile::getLine\nover buffer size.");
      //Serial.println(i);
      file.close();
      return false;
    }
    
    // 1文字読み取り
    char readchr = file.read();

    // バッファに追加
    if(found_row){
      if(clearEscape){
        if(readchr != '\t' && readchr != '\n'){
          line[i++] = readchr;
        }
      }
      else{
        line[i++] = readchr; 
      }
    }

    // 1行読み取り用処理
    if(readchr == '\n'){
      // 目的行の終端の場合終了
      if(found_row){
        // 終端文字を挿入
        line[i++] = '\0';

        file.close();
        return true;
      }
      
      // 次の行が目的の行か
      if(rowcount + 1 == row){
        found_row = true;
      }
      
      rowcount++;
    }
  }

  file.close();
  Serial.println("INIFile::getLine\nRow not found");
  return false;
}

bool INIFile::getParam(const char *section, const char *param, char *buf){
  char line[64];
  int i = 1;
  bool found_section = false;

  while(this->getLine(i++, line, 64, true)){
    // パラメータを検索
    if(found_section){
      // strstrの戻り値がlineの先頭アドレスと一致する場合一致
      // ex.  line = "abc=4", param="c="
      //      strstr(line, param)=>"c=4"...not null
      if(strstr(line, param) == line){
        // =から終端文字までをコピー
        strncpy(buf, strchr(line, '=') + 1, strlen(line) + 1);
        return true;
      }
      break;
    }
    
    // セクションを検索
    if(strcmp(line, section)){
      found_section = true;
    }
  }

  Serial.println("Param not found.");
  return false;
}

bool INIFile::hasSection(const char *section){
  char line[64];
  int i = 1;

  while(this->getLine(i++, line, 64, true)){
    // セクションを検索
    if(strcmp(line, section)){
      return true;
    }
  }

  Serial.println("Section not found.");
  return false;
}

static bool INIFile::initSD(){
  if(!SD.begin(PINNO)){
    Serial.println("SD initalization failed.");
    return false;
  }
  
  Serial.println("SD initalization done.");
  return true;
}
