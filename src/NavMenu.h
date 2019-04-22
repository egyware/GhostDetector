#ifndef __NAV_MENU_H__
#define __NAV_MENU_H__

#include <string.h>
#include "Menu.h"

typedef void (*Action)(void *arg);

struct NavMenuItem
{
    char name[8];      
    Action action;
};

class NavMenu : public  Menu
{
    public:
        NavMenu();
        virtual void init() = 0;
        virtual void run() = 0;
        virtual void end() = 0;

        void okPress();
        void leftPress();
        void rightPress();

        void drawNavMenu();
        
        //funciones internas
        virtual void _okPress() = 0;
        virtual void _leftPress() = 0;
        virtual void _rightPress() = 0;
        
        void okLongPress()
        {
            navMenuIndex = 0;
            selectedNavMenu = !selectedNavMenu;
        }

        inline const bool isDone() const { return done; }
        inline const bool isSelectedNavMenu() const { return selectedNavMenu; }
        inline void registerNavMenu(const unsigned int index, const char* name, const Action action) { navMenus[index].action = action; strcpy(navMenus[index].name, name); }
    protected:        
        unsigned int navMenuIndex;        
    private:        
        NavMenuItem navMenus[2];        
        bool selectedNavMenu;
};

#endif