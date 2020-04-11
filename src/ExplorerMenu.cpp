#include "ExplorerMenu.h"

#include "main.h"

ExplorerMenu::ExplorerMenu()
{
    registerNavMenu(0, "Entrar", &ExplorerMenu::okAction);
    registerNavMenu(1, "Volver", &ExplorerMenu::backAction);
}

void ExplorerMenu::init()
{  
    done = false;
}
void ExplorerMenu::run()
{
    lcd.clearDisplay(); 
    lcd.setTextColor(BLACK);
    lcd.setCursor(1,39);      
    lcd.print("Explorer");    

    drawNavMenu();
    lcd.display();    
}
void ExplorerMenu::end()
{    
}

void ExplorerMenu::_okPress()
{    
    done = true;
}
void ExplorerMenu::_leftPress()
{
}
void ExplorerMenu::_rightPress()
{
}   

void ExplorerMenu::okAction(void *arg)
{
    //ExplorerMenu *explorerMenu = static_cast<ExplorerMenu*>(arg);
}

void ExplorerMenu::backAction(void *arg)
{
    //ExplorerMenu *explorerMenu = static_cast<ExplorerMenu*>(arg);
}