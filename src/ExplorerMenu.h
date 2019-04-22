#ifndef __EXPLORER_MENU_H__
#define __EXPLORER_MENU_H__

#include "Menu.h"

class ExplorerMenu: public Menu
{
    public:
        void init();
        void run();
        void end();

        void _okPress();
        void _leftPress();
        void _rightPress();        
};

#endif