#include "ExplorerMenu.h"

#include "main.h"
#include "MainMenu.h"


void ExplorerMenu::init()
{
    //mostrar el logo, pero ya está por defecto así que no hacer nada
    analogWrite(5,255);
    analogWrite(6,255);
    delay(250);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    analogWrite(5, 0);
    analogWrite(6, 0);
}
void ExplorerMenu::run()
{
    for(int i = 0; i < 10; i++)
    {
        analogWrite(5,ledValues[i]);
        analogWrite(6,ledValues[i]);
        delay(200);
    }
    analogWrite(5,0);
    analogWrite(6,0);
    delay(250);
    menuState.push(&mainMenu);
    done = true;
}
void ExplorerMenu::end()
{    
}


void ExplorerMenu::_leftPress()
{
}
void ExplorerMenu::_rightPress()
{
}
void ExplorerMenu::_okPress()
{
}