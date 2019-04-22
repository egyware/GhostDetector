#include "Menu.h"
#include "main.h"


Menu::Menu(): done(false)
{   
}

void Menu::leftPress()
{
    _leftPress();
}

void Menu::rightPress()
{
    _rightPress();    
}

void Menu::okPress()
{
    _okPress();
}

void Menu::okLongPress()
{
    
}