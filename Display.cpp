#include "Display.h"

void displayTexture(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].texCoords=sf::Vector2f(0,0);
    SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x,0);
    SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
    SPRITE[3].texCoords=sf::Vector2f(0,TEX.getSize().y);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);

    sf::RenderStates rstate;
    rstate.texture=&TEX;
    //rstate.blendMode=sf::BlendAlpha;
    WINDOW.draw(SPRITE,rstate);
    //WINDOW.draw(SPRITE,&TEX);
}
void displayTexturePart(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int texX,int texY,int texX2,int texY2,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].texCoords=sf::Vector2f(texX,texY);
    SPRITE[1].texCoords=sf::Vector2f(texX2,texY);
    SPRITE[2].texCoords=sf::Vector2f(texX2,texY2);
    SPRITE[3].texCoords=sf::Vector2f(texX,texY2);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);
    WINDOW.draw(SPRITE,&TEX);
}
void displayTexture2(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int rotation,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);

    switch(rotation)
    {
        case 0:
        {
            SPRITE[0].texCoords=sf::Vector2f(0,0);
            SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x,0);
            SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
            SPRITE[3].texCoords=sf::Vector2f(0,TEX.getSize().y);
            break;
        }
        case 1:
        {
            SPRITE[0].texCoords=sf::Vector2f(0,TEX.getSize().y);
            SPRITE[1].texCoords=sf::Vector2f(0,0);
            SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().x,0);
            SPRITE[3].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
            break;
        }
        case 2:
        {
            SPRITE[0].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
            SPRITE[1].texCoords=sf::Vector2f(0,TEX.getSize().y);
            SPRITE[2].texCoords=sf::Vector2f(0,0);
            SPRITE[3].texCoords=sf::Vector2f(TEX.getSize().x,0);
            break;
        }
        case 3:
        {
            SPRITE[0].texCoords=sf::Vector2f(TEX.getSize().x,0);
            SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
            SPRITE[2].texCoords=sf::Vector2f(0,TEX.getSize().y);
            SPRITE[3].texCoords=sf::Vector2f(0,0);
            break;
        }
    }

    WINDOW.draw(SPRITE,&TEX);
}
void displayTriangleTexture(sf::RenderTarget &WINDOW,sf::Texture &TEX,int X,int Y,int TX,int TY,int rotation,int R,int G,int B,int Alpha,int divideSize)
{
    sf::VertexArray SPRITE(sf::Triangles,4);

    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);

    switch(rotation)
    {
        case 0:
        {
            SPRITE[0].texCoords=sf::Vector2f(0,0);
            SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x/divideSize,0);
            SPRITE[2].texCoords=sf::Vector2f(0,+TEX.getSize().y/divideSize);
            SPRITE[0].position=sf::Vector2f(X,Y);
            SPRITE[1].position=sf::Vector2f(X+TX/divideSize,Y);
            SPRITE[2].position=sf::Vector2f(X,Y+TY/divideSize);
            break;
        }
        case 1:
        {
            SPRITE[0].texCoords=sf::Vector2f(TEX.getSize().x/divideSize,0);
            SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x,0);
            SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y/divideSize);
            SPRITE[0].position=sf::Vector2f(X+TX/divideSize,Y);
            SPRITE[1].position=sf::Vector2f(X+TX,Y);
            SPRITE[2].position=sf::Vector2f(X+TX,Y+TY/divideSize);
            break;
        }
        case 2:
        {
            SPRITE[0].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y/divideSize);
            SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x,TEX.getSize().y);
            SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().x/divideSize,TEX.getSize().y);
            SPRITE[0].position=sf::Vector2f(X+TX,Y+TY/divideSize);
            SPRITE[1].position=sf::Vector2f(X+TX,Y+TY);
            SPRITE[2].position=sf::Vector2f(X+TX/divideSize,Y+TY);
            break;
        }
        case 3:
        {
            SPRITE[0].texCoords=sf::Vector2f(0,TEX.getSize().y/divideSize);
            SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().x/divideSize,TEX.getSize().y);
            SPRITE[2].texCoords=sf::Vector2f(0,TEX.getSize().y);
            SPRITE[0].position=sf::Vector2f(X,Y+TY/divideSize);
            SPRITE[1].position=sf::Vector2f(X+TX/divideSize,Y+TY);
            SPRITE[2].position=sf::Vector2f(X,Y+TY);
            break;
        }
    }

    WINDOW.draw(SPRITE,&TEX);
}
void displaySquare(sf::RenderTarget &WINDOW,int X,int Y,int TX,int TY,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);
    WINDOW.draw(SPRITE);
}
void displayCircle(sf::RenderTarget &WINDOW,int X,int Y,int RADIUS,int R,int G,int B,int Alpha)
{
    sf::CircleShape circle;
    circle.setFillColor(sf::Color(R,G,B,Alpha));
    circle.setRadius(RADIUS);
    circle.setPosition(X,Y);
    WINDOW.draw(circle);
}
void displayCircleTexture(sf::RenderTarget &WINDOW,int X,int Y,int RADIUS,sf::Texture &TEX,sf::IntRect texRectangle,int R,int G,int B,int Alpha)
{
    sf::CircleShape circle;
    circle.setFillColor(sf::Color(R,G,B,Alpha));
    circle.setRadius(RADIUS);
    circle.setPosition(X,Y);
    circle.setTexture(&TEX);
    circle.setTextureRect(texRectangle);
    WINDOW.draw(circle);
}
void eraseSquare(sf::RenderTarget &WINDOW,int X,int Y,int TX,int TY)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].color=sf::Color(0,0,0,0);
    SPRITE[1].color=sf::Color(0,0,0,0);
    SPRITE[2].color=sf::Color(0,0,0,0);
    SPRITE[3].color=sf::Color(0,0,0,0);
    WINDOW.draw(SPRITE,sf::BlendNone);
}
void eraseCircle(sf::RenderTarget &WINDOW,int X,int Y,int RADIUS)
{
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Transparent);
    circle.setRadius(RADIUS);
    circle.setPosition(X,Y);
    WINDOW.draw(circle,sf::BlendNone);
}

void displayTextureFromTexMap(sf::RenderWindow &WINDOW,sf::Texture &TEX,int TextureNumber,int X,int Y,int TX,int TY,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,4);
    SPRITE[0].position=sf::Vector2f(X,Y);
    SPRITE[1].position=sf::Vector2f(X+TX,Y);
    SPRITE[2].position=sf::Vector2f(X+TX,Y+TY);
    SPRITE[3].position=sf::Vector2f(X,Y+TY);
    SPRITE[0].texCoords=sf::Vector2f(TEX.getSize().y*(TextureNumber-1),0);
    SPRITE[1].texCoords=sf::Vector2f(TEX.getSize().y*TextureNumber,0);
    SPRITE[2].texCoords=sf::Vector2f(TEX.getSize().y*TextureNumber,TEX.getSize().y);
    SPRITE[3].texCoords=sf::Vector2f(TEX.getSize().y*(TextureNumber-1),TEX.getSize().y);
    SPRITE[0].color=sf::Color(R,G,B,Alpha);
    SPRITE[1].color=sf::Color(R,G,B,Alpha);
    SPRITE[2].color=sf::Color(R,G,B,Alpha);
    SPRITE[3].color=sf::Color(R,G,B,Alpha);
    WINDOW.draw(SPRITE,&TEX);
}
void displayObjects(sf::RenderTarget &WINDOW,int selecR,int selecG,int selecB,float multiplier)
{
    for(int i=0;i<objects.size();i++)
    {
        int TEX=objects[i].tex;
        displayTexture2(WINDOW,Textures::Object[TEX],
                       (objects[i].X-(objects[i].displaySizeX)/2)*multiplier, (objects[i].Y-objects[i].displaySizeY/2)*multiplier,
                       objects[i].displaySizeX*multiplier, objects[i].displaySizeY*multiplier,objects[i].rotation);
        if(objects[i].selected)
        displaySquare(WINDOW,
                      objects[i].X-(objects[i].displaySizeX)/2*multiplier, objects[i].Y-objects[i].displaySizeY/2*multiplier,
                    objects[i].displaySizeX*multiplier, objects[i].displaySizeY*multiplier,
                    selecR,selecG,selecB,100);
    }
}
void displayNumber(sf::RenderWindow &WINDOW,std::string STR,int X,int Y,int Size,int R,int G,int B,int Alpha)
{
    for(int i=0;i<STR.length();i++)
    {
        displayTextureFromTexMap(WINDOW,Textures::Numbers,STR[i]-47,X+i*(Size*0.8),Y,Size,Size,R,G,B,Alpha);
    }
}
void displayDoConnectMap(sf::RenderTarget &TARGET)
{
    for(int i=0;i<20;i++){
        for(int y=0;y<20;y++){
            if(WorldDoConnect[y][i])
                displaySquare(TARGET,y*30,i*30,30,30,0,0,255,50);
        }
    }
}
void drawBrushIcon(Brush &BRUSH)
{
    int sizemax=0;
    sf::RenderTexture rendtex;
    rendtex.create(165,165);
    rendtex.clear(sf::Color::Transparent);
    for(int i=0;i<BRUSH.parts.size();i++)
    {
        BrushPart &part=BRUSH.parts[i];
        int number=((part.numbermax-part.numbermin)*1.00+0.99)*rand()/RAND_MAX+part.numbermin;
        std::cout<<"poule:"<<number<<":";

        std::vector<sf::Vector2i> places=part.places;
        for(int numi=0;numi<number;numi++)
        {
            std::cout<<"X:";
            int centerid=(places.size()*1.00)*rand()/RAND_MAX;
            sf::Vector2i &center=places[centerid];
            sf::Vector2i drawsize;
            drawsize.x=((part.sizeMax.x-part.sizeMin.x)*1.00+0.99)*rand()/RAND_MAX+part.sizeMin.x;
            drawsize.y=((part.sizeMax.y-part.sizeMin.y)*1.00+0.99)*rand()/RAND_MAX+part.sizeMin.y;

            for(int x=center.x-drawsize.x; x<=center.x+drawsize.x; x++)
            {
                for(int y=center.y-drawsize.y; y<=center.y+drawsize.y; y++)
                {
                    if(0<=x&&x<=10 && 0<=y&&y<=10)
                    {
                        if(x-5>sizemax)sizemax=x-5; if((x-5)*-1>sizemax)sizemax=(x-5)*-1;
                        if(y-5>sizemax)sizemax=y-5; if((y-5)*-1>sizemax)sizemax=(y-5)*-1;
                        displayTexture(rendtex,Textures::Tile[part.tile],(x)*15,(y)*15,15,15);
                    }
                }
            }
            places.erase(places.begin()+centerid);
        }
        std::cout<<"\n";
    }
    rendtex.display();
    sf::Texture oldtex=rendtex.getTexture();
    rendtex.clear(sf::Color::Transparent);
    displayTexturePart(rendtex,oldtex,0,0,165,165,
                       (5-sizemax)*15,(5-sizemax)*15,(6+sizemax)*15,(6+sizemax)*15);
    rendtex.display();
    BRUSH.icon=rendtex.getTexture();
}
void displayPicText(sf::RenderWindow &WINDOW,std::string Text,int X,int Y,int Size,sf::Texture &TEX,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,Text.length()*4);
    int OFFSET=0;
    int Letter;
    int LetterX,LetterY,SizeX,SizeY;
    bool MAJ;
    for(int i=0;i<Text.length();i++)
    {
        if(Text[i]!=' ')
        {
        if(Text[i]<91){Letter=Text[i]-64;MAJ=true;}
        if(Text[i]>96){Letter=Text[i]-96;MAJ=false;}
        if(Letter>=1&&Letter<=6){LetterX=Letter-1;LetterY=0;}
        if(Letter>=7&&Letter<=12){LetterX=Letter-7;LetterY=1;}
        if(Letter>=13&&Letter<=18){LetterX=Letter-13;LetterY=2;}
        if(Letter>=19&&Letter<=24){LetterX=Letter-19;LetterY=3;}
        if(Letter>=25&&Letter<=26){LetterX=Letter-25;LetterY=4;}
        if(Text[i]==60){LetterX=3;LetterY=4;}if(Text[i]==62){LetterX=4;LetterY=4;}
        if(Text[i]==43){LetterX=5;LetterY=4;}if(Text[i]==45){LetterX=0;LetterY=5;}
        LetterX=LetterX*(TEX.getSize().x/6);LetterY=LetterY*(TEX.getSize().y/6);
        SizeX=TEX.getSize().x/6;SizeY=TEX.getSize().y/6;

        SPRITE[2+i*4].position=sf::Vector2f(X,Y-(Size*0.3*MAJ)+OFFSET);
        SPRITE[3+i*4].position=sf::Vector2f(X+Size,Y-(Size*0.3*MAJ)+OFFSET);
        SPRITE[0+i*4].position=sf::Vector2f(X+Size,Y+Size+OFFSET);
        SPRITE[1+i*4].position=sf::Vector2f(X,Y+Size+OFFSET);

        SPRITE[3+i*4].texCoords=sf::Vector2f(LetterX,LetterY);
        SPRITE[0+i*4].texCoords=sf::Vector2f(LetterX+SizeX,LetterY);
        SPRITE[1+i*4].texCoords=sf::Vector2f(LetterX+SizeX,LetterY+SizeY);
        SPRITE[2+i*4].texCoords=sf::Vector2f(LetterX,LetterY+SizeY);

        SPRITE[0+i*4].color=sf::Color(R,G,B,Alpha);
        SPRITE[1+i*4].color=sf::Color(R,G,B,Alpha);
        SPRITE[2+i*4].color=sf::Color(R,G,B,Alpha);
        SPRITE[3+i*4].color=sf::Color(R,G,B,Alpha);
        OFFSET+=Size*0.8;
        }
        else OFFSET+=Size*0.8;
    }
    WINDOW.draw(SPRITE,&TEX);
}
void displayPicText2(sf::RenderWindow &WINDOW,std::string Text,int X,int Y,int Size,sf::Texture &TEX,int R,int G,int B,int Alpha)
{
    sf::VertexArray SPRITE(sf::Quads,Text.length()*4);
    int OFFSET=0;
    int Letter;
    int LetterX,LetterY,SizeX,SizeY;
    bool MAJ;
    for(int i=0;i<Text.length();i++)
    {
        if(Text[i]!=' ')
        {
        if(Text[i]<91){Letter=Text[i]-64;MAJ=true;}
        if(Text[i]>96){Letter=Text[i]-96;MAJ=false;}
        if(Letter>=1&&Letter<=6){LetterX=Letter-1;LetterY=0;}
        if(Letter>=7&&Letter<=12){LetterX=Letter-7;LetterY=1;}
        if(Letter>=13&&Letter<=18){LetterX=Letter-13;LetterY=2;}
        if(Letter>=19&&Letter<=24){LetterX=Letter-19;LetterY=3;}
        if(Letter>=25&&Letter<=26){LetterX=Letter-25;LetterY=4;}
        if(Text[i]==60){LetterX=3;LetterY=4;}if(Text[i]==62){LetterX=4;LetterY=4;}
        if(Text[i]==43){LetterX=5;LetterY=4;}if(Text[i]==45){LetterX=0;LetterY=5;}
        LetterX=LetterX*(TEX.getSize().x/6);LetterY=LetterY*(TEX.getSize().y/6);
        SizeX=TEX.getSize().x/6;SizeY=TEX.getSize().y/6;

        SPRITE[0+i*4].position=sf::Vector2f(X+OFFSET,Y-(Size*0.3*MAJ));
        SPRITE[1+i*4].position=sf::Vector2f(X+Size+OFFSET,Y-(Size*0.3*MAJ));
        SPRITE[2+i*4].position=sf::Vector2f(X+Size+OFFSET,Y+Size);
        SPRITE[3+i*4].position=sf::Vector2f(X+OFFSET,Y+Size);

        SPRITE[0+i*4].texCoords=sf::Vector2f(LetterX,LetterY);
        SPRITE[1+i*4].texCoords=sf::Vector2f(LetterX+SizeX,LetterY);
        SPRITE[2+i*4].texCoords=sf::Vector2f(LetterX+SizeX,LetterY+SizeY);
        SPRITE[3+i*4].texCoords=sf::Vector2f(LetterX,LetterY+SizeY);

        SPRITE[0+i*4].color=sf::Color(R,G,B,Alpha);
        SPRITE[1+i*4].color=sf::Color(R,G,B,Alpha);
        SPRITE[2+i*4].color=sf::Color(R,G,B,Alpha);
        SPRITE[3+i*4].color=sf::Color(R,G,B,Alpha);
        OFFSET+=Size*0.8;
        }
        else OFFSET+=Size*0.8;
    }
    WINDOW.draw(SPRITE,&TEX);
}
