#ifndef __LED_MENU_H__
#define __LED_MENU_H__

#include "NavMenu.h"

class LedMenu: public NavMenu
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
        bool barMode;
        unsigned int barValue;
        unsigned int currentIndex;     

        static void   okAction(void *arg);
        static void backAction(void *arg);
};

#endif