#ifndef __POWER_ON_MENU_H__
#define __POWER_ON_MENU_H__

#include "Menu.h"

class PowerOnMenu: public Menu
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