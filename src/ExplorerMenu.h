#ifndef __EXPLORER_MENU_H__
#define __EXPLORER_MENU_H__

#include "NavMenu.h"

class ExplorerMenu: public NavMenu
{
    public:
        ExplorerMenu();

        void init();
        void run();
        void end();

        void _okPress();
        void _leftPress();
        void _rightPress();   

        static void   okAction(void *arg);
        static void backAction(void *arg);
};

#endif