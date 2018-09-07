#include "Menu.h"
#include "main.h"


Menu::Menu(): done(false), navMenu(false), navMenuIndex(0) {}

void Menu::leftPress()
{
    if(navMenu)
    {
        navMenuIndex +=1;    
        if(navMenuIndex > 1) navMenuIndex = 1;
    }
    else
    {
        _leftPress();
    }
}

void Menu::rightPress()
{
    if(navMenu)
    {
        navMenuIndex -=1;
        if(navMenuIndex < 0) navMenuIndex = 0;
    }
    else
    {
        _rightPress();
    }
}

void Menu::okPress()
{
    if(navMenu)
    {
        
    }
    else
    {
        _okPress();
    }
}