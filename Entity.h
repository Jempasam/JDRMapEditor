#ifndef ENTITY_H
#define ENTITY_H

#include "CoordCalc.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Object
{
    public:
    int X;
    int Y;
    int displaySizeX=1;
    int displaySizeY=1;
    int tex;
    int rotation=0;
    bool selected=false;
};
struct BrushPart
{
    int tile;
    sf::Vector2i sizeMin,sizeMax;
    std::vector<sf::Vector2i> places;
    int numbermin=1,numbermax=1;
};
struct Brush
{
    std::vector<BrushPart> parts;
    sf::Texture icon;
};

extern std::vector<Object> objects;
extern std::vector<Brush> brushs;

#endif // ENTITY_H
