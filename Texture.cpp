#include "Texture.h"

class AnimatedTexture
{
    std::vector<sf::Texture> Frames;
    int AnimationSpeed;
};
namespace Textures
{
    sf::Texture Player[4];
    std::vector<sf::Texture> Tile;
    std::vector<sf::Texture> Object;
    sf::Texture Life,SelectedSlot,Aim;
    sf::Texture Numbers;
    sf::Texture Background,Fog;
    sf::RenderTexture DrawTexture;
    sf::Texture menu,menu2,photomenu,tilemenu;
    sf::Texture check1,check2,bigcheck1,bigcheck2,backselector;
    sf::Texture bandemenu,bigmenu,bigmenu2,bigmenu3,bigmenu3b;
    sf::Texture leftbutton,rightbutton,plusbutton,minusbutton,brushbutton,piston,data;
    sf::Texture resetter,resetbutton,zoneborder,rangebar,grid;
    sf::Texture bigmissile,missiledoor,loadship,loadscreen,crate;
    sf::Texture screens[3];
    sf::Texture textmap;
};

void loadTexture()
{
    Textures::Life.loadFromFile("Texture/GUI/life.png");
    Textures::Aim.loadFromFile("Texture/GUI/aim.png");
    Textures::Numbers.loadFromFile("Texture/GUI/numbers.png");
    Textures::SelectedSlot.loadFromFile("Texture/GUI/selected.png");
    Textures::Background.loadFromFile("Texture/Overlay/fog2.png");
    Textures::Fog.loadFromFile("Texture/Overlay/fog1.png");
    Textures::menu.loadFromFile("Texture/GUI/menu.png");
    Textures::menu2.loadFromFile("Texture/GUI/menu2.png");
    Textures::check1.loadFromFile("Texture/GUI/checked1.png");
    Textures::check2.loadFromFile("Texture/GUI/checked2.png");
    Textures::bigcheck1.loadFromFile("Texture/GUI/checked1b.png");
    Textures::bigcheck2.loadFromFile("Texture/GUI/checked2b.png");
    Textures::bandemenu.loadFromFile("Texture/GUI/menubande.png");
    Textures::bigmenu.loadFromFile("Texture/GUI/bigmenu.png");
    Textures::bigmenu2.loadFromFile("Texture/GUI/bigmenu2.png");
    Textures::photomenu.loadFromFile("Texture/GUI/photomenu.png");
    Textures::tilemenu.loadFromFile("Texture/GUI/tileeditormenu.png");
    Textures::resetter.loadFromFile("Texture/GUI/resetter.png");
    Textures::resetbutton.loadFromFile("Texture/GUI/resetbutton.png");
    Textures::screens[0].loadFromFile("Texture/GUI/tilescreen.png");
    Textures::screens[1].loadFromFile("Texture/GUI/objectscreen.png");
    Textures::screens[2].loadFromFile("Texture/GUI/brushscreen.png");
    Textures::bigmenu3.loadFromFile("Texture/GUI/bigmenu3.png");
    Textures::bigmenu3b.loadFromFile("Texture/GUI/bigmenu3-b.png");
    Textures::leftbutton.loadFromFile("Texture/GUI/leftbutton.png");
    Textures::rightbutton.loadFromFile("Texture/GUI/rightbutton.png");
    Textures::plusbutton.loadFromFile("Texture/GUI/plusbutton.png");
    Textures::minusbutton.loadFromFile("Texture/GUI/minusbutton.png");
    Textures::zoneborder.loadFromFile("Texture/GUI/zoneborder.png");
    Textures::rangebar.loadFromFile("Texture/GUI/rangebar.png");
    Textures::grid.loadFromFile("Texture/GUI/grid.png");
    Textures::brushbutton.loadFromFile("Texture/GUI/brushbutton.png");
    Textures::piston.loadFromFile("Texture/GUI/piston.png");
    Textures::data.loadFromFile("Texture/GUI/data.png");
    Textures::bigmissile.loadFromFile("Texture/GUI/bigmissile.png");
    Textures::missiledoor.loadFromFile("Texture/GUI/missiledoor.png");
    Textures::backselector.loadFromFile("Texture/GUI/backselector.png");
    Textures::textmap.loadFromFile("Texture/GUI/font.png");
    Textures::loadship.loadFromFile("Texture/GUI/loadship.png");
    Textures::loadscreen.loadFromFile("Texture/GUI/loadscreen.png");
    Textures::crate.loadFromFile("Texture/GUI/crate.png");
}

void loadTileTextures(std::string WORLD)
{
    std::string LINE;std::ifstream fileLoaded("Terrain/"+WORLD+"/TileNumber.data");

    std::getline(fileLoaded,LINE);int TileNumber=StringToInt(LINE);
    for(int i=1;i<TileNumber+1;i++)
    {
        Textures::Tile.push_back(sf::Texture());
        Textures::Tile[Textures::Tile.size()-1].loadFromFile("Terrain/"+WORLD+"/tile/"+IntToString(i)+".png");
    }

    std::getline(fileLoaded,LINE);TileNumber=StringToInt(LINE);
    for(int i=1;i<TileNumber+1;i++)
    {
        Textures::Object.push_back(sf::Texture());
        Textures::Object[Textures::Object.size()-1].loadFromFile("Terrain/"+WORLD+"/entity/"+IntToString(i)+".png");
    }
}
