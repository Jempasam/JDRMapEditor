#include "BaseActions.h"

void deselectAll(std::vector<Object> &objectss)
{
    for(int i=0;i<objectss.size();i++)
    {
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            objectss[i].selected=false;
    }
}
void switchBool(bool &BOOL)
{
    if(BOOL)BOOL=0;
    else BOOL=1;
}
void selectObject(sf::RenderWindow &WINDOW,int mouseX, int mouseY)
{
    float windowSizeChange[2];
    windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
    int posX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
    int posY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

    deselectAll(objects);

    for(int i=objects.size()-1;i>=0;i--)
    {
        int Ax=objects[i].X-(objects[i].displaySizeX)/2;
        int Ay=objects[i].Y-(objects[i].displaySizeY)/2;
        int Bx=objects[i].X+(objects[i].displaySizeX)/2;
        int By=objects[i].Y+(objects[i].displaySizeY)/2;

        if((Ax<posX&&posX<Bx)||(Bx<posX&&posX<Ax))
        {
            if((Ay<posY&&posY<By)||(By<posY&&posY<Ay))
            {
                objects[i].selected=true;
                break;
            }
        }
    }
}
void miniMenu(sf::RenderWindow &WINDOW,int mouseX, int mouseY,int selected,int &editorMenu)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);

    sf::Clock Clock;

    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>10)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
        }

        float windowSizeChange[2];
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            int xOffset=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0]-mouseX;
            int yOffset=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1]-mouseY;

            int xOffset2,yOffset2;
            if(xOffset<0)xOffset2=xOffset*-1;
            else xOffset2=xOffset;
            if(yOffset<0)yOffset2=yOffset*-1;
            else yOffset2=yOffset;

            if(xOffset2+yOffset2<10)return;

            if(xOffset2>yOffset2)
            {
                if(xOffset<0)
                {
                    int objectNumber=objects.size();
                    for(int i=0;i<objectNumber;i++)
                    if(objects[i].selected)
                    {
                        objects.push_back(objects[i]);
                        objects[objects.size()-1].X-=10;
                        objects[objects.size()-1].Y-=10;
                        objects[i].selected=false;
                    }
                }
                else
                {
                    editorMenu=1;
                }
            }
            else
            {
                if(yOffset<0)
                {
                    deselectAll(objects);
                    Object newObject;
                    newObject.X=int(mouseX);
                    newObject.Y=int(mouseY);
                    newObject.tex=selected;
                    newObject.displaySizeY=100;
                    newObject.displaySizeX=Textures::Object[selected].getSize().x*100/Textures::Object[selected].getSize().y;
                    newObject.selected=true;
                    objects.push_back(newObject);
                }
                else
                {
                    int objectNumber=objects.size();
                    for(int i=0;i<objectNumber;i++)
                    if(objects[i].selected)
                    {
                        objects.erase(objects.begin()+i);
                        i--;objectNumber--;
                    }
                    deselectAll(objects);
                }
            }
            return;
        }
        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture(WINDOW,Textures::menu,mouseX-100,mouseY-100,200,200);
        WINDOW.display();
    }
}
void miniMorphMenu(sf::RenderWindow &WINDOW,int mouseX, int mouseY,int selected,int &editorMenu)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);

    sf::Clock Clock;

    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event));

        float windowSizeChange[2];
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            int xOffset=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0]-mouseX;
            int yOffset=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1]-mouseY;

            int xOffset2,yOffset2;
            if(xOffset<0)xOffset2=xOffset*-1;
            else xOffset2=xOffset;
            if(yOffset<0)yOffset2=yOffset*-1;
            else yOffset2=yOffset;

            if(xOffset2+yOffset2<30)
            {
                editorMenu=0;
                return;
            }

            if(xOffset2>yOffset2)
            {
                if(xOffset<0)
                {
                    editorMenu=4;
                }
                else
                {
                    editorMenu=5;
                }
            }
            else
            {
                if(yOffset<0)
                {
                    editorMenu=2;
                }
                else
                {
                    editorMenu=3;
                }
            }
            return;
        }
        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture(WINDOW,Textures::menu2,mouseX-100,mouseY-100,200,200);
        WINDOW.display();
    }
}
sf::Texture getJDRTerrainImage()
{
    sf::RenderTexture image;
    image.create(1280,1280);
    createWorldTexture(true);
    createUpWorldTexture();

    displayTexture(image,Textures::Background,0,0,1280,1280);

    sf::Texture WORLDTEXTURE=WorldTexture.getTexture();
    displayTexture(image,WORLDTEXTURE,0,0,1280,1280);

    sf::Texture WORLDUP;WORLDUP=UpWorldTexture.getTexture();
    displayTexture(image,WORLDUP,0,0,1280,1280);

    deselectAll(objects);
    displayObjects(image,255,255,255,2.13);
    image.display();
    return image.getTexture();
}
sf::Texture combineTerrainShot(TerrainShot &terrainshot)
{
    sf::RenderTexture image;
    image.create(1280,1280);

    displayTexture(image,Textures::Background,0,0,1280,1280);

    displayTexture(image,terrainshot.worldTex,0,0,1280,1280);

    displayTexture(image,terrainshot.upWorldTex,0,0,1280,1280);

    displayTexture(image,terrainshot.entityTex,0,0,1280,1280);

    image.display();
    return image.getTexture();
}
TerrainShot getJDRTerrainShot()
{
    TerrainShot newTerrainShot;

    createWorldTexture(true);
    sf::Texture WORLDTEXTURE=WorldTexture.getTexture();
    newTerrainShot.worldTex=WORLDTEXTURE;

    createUpWorldTexture();
    sf::Texture WORLDUP;WORLDUP=UpWorldTexture.getTexture();
    newTerrainShot.upWorldTex=WORLDUP;

    deselectAll(objects);
    sf::RenderTexture WORLDOBJECTS;
    WORLDOBJECTS.create(1280,1280);WORLDOBJECTS.clear(sf::Color::Transparent);
    displayObjects(WORLDOBJECTS,255,255,255,2.13);WORLDOBJECTS.display();
    newTerrainShot.entityTex=WORLDOBJECTS.getTexture();

    return newTerrainShot;
}
void saveJDRTerrainImage()
{
    std::string filename="imagemap/map";
    filename+=IntToString((int)time(0));filename+=".png";

    getJDRTerrainImage().copyToImage().saveToFile(filename);
}
bool loadMenu(sf::RenderWindow &WINDOW)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);

    double windowSizeChange[2];
    int mouseX,mouseY;
    bool returnbool=false;
    windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
    WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
    mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
    mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

    bool ButtonPressed;

    std::string name="name";
    bool textSelected=false;

    sf::Clock Clock;

    int menuY=436;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY+=30;
        if(menuY>=546)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }
    menuY=546;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY+=30;
        if(menuY>=1006)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,menuY,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }

    menuY=600;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY-=30;
        if(menuY<=0)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::loadscreen,512,menuY,488,600);

        WINDOW.display();
    }

    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
            if (textSelected && event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::A<=event.key.code && event.key.code<=sf::Keyboard::Z
                   &&name.size()<=10)
                {
                    name+=char(int(event.key.code)+97);
                }
                else if(event.key.code==sf::Keyboard::Space
                        &&name.size()<=10)
                {
                    name+=' ';
                }
                else if(event.key.code==sf::Keyboard::Subtract||
                        event.key.code==sf::Keyboard::Num6
                        &&name.size()<=10)
                {
                    name+='-';
                }
                else if(event.key.code==sf::Keyboard::BackSpace)
                {
                    if(name.size()>0)name.erase(name.begin()+name.size()-1);
                }
            }
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
        mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::loadscreen,512,0,488,600);

        displayPicText2(WINDOW,name,617,73,30,Textures::textmap,205,243,245);
        if(textSelected)
            displaySquare(WINDOW,617,73,name.size()*24+6,30,205,243,245,100);

        if(!textSelected&&sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!ButtonPressed)break;
        if(!textSelected&&sf::Keyboard::isKeyPressed(sf::Keyboard::U)&&!ButtonPressed)
        {returnbool=true;break;}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&&!ButtonPressed)
        {
            std::ifstream loadfile("Save/"+name+".sjdr");
            std::vector<char> loadData=loadFile(loadfile,true);

            menuY=600;
            while(WINDOW.isOpen())
            if(Clock.getElapsedTime().asMilliseconds()>15)
            {
                Clock.restart();
                sf::Event event;
                while (WINDOW.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        WINDOW.close();
                    if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
                    {
                        ButtonPressed=0;
                    }
                }
                menuY-=30;
                if(menuY<=-600)break;

                displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
                displayTexture(WINDOW,Textures::loadscreen,512,0,488,600);

                if(menuY<=300)
                {
                    int advance=400-(menuY+100);
                    std::cout<<"\n"<<advance*loadData.size()/500;
                    for(int icase=0;icase<loadData.size();icase++)
                    {
                        if(advance*loadData.size()/500>=icase)
                        {
                            if(loadData[icase]==0)
                            {
                                displayTexture(WINDOW,Textures::crate,250,500-500*icase/loadData.size(),100,100);
                            }
                            else if(loadData[icase]==1)
                            {
                                displayTexture(WINDOW,Textures::crate,260,500-500*icase/loadData.size(),80,80);
                            }
                        }
                    }
                }

                displayTexture(WINDOW,Textures::loadship,0,menuY,600,600);

                WINDOW.display();
            }
            menuY=250;
            while(WINDOW.isOpen())
            if(Clock.getElapsedTime().asMilliseconds()>15)
            {
                Clock.restart();
                sf::Event event;
                while (WINDOW.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        WINDOW.close();
                    if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
                    {
                        ButtonPressed=0;
                    }
                }
                menuY-=20;
                if(menuY<=-270)break;

                displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
                displayTexture(WINDOW,Textures::loadscreen,512,0,488,600);

                for(int icase=0;icase<loadData.size();icase++)
                {
                        if(loadData[icase]==0)
                        {
                            displayTexture(WINDOW,Textures::crate,menuY,500-500*icase/loadData.size(),100,100);
                        }
                        else if(loadData[icase]==1)
                        {
                            displayTexture(WINDOW,Textures::crate,menuY+10,500-500*icase/loadData.size(),80,80);
                        }
                }

                WINDOW.display();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!ButtonPressed)
        {
            if(textSelected&&name=="")name="name";
            textSelected=false;
            if(617<=mouseX&&mouseX<=617+name.size()*24+6 && 73<=mouseY&&mouseY<=103)
            {
                std::cout<<"hey";
                textSelected=true;
            }
            ButtonPressed=1;
        }

        WINDOW.display();
    }
    menuY=0;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY+=30;
        if(menuY>=600)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::loadscreen,512,menuY,488,600);

        WINDOW.display();
    }
    menuY=1006;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY-=30;
        if(menuY<=546)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,menuY,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }
    menuY=546;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY-=30;
        if(menuY<=436)break;

        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }
    return returnbool;

}
void saveMenu(sf::RenderWindow &WINDOW)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);

    double windowSizeChange[2];
    int mouseX,mouseY;
    windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
    WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
    mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
    mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

    bool ButtonPressed;

    sf::Clock Clock;

    int menuY=600;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY-=40;
        if(menuY<=-100)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,menuY,1000,700,2);

        WINDOW.display();
    }
    menuY=1006;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY-=30;
        if(menuY<=546)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,menuY,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }
    menuY=546;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY-=30;
        if(menuY<=436)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }

    int BrushSelected=0;
    std::vector<int> brushstosave;
    bool doSaveTerrain=false;
    std::string name="name";
    bool textSelected=false;

    sf::Texture worldtex=WorldTexture.getTexture();
    sf::Texture upworldtex=UpWorldTexture.getTexture();

    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                BrushSelected+=event.mouseWheel.delta;
                if(BrushSelected<0)BrushSelected=brushs.size()-1;
                if(BrushSelected>=brushs.size())BrushSelected=0;
            }
            if (textSelected && event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::A<=event.key.code && event.key.code<=sf::Keyboard::Z
                   &&name.size()<=10)
                {
                    name+=char(int(event.key.code)+97);
                }
                else if(event.key.code==sf::Keyboard::Space
                        &&name.size()<=10)
                {
                    name+=' ';
                }
                else if(event.key.code==sf::Keyboard::Subtract||
                        event.key.code==sf::Keyboard::Num6
                        &&name.size()<=10)
                {
                    name+='-';
                }
                else if(event.key.code==sf::Keyboard::BackSpace)
                {
                    if(name.size()>0)name.erase(name.begin()+name.size()-1);
                }
            }
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
        mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

        if(!textSelected&&sf::Keyboard::isKeyPressed(sf::Keyboard::U)&&!ButtonPressed)break;
        if(!textSelected&&sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!ButtonPressed)
        {
            if(loadMenu(WINDOW))break;
        }


        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
        if(doSaveTerrain)
        {
            displayTexture(WINDOW,worldtex,743,49,100,100);
            displayTexture(WINDOW,upworldtex,743,49,100,100);
        }
        for(int i=0;i<brushstosave.size();i++)
        {
            displayTexture(WINDOW,Textures::backselector,748,145+i*30,90,90);
            displayTexture(WINDOW,brushs[brushstosave[i]].icon,763,160+i*30,60,60);
        }


        displayTexture(WINDOW,Textures::missiledoor,524,44,216,373);
        displayPicText(WINDOW,name,881,235-(name.size()*16),40,Textures::textmap);
        if(textSelected)
            displaySquare(WINDOW,881,235-(name.size()*16),40,(name.size()*33),0,100,255,100);

        if(brushs.size()>=5)
        {
            displayTexture(WINDOW,Textures::backselector,25,425,150,150);
            if(BrushSelected>1) displayTexture(WINDOW,brushs[BrushSelected-2].icon,50,450,100,100);
            else displayTexture(WINDOW,brushs[brushs.size()-2+BrushSelected].icon,50,450,100,100);
        }
        if(brushs.size()>=2)
        {
            displayTexture(WINDOW,Textures::backselector,25,325,150,150);
            if(BrushSelected>0) displayTexture(WINDOW,brushs[BrushSelected-1].icon,50,350,100,100);
            else displayTexture(WINDOW,brushs[brushs.size()-1].icon,50,350,100,100);
        }
        displayTexture(WINDOW,Textures::backselector,25,225,150,150);
        displayTexture(WINDOW,brushs[BrushSelected].icon,50,250,100,100);
        if(brushs.size()>=2)
        {
            displayTexture(WINDOW,Textures::backselector,25,125,150,150);
            if(BrushSelected<brushs.size()-1) displayTexture(WINDOW,brushs[BrushSelected+1].icon,50,150,100,100);
            else displayTexture(WINDOW,brushs[0].icon,50,150,100,100);
        }
        if(brushs.size()>=5)
        {
            displayTexture(WINDOW,Textures::backselector,25,25,150,150);
            if(BrushSelected<brushs.size()-2) displayTexture(WINDOW,brushs[BrushSelected+2].icon,50,50,100,100);
            else displayTexture(WINDOW,brushs[+BrushSelected-brushs.size()+2].icon,50,50,100,100);
        }
        displayTexture(WINDOW,Textures::rightbutton,160,250,100,100);

        if(!doSaveTerrain)
        {
            displayTexture(WINDOW,worldtex,270,225,150,150);
            displayTexture(WINDOW,upworldtex,270,225,150,150);
            displayTexture(WINDOW,Textures::rightbutton,430,250,100,100);
        }
        else
        {
            displayTexture(WINDOW,Textures::leftbutton,430,250,100,100);
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!ButtonPressed)
        {
            if(textSelected&&name=="")name="name";
            textSelected=false;
            if(160<=mouseX&&mouseX<=260 && 250<=mouseY&&mouseY<=350)
            {
                brushstosave.push_back(BrushSelected);
                ButtonPressed=1;
            }
            else if(430<=mouseX&&mouseX<=530 && 250<=mouseY&&mouseY<=350)
            {
                if(doSaveTerrain)doSaveTerrain=false;
                else doSaveTerrain=true;
                ButtonPressed=1;
            }
            else if(881<=mouseX&&mouseX<=921 && 235-(name.size()*16)<=mouseY&&mouseY<=235+(name.size()*16))
            {
                textSelected=true;
                ButtonPressed=1;
            }
            else if(701<=mouseX && 458<=mouseY&&mouseY<=557)
            {
                menuY=436;
                while(WINDOW.isOpen())
                if(Clock.getElapsedTime().asMilliseconds()>15)
                {
                    Clock.restart();
                    sf::Event event;
                    while (WINDOW.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            WINDOW.close();
                        if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
                        {
                            ButtonPressed=0;
                        }
                    }
                    menuY+=30;
                    if(menuY>=546)break;

                    displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
                    displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
                    displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

                    WINDOW.display();
                }
                menuY=-100;
                while(WINDOW.isOpen())
                if(Clock.getElapsedTime().asMilliseconds()>15)
                {
                    Clock.restart();
                    sf::Event event;
                    while (WINDOW.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            WINDOW.close();
                        if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
                        {
                            ButtonPressed=0;
                        }
                    }
                    menuY+=30;
                    if(menuY>=1000)break;

                    displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);

                    displayTexture(WINDOW,Textures::bigmissile,546,menuY,454,700);
                    displayTexture(WINDOW,Textures::missiledoor,634,menuY+144,216,373);
                    displayTexture(WINDOW,Textures::bigmissile,546,menuY-1100,454,700);
                    displayTexture(WINDOW,Textures::missiledoor,634,menuY-956,216,373);

                    WINDOW.display();
                }
                menuY=546;
                while(WINDOW.isOpen())
                if(Clock.getElapsedTime().asMilliseconds()>15)
                {
                    Clock.restart();
                    sf::Event event;
                    while (WINDOW.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            WINDOW.close();
                        if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
                        {
                            ButtonPressed=0;
                        }
                    }
                    menuY-=30;
                    if(menuY<=436)break;

                    displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
                    displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
                    displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

                    WINDOW.display();
                }
                std::ofstream saveFile("Save/"+name+".sjdr");

                if(doSaveTerrain)
                {
                    saveFile<<char(1);
                    saveTerrain(saveFile);
                }

                for(int ibrush=0;ibrush<brushstosave.size();ibrush++)
                {
                    saveFile<<char(2);
                    saveBrush(saveFile,brushs[brushstosave[ibrush]]);
                }
            }
        }

        WINDOW.display();
    }

    menuY=436;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY+=30;
        if(menuY>=546)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,546,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }
    menuY=546;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY+=30;
        if(menuY>=1006)break;

        displayTexture2(WINDOW,Textures::bigmenu,0,-100,1000,700,2);
        displayTexture(WINDOW,Textures::bigmissile,menuY,-100,454,700);
        displayTexture(WINDOW,Textures::missiledoor,menuY+88,44,216,373);

        WINDOW.display();
    }

    menuY=-100;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        menuY+=40;
        if(menuY>=600)break;

        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture2(WINDOW,Textures::bigmenu,0,menuY,1000,700,2);

        WINDOW.display();
    }
}
void TerrainShotMasker(sf::RenderWindow &WINDOW,int terrainshot)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);

    double windowSizeChange[2];
    int mouseX,mouseY;
    bool ButtonPressed;
    std::vector<sf::Vector2i> shapesPos;
    std::vector<int> shapesSize;
    std::vector<int> brushType;

    sf::RenderTexture groundRdTex,roofRdTex,entityRdTex;
    groundRdTex.create(1280,1280);displayTexture(groundRdTex,terrainShots[terrainshot].worldTex,0,0,1280,1280);
    roofRdTex.create(1280,1280);displayTexture(roofRdTex,terrainShots[terrainshot].upWorldTex,0,0,1280,1280);
    entityRdTex.create(1280,1280);displayTexture(entityRdTex,terrainShots[terrainshot].entityTex,0,0,1280,1280);
    groundRdTex.display();roofRdTex.display();entityRdTex.display();

    sf::Texture groundTex,roofTex,entityTex;
    groundTex=groundRdTex.getTexture();
    roofTex=roofRdTex.getTexture();
    entityTex=entityRdTex.getTexture();

    sf::Clock Clock;

    int menuX=-1000;
    int brushSize=100;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        menuX+=60;
        if(menuX>0)break;

        displayTexture(WINDOW,Textures::bigmenu2,menuX,0,1100,600);
        displayTexture(WINDOW,groundTex,menuX+15,19,563,563);
        displayTexture(WINDOW,roofTex,menuX+15,19,563,563);
        displayTexture(WINDOW,entityTex,menuX+15,19,563,563);
        WINDOW.display();
    }
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if (event.type == sf::Event::MouseWheelMoved)
            {
                brushSize+=event.mouseWheel.delta*10;
                if(brushSize<10)brushSize=10;
                else if(brushSize>1000)brushSize=1000;
            }
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
        mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

        displayTexture(WINDOW,Textures::bigmenu2,0,0,1100,600);
        displayTexture(WINDOW,groundTex,15,19,563,563);
        displayTexture(WINDOW,roofTex,15,19,563,563);
        displayTexture(WINDOW,entityTex,15,19,563,563);
        displayTexture(WINDOW,Textures::resetbutton,595,7,60,586);
        displayTexture2(WINDOW,Textures::resetbutton,933,7,60,586,2);

        if(15<mouseX&&mouseX<578 && 19<mouseY&&mouseY<582)
        {
            for(int i=0;i<shapesPos.size();i++)
            {
                if(brushType[i]==0)
                    displayCircleTexture(WINDOW,shapesPos[i].x-shapesSize[i],shapesPos[i].y-shapesSize[i],shapesSize[i],Textures::bigmenu2,
                                     sf::IntRect(shapesPos[i].x-shapesSize[i], shapesPos[i].y-shapesSize[i],
                                                 shapesSize[i]*2, shapesSize[i]*2));
                else if(brushType[i]==1)
                    displayCircleTexture(WINDOW,shapesPos[i].x-shapesSize[i],shapesPos[i].y-shapesSize[i],shapesSize[i],terrainShots[terrainshot].worldTex,
                                     sf::IntRect((shapesPos[i].x-shapesSize[i]-15)*1280/563, (shapesPos[i].y-shapesSize[i]-19)*1280/563,
                                                 shapesSize[i]*1280/563*2, shapesSize[i]*1280/563*2));
            }
            displayCircle(WINDOW,mouseX-brushSize,mouseY-brushSize,brushSize,100,150,255,100);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                shapesPos.push_back(sf::Vector2i(mouseX,mouseY));
                shapesSize.push_back(brushSize);
                brushType.push_back(0);
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                shapesPos.push_back(sf::Vector2i(mouseX,mouseY));
                shapesSize.push_back(brushSize);
                brushType.push_back(1);
            }

            if(shapesPos.size()>10||
               (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&sf::Mouse::isButtonPressed(sf::Mouse::Right)))
            {
                for(int i=0;i<shapesPos.size();i++)
                {
                    if(brushType[i]==0)
                    {
                        eraseCircle(groundRdTex,(shapesPos[i].x-shapesSize[i]-15)*1280/563,(shapesPos[i].y-shapesSize[i]-19)*1280/563,
                            shapesSize[i]*1280/563);
                        eraseCircle(roofRdTex,(shapesPos[i].x-shapesSize[i]-15)*1280/563,(shapesPos[i].y-shapesSize[i]-19)*1280/563,
                            shapesSize[i]*1280/563);
                        eraseCircle(entityRdTex,(shapesPos[i].x-shapesSize[i]-15)*1280/563,(shapesPos[i].y-shapesSize[i]-19)*1280/563,
                            shapesSize[i]*1280/563);
                    }
                    else if(brushType[i]==1)
                    {
                        displayCircleTexture(groundRdTex,(shapesPos[i].x-shapesSize[i]-15)*1280/563,(shapesPos[i].y-shapesSize[i]-19)*1280/563,
                            shapesSize[i]*1280/563,terrainShots[terrainshot].worldTex,
                            sf::IntRect((shapesPos[i].x-shapesSize[i]-15)*1280/563,
                                        (shapesPos[i].y-shapesSize[i]-19)*1280/563,
                                        shapesSize[i]*1280/563*2, shapesSize[i]*1280/563*2));

                        displayCircleTexture(roofRdTex,(shapesPos[i].x-shapesSize[i]-15)*1280/563,(shapesPos[i].y-shapesSize[i]-19)*1280/563,
                            shapesSize[i]*1280/563,terrainShots[terrainshot].upWorldTex,
                            sf::IntRect((shapesPos[i].x-shapesSize[i]-15)*1280/563,
                                        (shapesPos[i].y-shapesSize[i]-19)*1280/563,
                                        shapesSize[i]*1280/563*2, shapesSize[i]*1280/5635*2));

                        displayCircleTexture(entityRdTex,(shapesPos[i].x-shapesSize[i]-15)*1280/563,(shapesPos[i].y-shapesSize[i]-19)*1280/563,
                            shapesSize[i]*1280/563,terrainShots[terrainshot].entityTex,
                            sf::IntRect((shapesPos[i].x-shapesSize[i]-15)*1280/563,
                                        (shapesPos[i].y-shapesSize[i]-19)*1280/563,
                                        shapesSize[i]*1280/563*2, shapesSize[i]*1280/563*2));
                    }
                }
                groundRdTex.display();roofRdTex.display();entityRdTex.display();

                groundTex=groundRdTex.getTexture();
                roofTex=roofRdTex.getTexture();
                entityTex=entityRdTex.getTexture();
                shapesPos.clear();shapesSize.clear();brushType.clear();
            }
        }
        WINDOW.display();
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&
           595<mouseX&&mouseX<655 && 7<mouseY&&mouseY<593)
        {

            int menuposx=0;
            while(WINDOW.isOpen())
            if(Clock.getElapsedTime().asMilliseconds()>20)
            {
                Clock.restart();
                sf::Event event;
                while (WINDOW.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        WINDOW.close();
                }
                menuposx+=20;
                displayTexture(WINDOW,Textures::resetter,0,-300+menuposx,600,300);
                displayTexture2(WINDOW,Textures::resetter,0,600-menuposx,600,300,2);
                WINDOW.display();
                if(menuposx>300)break;
            }

            groundRdTex.clear(sf::Color::Transparent);
            roofRdTex.clear(sf::Color::Transparent);
            entityRdTex.clear(sf::Color::Transparent);
            displayTexture(groundRdTex,terrainShots[terrainshot].worldTex,0,0,1280,1280);
            displayTexture(roofRdTex,terrainShots[terrainshot].upWorldTex,0,0,1280,1280);
            displayTexture(entityRdTex,terrainShots[terrainshot].entityTex,0,0,1280,1280);
            groundRdTex.display();roofRdTex.display();entityRdTex.display();

            groundTex=groundRdTex.getTexture();
            roofTex=roofRdTex.getTexture();
            entityTex=entityRdTex.getTexture();

            menuposx=300;
            while(WINDOW.isOpen())
            if(Clock.getElapsedTime().asMilliseconds()>20)
            {
                Clock.restart();
                sf::Event event;
                while (WINDOW.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        WINDOW.close();
                }
                menuposx-=20;
                displayTexture(WINDOW,Textures::bigmenu2,0,0,1100,600);
                displayTexture(WINDOW,groundTex,15,19,563,563);
                displayTexture(WINDOW,roofTex,15,19,563,563);
                displayTexture(WINDOW,entityTex,15,19,563,563);
                displayTexture(WINDOW,Textures::resetbutton,595,7,60,586);
                displayTexture2(WINDOW,Textures::resetbutton,933,7,60,586,2);
                displayTexture(WINDOW,Textures::resetter,0,-300+menuposx,600,300);
                displayTexture2(WINDOW,Textures::resetter,0,600-menuposx,600,300,2);
                WINDOW.display();
                if(menuposx<0)break;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&
           933<mouseX&&mouseX<993 && 7<mouseY&&mouseY<593)break;
    }

    terrainShots[terrainshot].worldTex=groundRdTex.getTexture();
    terrainShots[terrainshot].upWorldTex=roofRdTex.getTexture();
    terrainShots[terrainshot].entityTex=entityRdTex.getTexture();

    menuX=0;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        menuX-=60;
        if(menuX<-1000)break;

        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture(WINDOW,Textures::bigmenu2,menuX,0,1100,600);
        displayTexture(WINDOW,groundTex,menuX+15,19,563,563);
        displayTexture(WINDOW,roofTex,menuX+15,19,563,563);
        displayTexture(WINDOW,entityTex,menuX+15,19,563,563);
        WINDOW.display();
    }
}
void terrainShotMenu(sf::RenderWindow &WINDOW,int shotnum)
{
    double windowSizeChange[2];
    windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;

    int menuX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
    int menuY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

    int mouseX,mouseY;

    int menuYOffset=0;if(menuY>300)menuYOffset=-150;

    sf::Clock Clock;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));

        mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

        displayTexture(WINDOW,Textures::photomenu,menuX-150,menuY+menuYOffset,150,150);

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if(menuX-148<mouseX&&mouseX<menuX-3)
            {
                if(menuY+14+menuYOffset<mouseY&&
                   mouseY<menuY+134+menuYOffset)
                {
                    if(mouseY<menuY+38+menuYOffset)
                    {
                        terrainShots.erase(terrainShots.begin()+shotnum);
                    }
                    else if(mouseY>menuY+110+menuYOffset)TerrainShotMasker(WINDOW,shotnum);
                    else if(mouseY>menuY+47+menuYOffset&&
                            mouseY<menuY+71+menuYOffset)
                    {
                        terrainShots.push_back(terrainShots[shotnum]);
                    }

                    else if(mouseY>menuY+80+menuYOffset&&
                            mouseY<menuY+101+menuYOffset)
                    {
                        std::string filename="imagemap/shot";
                        filename+=IntToString((int)time(0));filename+=".png";
                        combineTerrainShot(terrainShots[shotnum]).copyToImage().saveToFile(filename);
                    }
                }
            }
            return;
        }

        WINDOW.display();
    }
}
void saveTerrainShot(sf::RenderWindow &WINDOW)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);
    TerrainShot terrainshot=getJDRTerrainShot();
    sf::Texture terrainpicture=combineTerrainShot(terrainshot);

    int upspeed=1;
    int flashopacity=250;
    sf::Clock Clock;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        upspeed+=upspeed/4+1;
        displayTexture(WINDOW,screen,0,0,1000,600);
        displaySquare(WINDOW,0,0,1000,600,0,0,0,flashopacity/2);
        displayTexture(WINDOW,terrainpicture,0,0-upspeed,600,600,255,255,255,255);

        displaySquare(WINDOW,0,0,1000,600,255,255,255,flashopacity);
        if(flashopacity>0)flashopacity-=10;
        if(upspeed>600)
        {
            terrainShots.push_back(terrainshot);
            return;
        }
        WINDOW.display();
    }
}
void displayZoneSelection(sf::RenderWindow &WINDOW,int posX,int posY,int sizeX,int sizeY,int &Ax,int &Ay,int &Bx,int &By,int &movingborder,int R=0,int G=100,int B=255,bool background=true)
{
    float casesizex=sizeX*1.00/22, casesizey=sizeY*1.00/22;
    if(background)displayTexture(WINDOW,Textures::grid,posX,posY,sizeX,sizeY);

    displaySquare(WINDOW,posX+casesizex*(Ax+5)*2,posY+casesizey*(Ay+5)*2,
                  2*(Bx-Ax+1)*casesizex,2*(By-Ay+1)*casesizey,
                  R,G,B,100);

    displayTexture(WINDOW,Textures::zoneborder,casesizex*(Ax*2+9)+posX,casesizey*(Ay*2+9)+posY,casesizex*4,casesizey*4);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(Bx*2+9)+posX,casesizey*(By*2+9)+posY,casesizex*4,casesizey*4,2);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(Ax*2+9)+posX,casesizey*(By*2+9)+posY,casesizex*4,casesizey*4,3);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(Bx*2+9)+posX,casesizey*(Ay*2+9)+posY,casesizex*4,casesizey*4,1);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(movingborder==-1)
        {
            movingborder=-2;
            int windowSizeChange[2];
            windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
            WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
            int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
            int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

            if(casesizex*(Ax*2+9)+posX<mouseX&&mouseX<casesizex*(Ax*2+9+2)+posX&&
               casesizey*(Ay*2+9)+posY<mouseY&&mouseY<casesizey*(Ay*2+9+2)+posY)
            {
                std::cout<<time(0)<<":haut-gauche\n";
                movingborder=0;
            }
            else if(casesizex*(Bx*2+9+2)+posX<mouseX&&mouseX<casesizex*(Bx*2+9+4)+posX&&
               casesizey*(By*2+9+2)+posY<mouseY&&mouseY<casesizey*(By*2+9+4)+posY)
            {
                std::cout<<time(0)<<":bas-droite\n";
                movingborder=1;
            }
            else if(casesizex*(Ax*2+9)+posX<mouseX&&mouseX<casesizex*(Ax*2+9+2)+posX&&
               casesizey*(By*2+9+2)+posY<mouseY&&mouseY<casesizey*(By*2+9+4)+posY)
            {
                std::cout<<time(0)<<":bas-gauche\n";
                movingborder=2;
            }
            else if(casesizex*(Bx*2+9+2)+posX<mouseX&&mouseX<casesizex*(Bx*2+9+4)+posX&&
               casesizey*(Ay*2+9)+posY<mouseY&&mouseY<casesizey*(Ay*2+9+2)+posY)
            {
                std::cout<<time(0)<<":haut-droite\n";
                movingborder=3;
            }
        }
        else if(movingborder!=-2)
        {
            int windowSizeChange[2];
            windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
            WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
            int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
            int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

            if(movingborder==0||movingborder==2)Ax=((mouseX-posX)*1.00/casesizex-9)/2;
            else Bx=((mouseX-posX)*1.00/casesizex-9)/2-1;

            if(movingborder==0||movingborder==3)Ay=((mouseY-posY)*1.00/casesizey-9)/2;
            else By=((mouseY-posY)*1.00/casesizey-9)/2-1;
        }
    }
    else
    {
        movingborder=-1;
    }
}
void displayZoneSelectionPair(sf::RenderWindow &WINDOW,int posX,int posY,int sizeX,int sizeY,int &minx,int &miny,int &maxx,int &maxy,int &movingborder,bool background=true,int mode=0)
{
    float casesizex=sizeX*1.00/22, casesizey=sizeY*1.00/22;
    if(background)displayTexture(WINDOW,Textures::grid,posX,posY,sizeX,sizeY);

    displaySquare(WINDOW,posX+casesizex*(maxx*-1+5)*2,posY+casesizey*(maxy*-1+5)*2,
                  2*(maxx-maxx*-1+1)*casesizex,2*(maxy-maxy*-1+1)*casesizey,
                  0,100,255,100);

    if(mode==1)
    displaySquare(WINDOW,posX+casesizex*(minx*-1+5)*2,posY+casesizey*(miny*-1+5)*2,
                  2*(minx-minx*-1+1)*casesizex,2*(miny-miny*-1+1)*casesizey,
                  100,100,100,150);
    if(mode==0)
    if(minx>0&&miny>0)
    displayTexturePart(WINDOW,Textures::grid,posX+casesizex*(minx*-1+5+1)*2,posY+casesizey*(miny*-1+5+1)*2,
                  2*(minx-minx*-1+1-2)*casesizex,2*(miny-miny*-1+1-2)*casesizey,
                       105.5-minx*21.0+21,105.5-miny*21.0+21,125.5+minx*21.0-21,125.5+miny*21.0-21);

    displayTexture(WINDOW,Textures::zoneborder,casesizex*(maxx*-2+8)+posX,casesizey*(maxy*-2+8)+posY,casesizex*4,casesizey*4);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(maxx*2+10)+posX,casesizey*(maxy*2+10)+posY,casesizex*4,casesizey*4,2);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(maxx*-2+8)+posX,casesizey*(maxy*2+10)+posY,casesizex*4,casesizey*4,3);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(maxx*2+10)+posX,casesizey*(maxy*-2+8)+posY,casesizex*4,casesizey*4,1);

    displayTexture(WINDOW,Textures::zoneborder,casesizex*(minx*-2+9)+posX,casesizey*(miny*-2+9)+posY,casesizex*4,casesizey*4);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(minx*2+9)+posX,casesizey*(miny*2+9)+posY,casesizex*4,casesizey*4,2);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(minx*-2+9)+posX,casesizey*(miny*2+9)+posY,casesizex*4,casesizey*4,3);
    displayTexture2(WINDOW,Textures::zoneborder,casesizex*(minx*2+9)+posX,casesizey*(miny*-2+9)+posY,casesizex*4,casesizey*4,1);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(movingborder==-1)
        {
            movingborder=-2;
            float windowSizeChange[2];
            windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
            WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
            int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
            int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

            if((casesizex*(maxx*-2+8)+posX<mouseX&&mouseX<casesizex*(maxx*-2+8+3)+posX&&
               casesizey*(maxy*-2+8)+posY<mouseY&&mouseY<casesizey*(maxy*-2+8+3)+posY)&&
               (casesizex*(maxx*-2+8+1)+posX>mouseX||mouseX>casesizex*(maxx*-2+8+4)+posX||
               casesizey*(maxy*-2+8+1)+posY>mouseY||mouseY>casesizey*(maxy*-2+8+4)+posY))
            {
                    std::cout<<time(0)<<":haut-gauche\n";
                    movingborder=0;
            }
            else if((casesizex*(maxx*2+10+1)+posX<mouseX&&mouseX<casesizex*(maxx*2+10+4)+posX&&
                    casesizey*(maxy*2+10+1)+posY<mouseY&&mouseY<casesizey*(maxy*2+10+4)+posY)&&
                    (casesizex*(maxx*2+10)+posX>mouseX||mouseX>casesizex*(maxx*2+10+3)+posX||
                    casesizey*(maxy*2+10)+posY>mouseY||mouseY>casesizey*(maxy*2+10+3)+posY))
            {
                std::cout<<time(0)<<":bas-droite\n";
                movingborder=1;
            }
            else if((casesizex*(maxx*-2+8)+posX<mouseX&&mouseX<casesizex*(maxx*-2+8+3)+posX&&
                    casesizey*(maxy*2+10+1)+posY<mouseY&&mouseY<casesizey*(maxy*2+10+4)+posY)&&
                    (casesizex*(maxx*-2+8+1)+posX>mouseX||mouseX>casesizex*(maxx*-2+8+4)+posX||
                    casesizey*(maxy*2+10)+posY>mouseY||mouseY>casesizey*(maxy*2+10+3)+posY))
            {
                    std::cout<<time(0)<<":bas-gauche\n";
                    movingborder=2;
            }
            else if((casesizex*(maxx*2+10+1)+posX<mouseX&&mouseX<casesizex*(maxx*2+10+4)+posX&&
                    casesizey*(maxy*-2+8)+posY<mouseY&&mouseY<casesizey*(maxy*-2+8+3)+posY)&&
                    (casesizex*(maxx*2+10)+posX>mouseX||mouseX>casesizex*(maxx*2+10+3)+posX||
                    casesizey*(maxy*-2+8+1)+posY>mouseY||mouseY>casesizey*(maxy*-2+8+4)+posY))
            {
                    std::cout<<time(0)<<":haut-droite\n";
                    movingborder=3;
            }
            else if((casesizex*(minx*-2+9)+posX<mouseX&&mouseX<casesizex*(minx*-2+9+3)+posX&&
               casesizey*(miny*-2+9)+posY<mouseY&&mouseY<casesizey*(miny*-2+9+3)+posY)&&
               (casesizex*(minx*-2+9+1)+posX>mouseX||mouseX>casesizex*(minx*-2+9+4)+posX||
               casesizey*(miny*-2+9+1)+posY>mouseY||mouseY>casesizey*(miny*-2+9+4)+posY))
            {
                    std::cout<<time(0)<<":2haut-gauche\n";
                    movingborder=4;
            }
            else if((casesizex*(minx*2+9+1)+posX<mouseX&&mouseX<casesizex*(minx*2+9+4)+posX&&
                    casesizey*(miny*2+9+1)+posY<mouseY&&mouseY<casesizey*(miny*2+9+4)+posY)&&
                    (casesizex*(minx*2+9)+posX>mouseX||mouseX>casesizex*(minx*2+9+3)+posX||
                    casesizey*(miny*2+9)+posY>mouseY||mouseY>casesizey*(miny*2+9+3)+posY))
            {
                std::cout<<time(0)<<":2bas-droite\n";
                movingborder=5;
            }
            else if((casesizex*(minx*-2+9)+posX<mouseX&&mouseX<casesizex*(minx*-2+9+3)+posX&&
                    casesizey*(miny*2+9+1)+posY<mouseY&&mouseY<casesizey*(miny*2+9+4)+posY)&&
                    (casesizex*(minx*-2+9+1)+posX>mouseX||mouseX>casesizex*(minx*-2+9+4)+posX||
                    casesizey*(miny*2+9)+posY>mouseY||mouseY>casesizey*(miny*2+9+3)+posY))
            {
                std::cout<<time(0)<<":2bas-gauche\n";
                movingborder=6;
            }
            else if((casesizex*(minx*2+9+1)+posX<mouseX&&mouseX<casesizex*(minx*2+9+4)+posX&&
                    casesizey*(miny*-2+9)+posY<mouseY&&mouseY<casesizey*(miny*-2+9+3)+posY)&&
                    (casesizex*(minx*2+9)+posX>mouseX||mouseX>casesizex*(minx*2+9+3)+posX||
                    casesizey*(miny*-2+9+1)+posY>mouseY||mouseY>casesizey*(miny*-2+9+4)+posY))
            {
                std::cout<<time(0)<<":2haut-droite\n";
                movingborder=7;
            }
        }
        else if(movingborder!=-2)
        {
            float windowSizeChange[2];
            windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
            WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
            int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
            int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

            if(movingborder==0||movingborder==2)maxx=(((mouseX-posX)*1.00/casesizex-10)/2)*-1;
            else if(movingborder==1||movingborder==3)maxx=((mouseX-posX)*1.00/casesizex-10)/2-1;

            if(movingborder==0||movingborder==3)maxy=(((mouseY-posY)*1.00/casesizey-10)/2)*-1;
            else if(movingborder==1||movingborder==2)maxy=((mouseY-posY)*1.00/casesizey-10)/2-1;

            if(movingborder==4||movingborder==6)minx=(((mouseX-posX)*1.00/casesizex-9)/2)*-1;
            else if(movingborder==5||movingborder==7)minx=((mouseX-posX)*1.00/casesizex-9)/2-1;

            if(movingborder==4||movingborder==7)miny=(((mouseY-posY)*1.00/casesizey-9)/2)*-1;
            else if(movingborder==5||movingborder==6)miny=((mouseY-posY)*1.00/casesizey-9)/2-1;

            if(maxx<0)maxx=0;
            if(maxy<0)maxy=0;
            if(maxx>5)maxx=5;
            if(maxy>5)maxy=5;

            if(minx<0)minx=0;
            if(miny<0)miny=0;
            if(minx>5)minx=5;
            if(miny>5)miny=5;

            if(maxx<minx)
            {
                if(movingborder>3)maxx=minx;
                else minx=maxx;
            }
            if(maxy<miny)
            {
                if(movingborder>3)maxy=miny;
                else miny=maxy;
            }
        }
    }
    else
    {
        movingborder=-1;
    }
}
void useBrush(Brush &BRUSH,int X,int Y,bool connection,int level=0)
{
    for(int i=0;i<BRUSH.parts.size();i++)
    {
        BrushPart &part=BRUSH.parts[i];
        int number=((part.numbermax-part.numbermin)*1.00+0.99)*rand()/RAND_MAX+part.numbermin;

        std::vector<sf::Vector2i> places=part.places;
        for(int numi=0;numi<number;numi++)
        {
            int centerid=(places.size()*1.00)*rand()/RAND_MAX;
            sf::Vector2i &center=places[centerid];
            sf::Vector2i drawsize;
            drawsize.x=((part.sizeMax.x-part.sizeMin.x)*1.00+0.99)*rand()/RAND_MAX+part.sizeMin.x;
            drawsize.y=((part.sizeMax.y-part.sizeMin.y)*1.00+0.99)*rand()/RAND_MAX+part.sizeMin.y;

            for(int x=X+center.x-drawsize.x-5; x<=X+center.x+drawsize.x-5; x++)
            {
                for(int y=Y+center.y-drawsize.y-5; y<=Y+center.y+drawsize.y-5; y++)
                {
                    if(0<=x&&x<=19 && 0<=y&&y<=19)
                    {
                        if(level==0)
                        {
                            WorldTiles[x][y]=part.tile;
                            createWorldAt(x,y,connection);
                        }
                        if(level==1)
                        {
                            WorldTilesUp[x][y]=part.tile;
                            createUpWorldAt(x,y);
                        }
                        if(level==2)
                        {
                            WorldDoConnect[x][y]=true;
                            createWorldAt(x,y);
                        }
                        if(level==3)
                        {
                            WorldTilesUp[x][y]=-1;
                            createUpWorldAt(x,y);
                        }
                        if(level==4)
                        {
                            WorldDoConnect[x][y]=false;
                            createWorldAt(x,y);
                        }
                    }
                }
            }
            places.erase(places.begin()+centerid);
        }
        std::cout<<"\n";
    }
}
void brushEditor(sf::RenderWindow &WINDOW)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);

    float windowSizeChange[2];
    bool ButtonPressed;

    sf::Clock Clock;

    int menuX=1000,menuSpeed=10;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));

        menuX-=60;
        displayTexture(WINDOW,Textures::bigmenu3,menuX,0,1100,600);
        if(menuX<-100)break;

        WINDOW.display();
    }
    menuX=600;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));

        menuX-=60;
        displayTexture(WINDOW,Textures::bigmenu3,-100,0,1100,600);
        displayTexture(WINDOW,Textures::bigmenu3b,-100,menuX,1100,600);
        if(menuX<0)break;

        WINDOW.display();
    }

    int movingborder=-1,movingborder2=-1;
    int brushselected=0;
    BrushPart newBrushPart;newBrushPart.tile=0;
    std::array<std::array<bool,11>,11> placesGrid={false};
    int minx=1,maxx=5,miny=1,maxy=5;
    ButtonPressed=0;
    int error1=0;
    int addPart=0;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
        int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

        displayTexture(WINDOW,Textures::bigmenu3,-100,0,1100,600);
        //START_TILES
        if(addPart>0)
        {
            if(addPart>50)
            {
                displayTexture(WINDOW,Textures::piston,425,-46-(addPart-50)*4,143,200);
                if(-46-(addPart-50)*4>-171)
                    displayTexture(WINDOW,Textures::Tile[newBrushPart.tile],445+(105-addPart)/2,200-46-(addPart-50)*4,
                                   addPart,addPart);
                else displayTexture(WINDOW,Textures::Tile[newBrushPart.tile],445+(105-addPart)/2,29,addPart,addPart);

                displayTexture(WINDOW,Textures::data,279+(100-addPart)*3.18,246,50,50);
                displayTexture(WINDOW,Textures::data,665-(100-addPart)*3.18,246,50,50);
            }
            if(addPart<=50)
            {
                displayTexture(WINDOW,Textures::piston,425,-46-(50-addPart)*4,143,200);

                displayTexture(WINDOW,Textures::Tile[newBrushPart.tile],472,154+(50-addPart)*6,50,50);
            }
            if(addPart<=30)
            {
                displayTexture(WINDOW,Textures::data,462,144+(50-addPart)*6,50,50);
            }
            if(addPart==2)
            {
                std::cout<<"hey";
                brushs[brushselected].parts.push_back(newBrushPart);
                drawBrushIcon(brushs[brushselected]);
            }

            addPart-=2;
        }
        else displayTexture(WINDOW,Textures::Tile[newBrushPart.tile],445,29,105,105);

        if(newBrushPart.tile>0)displayTexture(WINDOW,Textures::Tile[newBrushPart.tile-1],355,54,55,55);
        else displayTexture(WINDOW,Textures::Tile[Textures::Tile.size()-1],355,54,55,55);
        if(newBrushPart.tile<Textures::Tile.size()-1)displayTexture(WINDOW,Textures::Tile[newBrushPart.tile+1],585,54,55,55);
        else displayTexture(WINDOW,Textures::Tile[0],585,54,55,55);

        //END_TILES

        displayNumber(WINDOW,AddZero(newBrushPart.numbermin,0),91,60,36,10,255,100);
        displayNumber(WINDOW,AddZero(newBrushPart.numbermax,0),806,60,36,10,255,100);

        displayTexture(WINDOW,Textures::minusbutton,728,58,44,44);
        displayTexture(WINDOW,Textures::plusbutton,934,58,44,44);

        displayTexture(WINDOW,Textures::minusbutton,14,58,44,44);
        displayTexture(WINDOW,Textures::plusbutton,220,58,44,44);

        displayTexture(WINDOW,Textures::leftbutton,285,54,55,55);
        displayTexture(WINDOW,Textures::rightbutton,655,54,55,55);

        displayTexture(WINDOW,Textures::grid,22,163,236,236);
        for(int i=0;i<placesGrid.size();i++)
            for(int y=0;y<placesGrid[i].size();y++)
        {
            if(placesGrid[i][y])
                displaySquare(WINDOW, 22+i*236/11,163+y*236/11, 236/11,236/11,0,100,255,100);
        }

        if(error1>0)
        {
            displaySquare(WINDOW,22,163,236,236,255,0,0,error1);
            error1-=10;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(22<mouseX&&mouseX<258&&163<mouseY&&mouseY<399)
            {
                placesGrid[(mouseX-22)*11/236][(mouseY-163)*11/236]=true;
            }
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if(22<mouseX&&mouseX<258&&163<mouseY&&mouseY<399)
            {
                placesGrid[(mouseX-22)*11/236][(mouseY-163)*11/236]=false;
            }
        }
        /**displayZoneSelectionPair(WINDOW,22,163,236,236,
                                 newBrushPart.distanceMin.x,newBrushPart.distanceMin.y,
                                 newBrushPart.distanceMax.x,newBrushPart.distanceMax.y,movingborder);**/
        displayZoneSelectionPair(WINDOW,735,163,236,236,
                                 newBrushPart.sizeMin.x,newBrushPart.sizeMin.y,
                                 newBrushPart.sizeMax.x,newBrushPart.sizeMax.y,movingborder2,true,1);


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)
        {
            if(285<mouseX&&mouseX<340 && 54<mouseY&&mouseY<109){newBrushPart.tile--;ButtonPressed=1;}
            else if(655<mouseX&&mouseX<710 && 54<mouseY&&mouseY<109){newBrushPart.tile++;ButtonPressed=1;}

            if(newBrushPart.tile<0)newBrushPart.tile=Textures::Tile.size()-1;
            if(newBrushPart.tile>=Textures::Tile.size())newBrushPart.tile=0;

            if(451<mouseX&&mouseX<546 && 223<mouseY&&mouseY<318)
            {if(addPart==0)
            {
                newBrushPart.places.clear();
                for(int i=0;i<placesGrid.size();i++)
                for(int y=0;y<placesGrid[i].size();y++)
                {
                    if(placesGrid[i][y])
                        newBrushPart.places.push_back(sf::Vector2i(i,y));
                }

                if(newBrushPart.places.size()<=0)
                {
                    error1=250;
                }
                else
                {
                    addPart=100;
                    if(newBrushPart.numbermax>newBrushPart.places.size())
                            newBrushPart.numbermax=newBrushPart.places.size();
                    if(newBrushPart.numbermin>newBrushPart.places.size())
                            newBrushPart.numbermin=newBrushPart.places.size();
                }
                ButtonPressed=1;
            }}
            else if(58<mouseY&&mouseY<102)
            {
                if(728<mouseX&&mouseX<772)
                {
                    newBrushPart.numbermax--;
                    if(newBrushPart.numbermin>newBrushPart.numbermax)
                            newBrushPart.numbermin=newBrushPart.numbermax;
                }
                else if(934<mouseX&&mouseX<978)newBrushPart.numbermax++;
                else if(14<mouseX&&mouseX<58)newBrushPart.numbermin--;
                else if(220<mouseX&&mouseX<264)
                {
                    newBrushPart.numbermin++;
                    if(newBrushPart.numbermin>newBrushPart.numbermax)
                            newBrushPart.numbermax=newBrushPart.numbermin;
                }

                if(newBrushPart.numbermax<1)newBrushPart.numbermax=1;
                if(newBrushPart.numbermin<1)newBrushPart.numbermin=1;

                ButtonPressed=1;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&ButtonPressed==0)
        {
            if(285<mouseX&&mouseX<340 && 54<mouseY&&mouseY<109){newBrushPart.tile-=5;ButtonPressed=1;}
            else if(655<mouseX&&mouseX<710 && 54<mouseY&&mouseY<109){newBrushPart.tile+=5;ButtonPressed=1;}

            if(newBrushPart.tile<0)newBrushPart.tile=Textures::Tile.size()-1;
            if(newBrushPart.tile>=Textures::Tile.size())newBrushPart.tile=0;
        }
        displayTexture(WINDOW,brushs[brushselected].icon,421,412,150,150);

        if(brushselected>0) displayTexture(WINDOW,brushs[brushselected-1].icon,34,449,80,80);
        else displayTexture(WINDOW,brushs[brushs.size()-1].icon,34,449,80,80);

        if(brushselected<brushs.size()-1) displayTexture(WINDOW,brushs[brushselected+1].icon,879,449,80,80);
        else displayTexture(WINDOW,brushs[0].icon,879,449,80,80);

        displayTexture(WINDOW,Textures::bigmenu3b,-100,0,1100,600);

        if(400<mouseX&&mouseX<593 && 391<mouseY&&mouseY<584)
        {
            displayTexture(WINDOW,Textures::brushbutton,400,391,193,193);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)
            {
                if(mouseY<487)
                {
                    if(mouseX<496)
                    {
                        brushs.insert(brushs.begin()+brushselected,Brush());
                        drawBrushIcon(brushs[brushselected]);
                    }
                    else
                    {
                        brushs.erase(brushs.begin()+brushselected);
                    }
                }
                else
                {
                    brushs[brushselected].parts.clear();
                    drawBrushIcon(brushs[brushselected]);
                }
                ButtonPressed=1;
            }
        }
        if(416<mouseY&&mouseY<562)
        {
            if(1<mouseX&&mouseX<147)
            {
                displayTexture(WINDOW,Textures::leftbutton,1,416,146,146);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)
                {
                    brushselected--;
                    if(brushselected<0)brushselected=brushs.size()-1;
                    ButtonPressed=1;
                }
            }
            else if(846<mouseX&&mouseX<992)
            {
                displayTexture(WINDOW,Textures::rightbutton,846,416,146,146);
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)
                {
                    brushselected++;
                    if(brushselected>=brushs.size())brushselected=0;
                    ButtonPressed=1;
                }
            }
        }

        WINDOW.display();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))break;
    }
    menuX=0;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));

        menuX+=60;
        displayTexture(WINDOW,Textures::bigmenu3,-100,0,1100,600);
        displayTexture(WINDOW,Textures::bigmenu3b,-100,menuX,1100,600);
        if(menuX>600)break;

        WINDOW.display();
    }
    menuX=-100;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));

        menuX+=40;
        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture(WINDOW,Textures::bigmenu3,menuX,0,1100,600);
        if(menuX>1000)break;

        WINDOW.display();
    }
}
void saveFinalTerrain()
{
    sf::RenderTexture result;result.create(1280,1280);result.clear(sf::Color::Transparent);
    for(int shoti=0;shoti<terrainShots.size();shoti++)
    {
        if(terrainShots[shoti].groundVisible)
        {
            displayTexture(result,terrainShots[shoti].worldTex,0,0,1280,1280);
        }
        if(terrainShots[shoti].roofVisible)
        {
            displayTexture(result,terrainShots[shoti].upWorldTex,0,0,1280,1280);
        }
        if(terrainShots[shoti].entitisVisible)
        {
            displayTexture(result,terrainShots[shoti].entityTex,0,0,1280,1280);
        }
    }
    std::string filename="imagemap/finalmap";
    filename+=IntToString((int)time(0));filename+=".png";

    result.display();
    result.getTexture().copyToImage().saveToFile(filename);
}
void saveFinalTerrainShot(sf::RenderWindow &WINDOW)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);
    saveFinalTerrain();

    int flashopacity=250;
    sf::Clock Clock;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        displayTexture(WINDOW,screen,0,0,1000,600);
        displaySquare(WINDOW,0,0,1000,600,0,0,0,flashopacity/2);

        displaySquare(WINDOW,0,0,1000,600,255,255,255,flashopacity);
        flashopacity-=10;
        if(flashopacity<0)
        {
            return;
        }
        WINDOW.display();
    }
}
void TerrainShotEditor(sf::RenderWindow &WINDOW)
{
    sf::Texture screen;screen.create(WINDOW.getSize().x,WINDOW.getSize().y);screen.update(WINDOW);//screen.loadFromImage(WINDOW.capture());
    double windowSizeChange[2];
    bool ButtonPressed;

    sf::Clock Clock;

    int menuY=-600,menuSpeed=10;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        menuY+=menuSpeed;
        menuSpeed+=5;
        if(menuY>0)break;
        displayTexture(WINDOW,Textures::bigmenu,0,menuY,1000,700);
        WINDOW.display();
    }

    menuY=600;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        displayTexture(WINDOW,Textures::bigmenu,0,0,1000,700);
        menuY-=80;
        if(menuY<0)break;
        displayTexture(WINDOW,Textures::bandemenu,830,menuY,170,600);
        WINDOW.display();
    }
    menuY=600;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        displayTexture(WINDOW,Textures::bigmenu,0,0,1000,700);
        menuY-=80;
        if(menuY<0)break;
        displayTexture(WINDOW,Textures::bandemenu,830,menuY-600,170,600);
        displayTexture(WINDOW,Textures::bandemenu,830,menuY,170,600);
        for(int i=0;i<terrainShots.size();i++)
        {
            displayTexture(WINDOW,terrainShots[i].worldTex,858,menuY+10+100*i,80,80);
            displayTexture(WINDOW,terrainShots[i].upWorldTex,858,menuY+10+100*i,80,80);
            displayTexture(WINDOW,terrainShots[i].entityTex,858,menuY+10+100*i,80,80);
        }
        WINDOW.display();
    }


    int movingShot=-1;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));

        displayTexture(WINDOW,Textures::bigmenu,0,0,1000,700);

        int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];
        displaySquare(WINDOW,mouseX-5,mouseY-5,10,10,255,255,255,100);


        displayTexture(WINDOW,Textures::bandemenu,830,0,170,600);
        int rightClickOn=-1;
        for(int i=0;i<terrainShots.size();i++)
        {
            if(terrainShots[i].groundVisible)
                displayTexture(WINDOW,terrainShots[i].worldTex,0,0,600,600);
            if(terrainShots[i].roofVisible)
                displayTexture(WINDOW,terrainShots[i].upWorldTex,0,0,600,600);
            if(terrainShots[i].entitisVisible)
                displayTexture(WINDOW,terrainShots[i].entityTex,0,0,600,600);

            displayTexture(WINDOW,terrainShots[i].worldTex,858,10+100*i,80,80);
            displayTexture(WINDOW,terrainShots[i].upWorldTex,858,10+100*i,80,80);
            displayTexture(WINDOW,terrainShots[i].entityTex,858,10+100*i,80,80);

            if(movingShot==-1)
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(858<mouseX&&mouseX<938&&
                   10+100*i<mouseY&&mouseY<90+100*i)
                {
                    movingShot=i;
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if(858<mouseX&&mouseX<938&&
                   10+100*i<mouseY&&mouseY<90+100*i)
                {
                    rightClickOn=i;
                }
            }

            if(terrainShots[i].entitisVisible)
                displayTexture(WINDOW,Textures::check2,950,5+100*i+5,25,25);
            else displayTexture(WINDOW,Textures::check1,950,5+100*i+5,25,25);

            if(terrainShots[i].roofVisible)
                displayTexture(WINDOW,Textures::check2,950,5+100*i+33,25,25);
            else displayTexture(WINDOW,Textures::check1,950,5+100*i+33,25,25);

            if(terrainShots[i].groundVisible)
                displayTexture(WINDOW,Textures::check2,950,5+100*i+60,25,25);
            else displayTexture(WINDOW,Textures::check1,950,5+100*i+60,25,25);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)
            {
                if(950<mouseX&&mouseX<975)
                {
                    if(5+100*i+5<mouseY&&mouseY<5+100*i+30)
                    {
                        if(terrainShots[i].entitisVisible)terrainShots[i].entitisVisible=false;
                        else terrainShots[i].entitisVisible=true;
                    }
                    if(5+100*i+33<mouseY&&mouseY<5+100*i+58)
                    {
                        if(terrainShots[i].roofVisible)terrainShots[i].roofVisible=false;
                        else terrainShots[i].roofVisible=true;
                    }
                    if(5+100*i+60<mouseY&&mouseY<5+100*i+85)
                    {
                        if(terrainShots[i].groundVisible)terrainShots[i].groundVisible=false;
                        else terrainShots[i].groundVisible=true;
                    }
                }
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)
        {
            if(0<=mouseX&&mouseX<=600 && 0<=mouseY&&mouseY<=600)
            {
                saveFinalTerrainShot(WINDOW);
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&ButtonPressed==0)ButtonPressed=1;
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(movingShot!=-1)
            {
                int newPos=(mouseY+50)/100;
                if(newPos<terrainShots.size())
                {
                    terrainShots.insert(terrainShots.begin()+newPos,terrainShots[movingShot]);
                    if(newPos<=movingShot)terrainShots.erase(terrainShots.begin()+movingShot+1);
                    else terrainShots.erase(terrainShots.begin()+movingShot);
                }
                else if(newPos>=terrainShots.size())
                {
                    terrainShots.push_back(terrainShots[movingShot]);
                    terrainShots.erase(terrainShots.begin()+movingShot);
                }
            }
            movingShot=-1;
        }
        if(movingShot!=-1)
        {
            displayTexture(WINDOW,terrainShots[movingShot].worldTex,mouseX-40,mouseY-40,80,80,0,100,255,100);
            displayTexture(WINDOW,terrainShots[movingShot].upWorldTex,mouseX-40,mouseY-40,80,80,0,100,255,100);
            displayTexture(WINDOW,terrainShots[movingShot].entityTex,mouseX-40,mouseY-40,80,80,0,100,255,100);

            displaySquare(WINDOW,830,((mouseY+50)/100)*100-5,160,10,0,150,255,200);

        }

        WINDOW.display();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))break;
        if(rightClickOn!=-1)terrainShotMenu(WINDOW,rightClickOn);
    }
    menuY=0;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        displayTexture(WINDOW,Textures::bigmenu,0,0,1000,700);
        menuY-=80;
        if(menuY<-600)break;
        displayTexture(WINDOW,Textures::bandemenu,830,menuY,170,600);
        for(int i=0;i<terrainShots.size();i++)
        {
            displayTexture(WINDOW,terrainShots[i].worldTex,858,menuY+10+100*i,80,80);
            displayTexture(WINDOW,terrainShots[i].upWorldTex,858,menuY+10+100*i,80,80);
            displayTexture(WINDOW,terrainShots[i].entityTex,858,menuY+10+100*i,80,80);
        }
        WINDOW.display();
    }
    menuY=0;menuSpeed=10;
    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        menuY-=menuSpeed;
        menuSpeed+=5;
        if(menuY<-600)break;
        displayTexture(WINDOW,screen,0,0,1000,600);
        displayTexture(WINDOW,Textures::bigmenu,0,menuY,1000,700);
        WINDOW.display();
    }
}
void TilesEditor(sf::RenderWindow &WINDOW)
{
    int moveProcess=0;
    int editorMode=0;
    int TileSelected=0;
    int TypeSelected=0;
    int moveOffset[2]={0,0};
    int ObjectSelected=0;
    int BrushSelected=0;
    double windowSizeChange[2];
    char EditType=0,ButtonPressed=0;
    bool doConnect=false;


    sf::Clock Clock;

    while(WINDOW.isOpen())
    if(Clock.getElapsedTime().asMilliseconds()>20)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if(TypeSelected==0)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    {
                        TileSelected+=event.mouseWheel.delta*5;
                    }
                    else
                    {
                        TileSelected+=event.mouseWheel.delta;
                    }
                    if(TileSelected<0)TileSelected=Textures::Tile.size()-1;
                    if(TileSelected>=Textures::Tile.size())
                    {
                        TileSelected=TileSelected-Textures::Tile.size()+1;
                        if(TileSelected>=Textures::Tile.size())TileSelected=0;
                    }
                }
                else if(TypeSelected==1)
                {
                    ObjectSelected+=event.mouseWheel.delta;
                    if(ObjectSelected<0)ObjectSelected=Textures::Object.size()-1;
                    if(ObjectSelected>=Textures::Object.size())ObjectSelected=0;
                }
                else if(TypeSelected==2)
                {
                    BrushSelected+=event.mouseWheel.delta;
                    if(BrushSelected<0)BrushSelected=brushs.size()-1;
                    if(BrushSelected>=brushs.size())BrushSelected=0;
                }
            }
            if ( event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased )
            {
                ButtonPressed=0;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&!ButtonPressed)
        {
            if(EditType==0)EditType=1;
            else if(EditType==1)EditType=2;
            else if(EditType==2)EditType=0;
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!ButtonPressed)
        {
            if(TypeSelected==0)TypeSelected=1;
            else if(TypeSelected==1)TypeSelected=2;
            else if(TypeSelected==2)TypeSelected=0;
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&!ButtonPressed)
            saveTerrainShot(WINDOW);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)&&!ButtonPressed)
            TerrainShotEditor(WINDOW);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)&&!ButtonPressed)
            brushEditor(WINDOW);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)&&!ButtonPressed)
        {
            saveMenu(WINDOW);
            createWorldTexture(doConnect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
           &&sf::Keyboard::isKeyPressed(sf::Keyboard::S))saveJDRTerrainImage();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)&&ButtonPressed==0)
        {
            int objectNumber=objects.size();
            for(int i=0;i<objectNumber;i++)
            if(objects[i].selected)
            {
                objects.push_back(objects[i]);
                objects[objects.size()-1].X-=10;
                objects[objects.size()-1].Y-=10;
                objects[i].selected=false;
            }
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)&&ButtonPressed==0)
        {
            deselectAll(objects);
            Object newObject;
            newObject.X=int(sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0]);
            newObject.Y=int(sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1]);
            newObject.tex=ObjectSelected;
            newObject.displaySizeY=100;
            newObject.displaySizeX=Textures::Object[ObjectSelected].getSize().x*100/Textures::Object[ObjectSelected].getSize().y;
            newObject.selected=true;
            objects.push_back(newObject);
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)&&ButtonPressed==0)
        {
            if(doConnect)doConnect=false;
            else doConnect=true;
            createWorldTexture(doConnect);
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)&&ButtonPressed==0)
        {
            int objectNumber=objects.size();
            for(int i=0;i<objectNumber;i++)
            if(objects[i].selected)
            {
                objects.erase(objects.begin()+i);
                i--;objectNumber--;
            }
            deselectAll(objects);
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&&ButtonPressed==0)
        {
            editorMode=2;
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)&&ButtonPressed==0)
        {
            editorMode=5;
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)&&ButtonPressed==0)
        {
            editorMode=3;
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)&&ButtonPressed==0)
        {
            editorMode=0;
            ButtonPressed=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)&&ButtonPressed==0)
        {
            std::string NAME;
            std::getline(std::cin,NAME);
            std::ifstream inputfile("Save/"+NAME+".sjdr");
            loadFile(inputfile,doConnect);
            ButtonPressed=1;
        }

        windowSizeChange[0]=WINDOW.getSize().x/1000.0;windowSizeChange[1]=WINDOW.getSize().y/600.0;
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
        int mouseX=sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0];
        int mouseY=sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1];

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(TypeSelected==0)
            {
                if(int(mouseX)>0&&
                   int(mouseX)<600&&
                   int(mouseY)>0&&
                   int(mouseY)<600)
                {
                    if(EditType==0)
                        {WorldTiles[mouseX/30][mouseY/30]=TileSelected;
                        createWorldAt(mouseX/30,mouseY/30,doConnect);}
                    if(EditType==1)
                        {WorldTilesUp[mouseX/30][mouseY/30]=TileSelected;
                        createUpWorldAt(mouseX/30,mouseY/30);}
                    if(EditType==2)
                        {WorldDoConnect[mouseX/30][mouseY/30]=true;
                        createWorldAt(mouseX/30,mouseY/30,doConnect);}
                }
            }
            else if(TypeSelected==1)
            {
                if(ButtonPressed==0)selectObject(WINDOW,sf::Mouse::getPosition(WINDOW).x,sf::Mouse::getPosition(WINDOW).y);

                    if(editorMode==0||editorMode==1)
                    {
                        for(int i=0;i<objects.size();i++)
                        if(objects[i].selected)
                        {
                            objects[i].X+=(sf::Mouse::getPosition(WINDOW).x-moveOffset[0])/windowSizeChange[0];
                            objects[i].Y+=(sf::Mouse::getPosition(WINDOW).y-moveOffset[1])/windowSizeChange[1];
                        }
                    }
                    else if(editorMode==2)
                    {
                        for(int i=0;i<objects.size();i++)
                        if(objects[i].selected)
                        {
                            objects[i].displaySizeX+=(sf::Mouse::getPosition(WINDOW).x-moveOffset[0])/windowSizeChange[0]*2;
                            objects[i].displaySizeY+=(sf::Mouse::getPosition(WINDOW).y-moveOffset[1])/windowSizeChange[1]*2;
                        }
                    }
                    else if(editorMode==3)
                    {
                        moveProcess+=(sf::Mouse::getPosition(WINDOW).x-moveOffset[0])/windowSizeChange[0];
                        if(moveProcess>50||moveProcess<-50)
                        {
                            for(int i=0;i<objects.size();i++)
                            if(objects[i].selected)
                            {
                                if(moveProcess>50)objects[i].rotation++;
                                else objects[i].rotation--;
                                if(objects[i].rotation<0)objects[i].rotation=3;
                                else if(objects[i].rotation>3)objects[i].rotation=0;

                                int widthBuffer=objects[i].displaySizeX;
                                objects[i].displaySizeX=objects[i].displaySizeY;
                                objects[i].displaySizeY=widthBuffer;
                            }
                            moveProcess=0;
                        }
                    }
                    else if(editorMode==5)
                    {
                        if((sf::Mouse::getPosition(WINDOW).y-moveOffset[1])/windowSizeChange[1]>0)
                        {
                            int objectNumber=objects.size();
                            for(int i=0;i<objectNumber;i++)
                            if(objects[i].selected)
                            {
                                objects.insert(objects.begin(),objects[i]);
                                objects.erase(objects.begin()+i+1);
                                i--;objectNumber--;
                            }
                        }
                        else if((sf::Mouse::getPosition(WINDOW).y-moveOffset[1])/windowSizeChange[1]<0)
                        {
                            int objectNumber=objects.size();
                            for(int i=0;i<objectNumber;i++)
                            if(objects[i].selected)
                            {
                                objects.push_back(objects[i]);
                                objects.erase(objects.begin()+i);
                                i=objects.size()-1;
                                i--;objectNumber--;
                            }
                        }
                    }

                ButtonPressed=1;
            }
            else if(TypeSelected==2)
            {
                if(int(mouseX)>0&&
                   int(mouseX)<600&&
                   int(mouseY)>0&&
                   int(mouseY)<600)
                {
                    useBrush(brushs[BrushSelected],mouseX/30,mouseY/30,doConnect,EditType);
                }
            }
        }
        else
        {
            moveProcess=0;
        }
        moveOffset[0]=sf::Mouse::getPosition(WINDOW).x;
        moveOffset[1]=sf::Mouse::getPosition(WINDOW).y;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if(TypeSelected==0)
            {
                if(EditType==1)
                {
                    WorldTilesUp[mouseX/30][mouseY/30]=-1;
                    createUpWorldAt(mouseX/30,mouseY/30);
                }
                else if(EditType==2)
                {
                    WorldDoConnect[mouseX/30][mouseY/30]=false;
                    createWorldAt(mouseX/30,mouseY/30,doConnect);
                }
            }
            else if(TypeSelected==1)
            {
                if(editorMode==0)miniMenu(WINDOW,sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0],sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1],ObjectSelected,editorMode);
                else if(editorMode>=1&&editorMode<=5)miniMorphMenu(WINDOW,sf::Mouse::getPosition(WINDOW).x/windowSizeChange[0],sf::Mouse::getPosition(WINDOW).y/windowSizeChange[1],ObjectSelected,editorMode);
            }
            else if(TypeSelected==2)
            {
                if(int(mouseX)>0&&
                   int(mouseX)<600&&
                   int(mouseY)>0&&
                   int(mouseY)<600)
                {
                    if(EditType==1)useBrush(brushs[BrushSelected],mouseX/30,mouseY/30,doConnect,3);
                    else if(EditType==2)useBrush(brushs[BrushSelected],mouseX/30,mouseY/30,doConnect,4);
                }
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            if(TypeSelected==0)
            {
                if(int(mouseX)>0&&
                   int(mouseX)<600&&
                   int(mouseY)>0&&
                   int(mouseY)<600)
                {
                    if(EditType==0)
                        {TileSelected=WorldTiles[mouseX/30][mouseY/30];}
                    if(EditType==1)
                        {TileSelected=WorldTilesUp[mouseX/30][mouseY/30];}
                }
            }
        }

        displayTexture(WINDOW,Textures::Background,0,0,1000,600);
        sf::Texture WORLDTEXTURE=WorldTexture.getTexture();
        displayTexture(WINDOW,WORLDTEXTURE,0,0,600,600);
        displayTexture(WINDOW,Textures::tilemenu,601,0,400,600);
        displayTexture(WINDOW,Textures::screens[TypeSelected],620,0,170,53);

        sf::Texture WORLDUP;WORLDUP=UpWorldTexture.getTexture();
        if(EditType==1)
        {
            displaySquare(WINDOW,0,0,600,600,100,100,100,50);
            displayTexture(WINDOW,WORLDUP,0,0,600,600);
        }
        else if(EditType==2)
        {
            displaySquare(WINDOW,0,0,600,600,255,100,0,50);
            displayDoConnectMap(WINDOW);
        }

        if(editorMode==0)displayObjects(WINDOW,255,0,0);
        else if(editorMode==1)displayObjects(WINDOW,0,200,255);
        else if(editorMode==2)displayObjects(WINDOW,255,255,0);
        else if(editorMode==3)displayObjects(WINDOW,255,100,0);
        else if(editorMode==4)displayObjects(WINDOW,255,0,255);
        else if(editorMode==5)displayObjects(WINDOW,0,255,0);


        //TileSelector
        if(TypeSelected==0)
        {
            if(TileSelected>1) displayTexture(WINDOW,Textures::Tile[TileSelected-2],800,500,100,100);
            else displayTexture(WINDOW,Textures::Tile[Textures::Tile.size()-2+TileSelected],800,500,100,100);

            if(TileSelected>0) displayTexture(WINDOW,Textures::Tile[TileSelected-1],800,400,100,100);
            else displayTexture(WINDOW,Textures::Tile[Textures::Tile.size()-1],800,400,100,100);

            displayTexture(WINDOW,Textures::Tile[TileSelected],750,200,200,200);

            if(TileSelected<Textures::Tile.size()-1) displayTexture(WINDOW,Textures::Tile[TileSelected+1],800,100,100,100);
            else displayTexture(WINDOW,Textures::Tile[0],800,100,100,100);

            if(TileSelected<Textures::Tile.size()-2) displayTexture(WINDOW,Textures::Tile[TileSelected+2],800,0,100,100);
            else displayTexture(WINDOW,Textures::Tile[+TileSelected-Textures::Tile.size()+2],800,0,100,100);
        }
        else if(TypeSelected==1)
        {
            if(ObjectSelected>1) displayTexture(WINDOW,Textures::Object[ObjectSelected-2],800,500,100,100);
            else displayTexture(WINDOW,Textures::Object[Textures::Object.size()-2+ObjectSelected],800,500,100,100);

            if(ObjectSelected>0) displayTexture(WINDOW,Textures::Object[ObjectSelected-1],800,400,100,100);
            else displayTexture(WINDOW,Textures::Object[Textures::Object.size()-1],800,400,100,100);

            float widthFactor=(float)Textures::Object[ObjectSelected].getSize().x/Textures::Object[ObjectSelected].getSize().y;
            displayTexture(WINDOW,Textures::Object[ObjectSelected],850-100*widthFactor,200,200*widthFactor,200);

            if(ObjectSelected<Textures::Object.size()-1) displayTexture(WINDOW,Textures::Object[ObjectSelected+1],800,100,100,100);
            else displayTexture(WINDOW,Textures::Object[0],800,100,100,100);

            if(ObjectSelected<Textures::Object.size()-2) displayTexture(WINDOW,Textures::Object[ObjectSelected+2],800,0,100,100);
            else displayTexture(WINDOW,Textures::Object[+ObjectSelected-Textures::Object.size()+2],800,0,100,100);
        }
        else if(TypeSelected==2)
        {
            if(brushs.size()>=5)
            {
                if(BrushSelected>1) displayTexture(WINDOW,brushs[BrushSelected-2].icon,800,500,100,100);
                else displayTexture(WINDOW,brushs[brushs.size()-2+BrushSelected].icon,800,500,100,100);
            }

            if(brushs.size()>=2)
            {
                if(BrushSelected>0) displayTexture(WINDOW,brushs[BrushSelected-1].icon,800,400,100,100);
                else displayTexture(WINDOW,brushs[brushs.size()-1].icon,800,400,100,100);
            }

            float widthFactor=(float)brushs[BrushSelected].icon.getSize().x/brushs[BrushSelected].icon.getSize().y;
            displayTexture(WINDOW,brushs[BrushSelected].icon,850-100*widthFactor,200,200*widthFactor,200);

            if(brushs.size()>=2)
            {
                if(BrushSelected<brushs.size()-1) displayTexture(WINDOW,brushs[BrushSelected+1].icon,800,100,100,100);
                else displayTexture(WINDOW,brushs[0].icon,800,100,100,100);
            }

            if(brushs.size()>=5)
            {
                if(BrushSelected<brushs.size()-2) displayTexture(WINDOW,brushs[BrushSelected+2].icon,800,0,100,100);
                else displayTexture(WINDOW,brushs[+BrushSelected-brushs.size()+2].icon,800,0,100,100);
            }
        }


        WINDOW.display();

        /**if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {std::cout<<"\nSAVENAME:\n";std::string OUTPUT;std::cin>>OUTPUT;SaveTerrain("Editor/"+OUTPUT);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {std::cout<<"\nSAVENAME:\n";std::string OUTPUT;std::cin>>OUTPUT;LoadTerrain("Editor/"+OUTPUT);}**/
    }
}
/**void openInventory(sf::RenderWindow &WINDOW)
{
    sf::Clock Clock;sf::Time timeElapsed;
    while (WINDOW.isOpen())
    {
    timeElapsed=Clock.getElapsedTime();
    if(timeElapsed.asMilliseconds()>15)
    {
        Clock.restart();
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }
        WINDOW.setSize(sf::Vector2u(WINDOW.getSize().y*1.666666667,WINDOW.getSize().y));
        WINDOW.clear();
        sf::Sprite World(WorldTexture.getTexture());
        World.setPosition(1-FirstPlayer.X/20+500,1-FirstPlayer.Y/20+300);World.setScale(2,2);
        displayTexture(WINDOW,Textures::Background,0,0,1000,600);
        WINDOW.draw(World);
        if(FirstPlayer.Direction==0)displayTexture(WINDOW,Textures::Player[0],500,300,64,64);
        if(FirstPlayer.Direction==1)displayTexture(WINDOW,Textures::Player[1],500,300,64,64);
        if(FirstPlayer.Direction==2)displayTexture(WINDOW,Textures::Player[2],500,300,64,64);
        if(FirstPlayer.Direction==3)displayTexture(WINDOW,Textures::Player[3],500,300,64,64);
        displayTexture(WINDOW,Textures::Fog,1-FirstPlayer.X/20+500,1-FirstPlayer.Y/20+300,1280,1280);
        displaySquare(WINDOW,0,0,1000,600,0,0,0,100);
        displayPlayerLife(WINDOW);
        for(int i=0;i<FirstPlayer.Inventory.size();i++)
        {
            if(FirstPlayer.InventorySlotSelected==i)
                displayTexture(WINDOW,Textures::SelectedSlot,900,10+i*100,90,90,150,150,255);
            else displayTexture(WINDOW,Textures::SelectedSlot,900,10+i*100,90,90);
            displayTexture(WINDOW,weapons::WeaponsLoaded[FirstPlayer.Inventory[i]].Textures[1],905,15+i*100,80,80);
        }
        displayCollectables(WINDOW);

        //display inventory collectables
        int PosX=0;
        for(int i=0;i<items::CollectableLoaded.size();i++)
        {
            if(items::CollectableLoaded[i].TYPE==1&&FirstPlayer.CollectableInventory[i]!=0)
            {
                displayTexture(WINDOW,items::CollectableLoaded[i].Icon,750-74*(PosX%8),200+74*(PosX/8),64,64);
                displayNumber(WINDOW,IntToString(FirstPlayer.CollectableInventory[i]),750-74*(PosX%8),280-74*(PosX/8),32);
                PosX++;
            }
        }
        WINDOW.display();
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))break;
    }
    }
}**/



