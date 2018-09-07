#ifndef __LED_MENU_H__
#define __LED_MENU_H__

#include "Menu.h"

class LedMenu: public Menu
{
    public:
        LedMenu();
        void init();
        void run();
        void end();

        void _okPress();
        void _leftPress();
        void _rightPress();         
    private:
        int barMode;
        int barValue;
        int currentIndex;     

        static void   okAction(void *arg);
        static void backAction(void *arg);
};

#endif