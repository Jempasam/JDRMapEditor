#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <fstream>


namespace Textures
{
    extern sf::Texture Player[4];
    extern std::vector<sf::Texture> Tile;
    extern std::vector<sf::Texture> Object;
    extern sf::Texture Life,SelectedSlot,Aim;
    extern sf::Texture Numbers;
    extern sf::Texture Background,Fog;
    extern sf::RenderTexture DrawTexture;
    extern sf::Texture menu,menu2,photomenu,tilemenu;
    extern sf::Texture check1,check2,bigcheck1,bigcheck2,backselector;
    extern sf::Texture bandemenu,bigmenu,bigmenu2,bigmenu3,bigmenu3b;
    extern sf::Texture resetter,resetbutton,zoneborder,rangebar,grid;
    extern sf::Texture leftbutton,rightbutton,plusbutton,minusbutton,brushbutton,piston,data;
    extern sf::Texture bigmissile,missiledoor,loadship,loadscreen,crate;
    extern sf::Texture screens[3];
    extern sf::Texture textmap;
};

struct TerrainShot
{
    sf::Texture worldTex, upWorldTex, entityTex;
    bool groundVisible=false, roofVisible=false, entitisVisible=false;
};
void loadTexture();
void loadTileTextures(std::string WORLD);


#endif // TEXTURE_H
