#include "INIFile.h"
#include <string.h>

INIFile::INIFile(const char *filename) : TextFile(filename){
}

INIFile::~INIFile(){
}

bool INIFile::getParam(const char * section, const char * param, char * buf)
{
    // 1行分のバッファ
    char line[64];
    // 読み取る行
    int i = 0;
    // セクションを発見したか
    bool found_section = false;

    // i行が存在する間ループ
    while(this->readLine(i++, line, 64)){
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
        if(strcmp(line, section) == 0){
            found_section = true;
        }
    }

    Serial.println("Param not found.");
    return false;
}