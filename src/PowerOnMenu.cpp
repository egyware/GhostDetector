#include "PowerOnMenu.h"

#include "main.h"
#include "PIN.h"
#include "MainMenu.h"

void PowerOnMenu::init()
{
    //mostrar el logo, pero ya está por defecto así que no hacer nada
    analogWrite(LEFT_BAR, 255);
    analogWrite(RIGHT_BAR,255);
    delay(250);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    analogWrite(LEFT_BAR, 0);
    analogWrite(RIGHT_BAR, 0);
}
void PowerOnMenu::run()
{
    for(int i = 0; i < 10; i++)
    {
        analogWrite(LEFT_BAR, ledValues[i]);
        analogWrite(RIGHT_BAR,ledValues[i]);
        delay(200);
    }
    analogWrite(LEFT_BAR, 0);
    analogWrite(RIGHT_BAR,0);
    delay(250);
    menuState.push(&mainMenu);
    done = true;
}
void PowerOnMenu::end()
{    
}


void PowerOnMenu::navSwitchClick(const NavKey key)
{
}
void PowerOnMenu::navSwitchDoubleClick(const NavKey key)
{
}
void PowerOnMenu::navSwitchLongPress(const NavKey key)
{    
}