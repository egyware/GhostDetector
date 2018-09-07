#include "Menu.h"
#include "main.h"


Menu::Menu(): done(false), selectedNavMenu(false), navMenuIndex(0) 
{    
    //set 0
    memset(&navMenus, 0, sizeof(navMenus));
}

void Menu::leftPress()
{
    if(selectedNavMenu)
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
    if(selectedNavMenu)
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
    if(selectedNavMenu)
    {
        NavMenu &navMenu = navMenus[navMenuIndex];
        if(navMenu.action != nullptr) 
        {
            navMenu.action(this);
        }        
    }
    else
    {
        _okPress();
    }
}

void Menu::drawNavMenu()
{
    if(isSelectedNavMenu())
    {
        switch(navMenuIndex)
        {
            case 0:
            lcd.fillRect(5, 38, 35, 10, BLACK); lcd.setCursor(11, 40); lcd.setTextColor(WHITE); lcd.print(navMenus[0].name);
            lcd.drawRect(44,38, 35, 10, BLACK); lcd.setCursor(47, 40); lcd.setTextColor(BLACK); lcd.print(navMenus[1].name);
            break;
            case 1:
            lcd.drawRect(5, 38, 35, 10, BLACK); lcd.setCursor(11, 40); lcd.setTextColor(BLACK); lcd.print(navMenus[0].name);
            lcd.fillRect(44,38, 35, 10, BLACK); lcd.setCursor(47, 40); lcd.setTextColor(WHITE); lcd.print(navMenus[1].name);
            break;
        }
    }
    else
    {
        if(navMenus[0].name[0] != 0) lcd.drawRect(5, 38, 35, 10, BLACK); lcd.setCursor(11, 40); lcd.print(navMenus[0].name);
        if(navMenus[1].name[0] != 0) lcd.drawRect(44,38, 35, 10, BLACK); lcd.setCursor(47, 40); lcd.print(navMenus[1].name);
    }
}