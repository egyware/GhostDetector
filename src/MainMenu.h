#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "Menu.h"

class MainMenu: public Menu
{
    public:
        void _okPress();
        void _leftPress();
        void _rightPress();        
        
        void init();
        void run();
        void end();
};

#endif