#ifndef BASEACTIONS_H
#define BASEACTIONS_H

#include <fstream>
#include <iostream>
#include "Utility.h"
#include "Display.h"
#include "Entity.h"
#include "File.h"
#include "CoordCalc.h"
#include "time.h"

void screenChange(char direction);
void attack(sf::RenderWindow &WINDOW,int range,int MouseX,int MouseY);
void PickUpItem();
void TilesEditor(sf::RenderWindow &WINDOW);
void openInventory(sf::RenderWindow &WINDOW);
void generateWorld(int MaxX,int MaxY);
void drawBrushIcon(Brush &BRUSH);

#endif // BASEACTIONS_H
