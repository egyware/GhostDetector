#ifndef __MENU_H__
#define __MENU_H__

struct NavMenu
{

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
        
        //funciones internas
        virtual void _okPress() = 0;
        virtual void _leftPress() = 0;
        virtual void _rightPress() = 0;
        
        inline void okLongPress()
        {
            navMenuIndex = 0;
            navMenu = !navMenu;
        }

        inline const bool isDone() const { return done; }
        inline const bool isNavMenu() const { return navMenu; }
    protected:
        bool done;        
        int navMenuIndex;
    private:
        bool navMenu;        
        
        
};

#endif