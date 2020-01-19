#include "TextFile.h"
#include <Arduino.h>
#include <SD.h>
#include <string.h>

TextFile::TextFile(const char *filename)
{
    // ファイル名をメンバにコピー
    // 終端文字はstrcpyでコピーされない為追加
    this->filename = new char[strlen(filename) + 1];
    strcpy(this->filename, filename);
    this->filename[strlen(this->filename)] = '\0';
}

TextFile::~TextFile()
{
    if(this->filename != nullptr)
    {
        delete this->filename;
    }
}

bool TextFile::open(uint8_t mode)
{
    // ファイルオープン
    if(this->file = SD.open(this->filename, mode))
    {
        this->isFileOpen = true;
        return true;
    }
    else
    {
        this->isFileOpen = false;
        Serial.println("TextFile::open\nFile open failed.");
        return false;
    }
}

char TextFile::getChar()
{
    if(this->isFileOpen) return file.read();
    else return EOF;
}

bool TextFile::close()
{
    // ファイルクローズ
    if(this->isFileOpen)
    {
        file.close();
    }
}

bool TextFile::writeLine(const char *line)
{
    File file;

    // ファイルオープン
    if(file = SD.open(this->filename, FILE_WRITE))
    {
        // 1行書き込み
        file.println(line);
        file.close();
        return true;
    }
    else
    {
        Serial.println("TextFile::writeLine\nFile open failed.");
        file.close();
        return false;
    }
}

bool TextFile::readLine(const int row, char *line, unsigned int bufsize)
{
    int row_count = 0;
    char buf;
    int i = 0;

    if(this->open(FILE_READ))
    {
        // 1文字ずつ読み取り
        while((buf = this->getChar()) != EOF)
        {
            // バッファオーバーフロー回避
            if(bufsize <= i)
            {
                Serial.println("TextFile::readLine\nBuffer Over Flow.");
                file.close();
                return false;
            }

            // 目的行かつ終端文字以外の場合格納
            if(row_count == row && buf != '\r' && buf != '\n') line[i++] = buf;

            // 改行コードの場合++row_count
            if(buf == '\n') ++row_count;

            // 次の行の場合終了
            if(row_count > row) break;
        }

        // 終端文字を格納
        line[i] = '\0';

        this->close();

        return true;
    }
    else
    {
        Serial.println("TextFile::readLine\nFile open failed.");
        return false;
    }
}