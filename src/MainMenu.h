#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "Menu.h"

class MainMenu: public Menu
{
    private:
        unsigned int selectedGasItem;
        bool refreshGraph;
    public:
        void navSwitchClick(const NavKey key);
        void navSwitchDoubleClick(const NavKey key);
        void navSwitchLongPress(const NavKey key);
        
        void init();
        void run();
        void end();    
};

#endif