#ifndef __MENU_H__
#define __MENU_H__

#include <string.h>

class Menu;

typedef void (*Action)(void *arg);

struct NavMenu
{
    char name[8];      
    Action action;
};

class Menu
{
    public:
        Menu();
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
        
        inline void okLongPress()
        {
            navMenuIndex = 0;
            selectedNavMenu = !selectedNavMenu;
        }

        inline const bool isDone() const { return done; }
        inline const bool isSelectedNavMenu() const { return selectedNavMenu; }
        inline void registerNavMenu(const unsigned int index, const char* name, const Action action) { navMenus[index].action = action; strcpy(navMenus[index].name, name); }
    protected:        
        int navMenuIndex;
        bool done;
    private:        
        NavMenu navMenus[2];        
        bool selectedNavMenu;
};

#endif