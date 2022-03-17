#include "File.h"
#include <vector>

void loadWorld(std::string WORLD)
{
    loadTileTextures(WORLD);
    std::string LINE;
    std::ifstream fileLoaded(("Terrain/"+WORLD+"/config.data").c_str());
    if(!fileLoaded) std::cerr<<"ERROR:Wrong World Name";
    else
    {
        ActualWorld=WORLD;
        createWorldTexture();
        createUpWorldTexture();

        fileLoaded.close();
        fileLoaded.open(("Terrain/"+WORLD+"/collide.data").c_str());
    }
}
void loadBrush(std::ifstream &file)
{
    char CHAR;

    Brush newBrush;
    BrushPart newPart;

    while(file.get(CHAR))
    {
        if(CHAR==127)break;

        newPart.numbermin=int(CHAR)*128;
        file.get(CHAR);newPart.numbermin+=int(CHAR);

        file.get(CHAR);newPart.numbermax=int(CHAR)*128;
        file.get(CHAR);newPart.numbermax+=int(CHAR);

        file.get(CHAR);newPart.tile=int(CHAR)*128;
        file.get(CHAR);newPart.tile+=int(CHAR);

        file.get(CHAR);newPart.sizeMax.x=int(CHAR)*128;
        file.get(CHAR);newPart.sizeMax.x+=int(CHAR);
        file.get(CHAR);newPart.sizeMax.y=int(CHAR)*128;
        file.get(CHAR);newPart.sizeMax.y+=int(CHAR);

        file.get(CHAR);newPart.sizeMin.x=int(CHAR)*128;
        file.get(CHAR);newPart.sizeMin.x+=int(CHAR);
        file.get(CHAR);newPart.sizeMin.y=int(CHAR)*128;
        file.get(CHAR);newPart.sizeMin.y+=int(CHAR);

        while(file.get(CHAR))
        {
            if(CHAR==127)break;

            sf::Vector2i newPlace;
            newPlace.x=int(CHAR)*128;
            file.get(CHAR);newPlace.x+=int(CHAR);
            file.get(CHAR);newPlace.y=int(CHAR)*128;
            file.get(CHAR);newPlace.y+=int(CHAR);
            newPart.places.push_back(newPlace);
        }
        newBrush.parts.push_back(newPart);
        newPart.places.clear();
    }
    drawBrushIcon(newBrush);
    brushs.push_back(newBrush);
}
void saveBrush(std::ofstream &file,Brush &BRUSH)
{
    char RETURN;
    for(int i=0;i<BRUSH.parts.size();i++)
    {
        file<<char(BRUSH.parts[i].numbermin/128);
        file<<char(BRUSH.parts[i].numbermin%128);

        file<<char(BRUSH.parts[i].numbermax/128);
        file<<char(BRUSH.parts[i].numbermax%128);

        file<<char(BRUSH.parts[i].tile/128);
        file<<char(BRUSH.parts[i].tile%128);

        file<<char(BRUSH.parts[i].sizeMax.x/128);
        file<<char(BRUSH.parts[i].sizeMax.x%128);
        file<<char(BRUSH.parts[i].sizeMax.y/128);
        file<<char(BRUSH.parts[i].sizeMax.y%128);

        file<<char(BRUSH.parts[i].sizeMin.x/128);
        file<<char(BRUSH.parts[i].sizeMin.x%128);
        file<<char(BRUSH.parts[i].sizeMin.y/128);
        file<<char(BRUSH.parts[i].sizeMin.y%128);

        for(int y=0;y<BRUSH.parts[i].places.size();y++)
        {
            file<<char(BRUSH.parts[i].places[y].x/128);
            file<<char(BRUSH.parts[i].places[y].x%128);
            file<<char(BRUSH.parts[i].places[y].y/128);
            file<<char(BRUSH.parts[i].places[y].y%128);
        }
        file<<char(127);
    }
    file<<char(127);
}
void saveTerrain(std::ofstream &file)
{
    for(int x=0;x<WorldTiles.size();x++)
    {
        for(int y=0;y<WorldTiles.size();y++)
        {
            file<<char(WorldTiles[x][y]/128);
            file<<char(WorldTiles[x][y]%128);
        }
    }
    for(int x=0;x<WorldTilesUp.size();x++)
    {
        for(int y=0;y<WorldTilesUp.size();y++)
        {
            file<<char(WorldTilesUp[x][y]/128);
            file<<char(WorldTilesUp[x][y]%128);
        }
    }
    for(int i=0;i<objects.size();i++)
    {
        file<<char(objects[i].X/128);
        file<<char(objects[i].X%128);
        file<<char(objects[i].Y/128);
        file<<char(objects[i].Y%128);
        file<<char(objects[i].rotation/128);
        file<<char(objects[i].rotation%128);

        file<<char(objects[i].tex/128);
        file<<char(objects[i].tex%128);

        file<<char(objects[i].displaySizeX/128);
        file<<char(objects[i].displaySizeX%128);
        file<<char(objects[i].displaySizeY/128);
        file<<char(objects[i].displaySizeY%128);
    }
    file<<char(127);
}
void loadTerrain(std::ifstream &file,bool connection)
{
    char CHAR;

    /**while(file.get(CHAR))
    {
        if(CHAR==127)break;**/

    for(int x=0;x<WorldTiles.size();x++)
    {
        for(int y=0;y<WorldTiles.size();y++)
        {
            file.get(CHAR);WorldTiles[x][y]=int(CHAR)*128;
            file.get(CHAR);WorldTiles[x][y]+=int(CHAR);
        }
    }
    for(int x=0;x<WorldTilesUp.size();x++)
    {
        for(int y=0;y<WorldTilesUp.size();y++)
        {
            file.get(CHAR);WorldTilesUp[x][y]=int(CHAR)*128;
            file.get(CHAR);WorldTilesUp[x][y]+=int(CHAR);
        }
    }
    objects.clear();
    while(file.get(CHAR))
    {
        Object newObject;
        if(CHAR==127)break;

        newObject.X=int(CHAR)*128;
        file.get(CHAR);newObject.X+=int(CHAR);
        file.get(CHAR);newObject.Y=int(CHAR)*128;
        file.get(CHAR);newObject.Y+=int(CHAR);
        file.get(CHAR);newObject.rotation=int(CHAR)*128;
        file.get(CHAR);newObject.rotation+=int(CHAR);

        file.get(CHAR);newObject.tex=int(CHAR)*128;
        file.get(CHAR);newObject.tex+=int(CHAR);

        file.get(CHAR);newObject.displaySizeX=int(CHAR)*128;
        file.get(CHAR);newObject.displaySizeX+=int(CHAR);
        file.get(CHAR);newObject.displaySizeY=int(CHAR)*128;
        file.get(CHAR);newObject.displaySizeY+=int(CHAR);

        objects.push_back(newObject);
    }
    createUpWorldTexture();
}
std::vector<char> loadFile(std::ifstream &file,bool connection)
{
    std::vector<char> RETURN;
    char CHAR;

    while(file.get(CHAR))
    {
        if(CHAR==1)
        {
            RETURN.push_back(0);
            loadTerrain(file,connection);
        }
        else if(CHAR==2)
        {
            RETURN.push_back(1);
            loadBrush(file);
        }
    }
    return RETURN;
}
unsigned char getTerrainType(int X,int Y)
{
    std::string LINE;
    std::ifstream fileLoaded(("Terrain/"+ActualWorld+"/Save/Map/"+IntToChars(X)+IntToChars(Y)+".trrn").c_str());
    if(!fileLoaded)
    {
        fileLoaded.close();
        fileLoaded.open(("Terrain/"+ActualWorld+"/"+IntToChars(X)+IntToChars(Y)+".trrn").c_str());
        std::cout<<("Terrain/"+ActualWorld+"/Save/Map/"+IntToChars(X)+IntToChars(Y)+".trrn").c_str();
    }

    if(!fileLoaded)return 255;
    else
    {
        std::cout<<"<<L<"<<int(X)<<"/"<<int(Y)<<">L>>";
        for(int i=0;i<62;i++)
        {
            std::getline(fileLoaded,LINE);
        }
        if(std::getline(fileLoaded,LINE))return char(StringToInt(LINE));
        else return char(0);
    }
}
void SaveTerrain(std::string MAP)
{
    std::string LINE;
    std::ofstream fileSaved((MAP+".trrn").c_str());

        for(int i=0;i<20;i++) //SAVED TILEMAP
        {
            for(int y=0;y<20;y++)
            {
            fileSaved<<IntToTerrainChars(WorldTiles[y][i]);
            }
            fileSaved<<"\n";
        }
        fileSaved<<"\n";
        for(int i=0;i<20;i++) //LOAD UPTILEMAP
        {
            for(int y=0;y<20;y++)
            {
            fileSaved<<IntToTerrainChars(WorldTilesUp[y][i]);
            }
            fileSaved<<"\n";
        }
}
void getTreatedFile(std::string filePath,std::stringstream &fileTreated)
{
    std::ifstream file(filePath);
    std::string LINE;
    while(std::getline(file,LINE))
    {
        std::vector<std::string> explodedLine=explode(LINE," ");
        for(int i=0;i<explodedLine.size();i++)
            fileTreated<<explodedLine[i]<<"\n";
    }
}
