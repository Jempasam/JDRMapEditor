#ifndef TILEMAP_H
#define TILEMAP_H
#include "Texture.h"
#include "Display.h"
#include "array"
#include <iostream>
#include <SFML/Graphics.hpp>

extern std::array<std::array<int,20>,20> WorldTiles,WorldTilesUp;
extern bool WorldDoConnect[20][20];
extern std::string ActualWorld;
extern std::vector<int> tileGoOver;
extern sf::RenderTexture WorldTexture,UpWorldTexture;
extern std::vector<TerrainShot> terrainShots;

void createWorldTexture(std::string TILEMAP);
void createWorldTexture(bool connection=false);
void createUpWorldAt(int x,int y);
void createWorldAt(int x,int y,bool connection=false);
void createWorldAt2(int x,int y,bool connection=false);
void createUpWorldTexture();


#endif // TILEMAP_H
