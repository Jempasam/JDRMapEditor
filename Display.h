#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "Entity.h"
#include "Tilemap.h"

void displayTexture(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int R=255,int G=255,int B=255,int Alpha=255);
void displayTextureMix(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int R=255,int G=255,int B=255,int Alpha=255);
void displayTexturePart(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int texX,int texY,int texX2,int texY2,int R=255,int G=255,int B=255,int Alpha=255);
void displayTexture2(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int rotation=0,int R=255,int G=255,int B=255,int Alpha=255);
void displayTriangleTexture(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int rotation=0,int R=255,int G=255,int B=255,int Alpha=255,int divideSize=2);
void displaySquare(sf::RenderTarget &WINDOW,int X,int Y,int TX,int TY,int R=255,int G=255,int B=255,int Alpha=255);
void displayCircle(sf::RenderTarget &WINDOW,int X,int Y,int RADIUS,int R=255,int G=255,int B=255,int Alpha=255);
void displayCircleTexture(sf::RenderTarget &WINDOW,int X,int Y,int RADIUS,sf::Texture &TEX,sf::IntRect texRectangle,int R=255,int G=255,int B=255,int Alpha=255);
void displayEntities(sf::RenderWindow &WINDOW);
void displayTextureFromTexMap(sf::RenderWindow &WINDOW,sf::Texture &TEX,int TextureNumber,int X,int Y,int TX,int TY,int R=255,int G=255,int B=255,int Alpha=255);
void displayPlayerLife(sf::RenderWindow &WINDOW);
void displayObjects(sf::RenderTarget &WINDOW,int selecR=0,int selecG=100,int selecB=255,float multiplier=1);
void displayEntitiesLife(sf::RenderWindow &WINDOW);
void displayItemInInventory(sf::RenderWindow &WINDOW,int InventorySlot);
void displayItemsEntities(sf::RenderWindow &WINDOW);
void displayNumber(sf::RenderWindow &WINDOW,std::string STR,int X,int Y,int Size,int R=255,int G=255,int B=255,int Alpha=255);
void displayCollectables(sf::RenderWindow &WINDOW);
void displayDoConnectMap(sf::RenderTarget &TARGET);
void eraseSquare(sf::RenderTarget &WINDOW,int X,int Y,int TX,int TY);
void eraseCircle(sf::RenderTarget &WINDOW,int X,int Y,int RADIUS);
void drawBrushIcon(Brush &BRUSH);
void displayPicText(sf::RenderWindow &WINDOW,std::string Text,int X,int Y,int Size,sf::Texture &TEX,int R=0,int G=0,int B=0,int Alpha=255);
void displayPicText2(sf::RenderWindow &WINDOW,std::string Text,int X,int Y,int Size,sf::Texture &TEX,int R=0,int G=0,int B=0,int Alpha=255);

#endif // DISPLAY_H
