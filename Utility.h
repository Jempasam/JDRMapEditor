#ifndef UTILITY_H
#define UTILITY_H

#include "sstream"
#include <string>
#include "iostream"
#include <vector>


int CharToInt(char STRING);
int CharToInt2(char STRING);
std::string IntToString(int INT);
int StringToInt(std::string STRING);
std::string IntToUnit(int NUM);
char IntToChar(int NUM);
std::string AddZero(int NUM,int TYPE);
std::string IntToChars(int NUM);
std::string IntToTerrainChars(int NUM);
int TerrainCharsToInt(std::string STR);
std::vector<std::string> explode(std::string STRING,std::string SEPARATOR,bool KEEP_SEP=false,bool KEEP_EMPTY=false);

#endif // UTILITY_H
