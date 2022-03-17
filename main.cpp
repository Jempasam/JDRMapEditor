#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "File.h"
#include "Entity.h"
#include "Tilemap.h"
#include "Texture.h"
#include "BaseActions.h"
#include "Display.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
int main()
{
    srand(time(NULL));
    int EntitySelected=0;int Editor=0;
    sf::Clock Clock,FPS;sf::Time timeElapsed;bool ButtonPressed=0;
    int FramePerSecond=0,Frame=0;
    bool WeaponInHand=true;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "HorrorGame");

    sf::Texture startmenu;startmenu.loadFromFile("Texture/GUI/startmenu.png");
    displayTexture(window,startmenu,0,0,1000,600);
    window.display();

    loadTexture();
    brushs.push_back(Brush());
    drawBrushIcon(brushs[0]);

    //LOAD TERRAIN
    if(true)
    {
        std::ifstream startfile("Start/start.txt");std::string LINE;
        std::getline(startfile,LINE);
        loadWorld(LINE);
        /**if(!LoadEntities(LINE+"/Save/EntitiesMap/"+MapPos))
           LoadEntities(LINE+"/EntitiesMap/"+MapPos);**/

    }

    float windowSizeChange[2];
    TilesEditor(window);

        window.display();

    return 0;
}
