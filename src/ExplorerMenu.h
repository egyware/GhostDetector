#ifndef __EXPLORER_MENU_H__
#define __EXPLORER_MENU_H__

#include "Menu.h"

class ExplorerMenu: public Menu
{
    public:
        void init();
        void run();
        void end();

        void navSwitchClick(const NavKey);
        void navSwitchDoubleClick(const NavKey);
        void navSwitchLongPress(const NavKey);
};

#endif