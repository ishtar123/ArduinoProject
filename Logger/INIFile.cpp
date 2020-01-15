#include "INIFile.h"
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

INIFile::INIFile(const char *filename){
    strcpy(this->filename, filename);
}

INIFile::~INIFile(){
}

// ファイルのrow行を*lineに格納する。(row >= 1)
// 行が存在しない場合は*line = null, falseを返す。
bool INIFile::getLine(const int row, char *line, const unsigned int bufsize, bool clearEscape){
    File file;
    // バッファインデックス
    int i = 0;
    // 処理中の行
    int rowcount = 1;
    // 今処理している行が目的の行か
    bool found_row = row == 1 ? true : false;

    // ファイルオープン
    file = SD.open(this->filename, FILE_READ);
    if(!file){
        Serial.println("INIFile::getLine\nFile open failed.");
        Serial.println(this->filename);
        return false;
    }

    // 1文字ずつループ
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

        // 目的行の場合
        if(found_row){
            // エスケープ文字除去フラグ=Trueの場合は除去
            if(clearEscape){
                if(readchr != '\t' && readchr != '\n'){
                line[i++] = readchr;
                }
            }
            else{
                line[i++] = readchr; 
            }
        }

        // 改行コードの場合
        if(readchr == '\n' || readchr == EOF){
            // 目的行の終端の場合これ以上処理を継続しない
            if(found_row){
                break;
            }
            
            // 次の行が目的の行か
            if(rowcount + 1 == row){
                found_row = true;
            }
            
            rowcount++;
        }
    }
  
    // 終端文字を挿入
    line[i++] = '\0';
    file.close();

    if(found_row){
        return true;
    }
    else{
        return false;
    }
}

bool INIFile::getParam(const char *section, const char *param, char *buf){
    // 1行分のバッファ
    char line[64];
    // 読み取る行
    int i = 1;
    // セクションを発見したか
    bool found_section = false;

    // i行が存在する間ループ
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
            Serial.println("in");
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
