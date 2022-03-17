#include "Utility.h"
int CharToInt(char STRING)
{
    int RETURN;
    std::stringstream convert;
    convert<<STRING;
    convert>>RETURN;
    return RETURN;

}
int CharToInt2(char STRING)
{
    int RETURN;
    RETURN=STRING;
    if(RETURN>=48&&RETURN<=57) RETURN=RETURN-48;
    else if(RETURN>=97&&RETURN<=122) RETURN=RETURN-87;
    else if(RETURN>=65&&RETURN<=90) RETURN=RETURN-29;
    else if(RETURN>=33&&RETURN<=47)RETURN=RETURN+29;
    else if(RETURN>=58&&RETURN<=64)RETURN=RETURN+19;
    else if(RETURN==35)RETURN=-1;
    return RETURN;
}
char IntToChar(int NUM)
{
    char RETURN=255;
    if(NUM>=0&&NUM<=9)RETURN=NUM+48;
    else if(NUM>=10&&NUM<=35)RETURN=NUM+87;
    else if(NUM>=36&&NUM<=61)RETURN=NUM+29;
    else if(NUM>=62&&NUM<=76)RETURN=NUM-29;
    else if(NUM>=77&&NUM<=83)RETURN=NUM-19;
    else if(NUM==-1)RETURN=35;
    return RETURN;
}
std::string IntToTerrainChars(int NUM)
{
    std::string RETURN="";
    RETURN+=(NUM/94)+33;
    RETURN+=(NUM%94)+33;

    return RETURN;
}
int TerrainCharsToInt(std::string STR)
{
    int RETURN=0;
    RETURN+=(STR[0]-33)*94;
    RETURN+=STR[1]-33;
    return RETURN;
}
std::string IntToChars(int NUM)
{
    std::string RETURN="";
    RETURN+=IntToChar(NUM/3844);
    RETURN+=IntToChar(NUM%3844/62);
    RETURN+=IntToChar(NUM%3844%62);

    return RETURN;
}
std::string IntToUnit(int NUM)
{
    if(NUM<0)std::cout<<"BLEUROUGE JAUNE VERT";
    int RETURN;
    std::string RETURNSTR;
    RETURN=NUM;
    if(RETURN<0)
    {
        RETURNSTR="S";
        RETURN=RETURN+33;
    }
    if(RETURN>=0&&RETURN<=9) RETURN=RETURN+48;
    else if(RETURN>=10&&RETURN<=35) RETURN=RETURN+87;
    else if(RETURN>=36&&RETURN<=61) RETURN=RETURN+29;
    else if(RETURN==-1)RETURN=35;
    RETURNSTR=RETURNSTR+(char)RETURN;
    return RETURNSTR;
}
std::string IntToString(int INT)
{
    std::string RETURN;
    std::stringstream convert;
    convert<<INT;
    convert>>RETURN;
    return RETURN;

}
int StringToInt(std::string STRING)
{
    int RETURN;
    std::stringstream convert;
    convert<<STRING;
    convert>>RETURN;
    return RETURN;

}
std::string AddZero(int NUM,int TYPE)
{
    std::string RETURN="";
    if(TYPE==0&&NUM<100) RETURN="0";
    if(NUM<10)RETURN=RETURN+"0";
    RETURN=RETURN+IntToString(NUM);
    return RETURN;
}
std::vector<std::string> explode(std::string STRING,std::string SEPARATOR,bool KEEP_SEP,bool KEEP_EMPTY)
{
    std::vector<std::string> RETURN;
    std::string WORD="";bool NEWWORD=false;
    for(int i=0;i<STRING.length();i++)
    {
        NEWWORD=false;
        for(int y=0;y<SEPARATOR.size();y++)
        {
            if(STRING[i]==SEPARATOR[y])
            {
                if(WORD!=""||KEEP_EMPTY){if(KEEP_SEP==true)WORD+=STRING[i];
                            RETURN.push_back(WORD);
                            WORD="";
                            }
                NEWWORD=true;
                break;
            }
        }
        if(NEWWORD==false)WORD+=STRING[i];

    }
    if(WORD!="")RETURN.push_back(WORD);
    return RETURN;
}
