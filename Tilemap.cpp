#include "Tilemap.h"

std::array<std::array<int,20>,20> WorldTiles,WorldTilesUp;
bool WorldDoConnect[20][20]={false};
std::string ActualWorld;
std::vector<int> tileGoOver;
sf::RenderTexture WorldTexture,UpWorldTexture;
std::vector<TerrainShot> terrainShots;

void createWorldTexture(std::string TILEMAP)
{
    WorldTexture.create(1280,1280);
    int h=0;
    sf::Sprite SPRITE;

    for(int i=0;i<20;i++){
        for(int y=0;y<20;y++){
            /**SPRITE.setTexture(Textures::Tile[TILEMAP[h]-33]);
            SPRITE.setPosition(y*32,i*32);
            SPRITE.setScale(1,1);**/
            std::cout<<TILEMAP[h]-33<<"/";
            //WorldTexture.draw(SPRITE);
            displayTexture(WorldTexture,Textures::Tile[TILEMAP[h]-33],y*64,i*64,64,64);
            h++;
        }
    }
    WorldTexture.display();
}


void createWorldTexture(bool connection)
{
    WorldTexture.create(1280,1280);
    sf::Sprite SPRITE;

    for(int i=0;i<20;i++){
        for(int y=0;y<20;y++){
            /**SPRITE.setTexture(Textures::Tile[WorldTiles[y][i]]);
            SPRITE.setPosition(y*32,i*32);
            SPRITE.setScale(1,1);
            WorldTexture.draw(SPRITE);**/
            //displayTexture(WorldTexture,Textures::Tile[WorldTiles[y][i]],y*64,i*64,64,64);
            createWorldAt2(y,i,connection);

        }
    }
    WorldTexture.display();
}
void createWorldAt(int x,int y,bool connection)
{
    createWorldAt2(x,y,connection);
    if(x>0)
    {
        createWorldAt2(x-1,y,connection);
        if(y>0)createWorldAt2(x-1,y-1,connection);
        if(y<19)createWorldAt2(x-1,y+1,connection);
    }
    if(x<19)
    {
        createWorldAt2(x+1,y,connection);
        if(y>0)createWorldAt2(x+1,y-1,connection);
        if(y<19)createWorldAt2(x+1,y+1,connection);
    }
    if(y>0)createWorldAt2(x,y-1,connection);
    if(y<19)createWorldAt2(x,y+1,connection);
}
void createWorldAt3(int x,int y,bool connection)
{
    displayTexture(WorldTexture,Textures::Tile[WorldTiles[x][y]],x*64,y*64,64,64);

    if(connection&&WorldDoConnect[x][y])
    {
        if(x>0&&y>0)
        {
            int border=WorldTiles[x-1][y-1];
            if(WorldTiles[x-1][y]==border&&
               WorldTiles[x][y-1]==border)
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x-1][y-1]],x*64,y*64,64,64,0);
            }
        }
        if(x>0&&y<19)
        {
            int border=WorldTiles[x-1][y+1];
            if(WorldTiles[x-1][y]==border&&
               WorldTiles[x][y+1]==border)
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x-1][y+1]],x*64,y*64,64,64,3);
            }
        }
        if(x<19&&y>0)
        {
            int border=WorldTiles[x+1][y-1];
            if(WorldTiles[x][y-1]==border&&
               WorldTiles[x+1][y]==border)
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x+1][y-1]],x*64,y*64,64,64,1);
            }
        }
        if(x<19&&y<19)
        {
            int border=WorldTiles[x+1][y+1];
            if(WorldTiles[x][y+1]==border&&
               WorldTiles[x+1][y]==border)
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x+1][y+1]],x*64,y*64,64,64,2);
            }
        }
    }

    WorldTexture.display();
}
void createWorldAt2(int x,int y,bool connection)
{
    eraseSquare(WorldTexture,x*64,y*64,64,64);
    displayTexture(WorldTexture,Textures::Tile[WorldTiles[x][y]],x*64,y*64,64,64);

    if(connection&&WorldDoConnect[x][y])
    {
        if(x>0&&y>0)
        {
            if(WorldTiles[x-1][y]==WorldTiles[x][y-1]&&
               WorldTiles[x-1][y-1]!=WorldTiles[x][y])
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x-1][y]],x*64,y*64,64,64,0);
            }
        }
        if(x>0&&y<19)
        {
            if(WorldTiles[x-1][y]==WorldTiles[x][y+1]&&
               WorldTiles[x-1][y+1]!=WorldTiles[x][y])
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x-1][y]],x*64,y*64,64,64,3);
            }
        }
        if(x<19&&y>0)
        {
            if(WorldTiles[x][y-1]==WorldTiles[x+1][y]&&
               WorldTiles[x+1][y-1]!=WorldTiles[x][y])
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x][y-1]],x*64,y*64,64,64,1);
            }
        }
        if(x<19&&y<19)
        {
            if(WorldTiles[x][y+1]==WorldTiles[x+1][y]&&
               WorldTiles[x+1][y+1]!=WorldTiles[x][y])
            {
                displayTriangleTexture(WorldTexture,Textures::Tile[WorldTiles[x][y+1]],x*64,y*64,64,64,2);
            }
        }
    }

    WorldTexture.display();
}

void createUpWorldTexture()
{
    UpWorldTexture.create(1280,1280);
    UpWorldTexture.clear(sf :: Color :: Transparent);

    for(int i=0;i<20;i++){
        for(int y=0;y<20;y++){
            if(WorldTilesUp[y][i]!=0)
            {
                eraseSquare(UpWorldTexture,y*64,i*64,64,64);
                if(WorldTilesUp[y][i]>=0)
                    displayTexture(UpWorldTexture,Textures::Tile[WorldTilesUp[y][i]],y*64,i*64,64,64);
            }
            UpWorldTexture.display();
        }
    }
}
void createUpWorldAt(int x,int y)
{
    eraseSquare(UpWorldTexture,x*64,y*64,64,64);
    if(WorldTilesUp[x][y]>=0)
        displayTexture(UpWorldTexture,Textures::Tile[WorldTilesUp[x][y]],x*64,y*64,64,64);
    UpWorldTexture.display();
}


