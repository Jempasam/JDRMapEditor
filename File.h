#ifndef FILE_H
#define FILE_H

#include "Tilemap.h"
#include "Utility.h"
#include "Entity.h"
#include "Texture.h"
#include "Display.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

void loadWorld(std::string WORLD);
void loadEntity(std::string WORLD);
void SaveEntities(std::string MAP);
bool LoadEntities(std::string MAP);
void SaveTerrain(std::string MAP);
void loadGenerator(std::string WORLD);
unsigned char getTerrainType(int X,int Y);
void getTreatedFile(std::string filePath,std::stringstream &fileTreated);
void loadBrush(std::ifstream &file);
void saveBrush(std::ofstream &file,Brush &BRUSH);
void saveTerrain(std::ofstream &file);
void loadTerrain(std::ifstream &file,bool connection);
void saveFile(std::ofstream &file);
std::vector<char> loadFile(std::ifstream &file,bool connection);


#endif // FILE_H
