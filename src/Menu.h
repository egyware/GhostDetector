#ifndef __MENU_H__
#define __MENU_H__

enum NavKey
{
    NavLeft = 0,
    NavRight, 
    NavOk
};


class Menu
{
    public:
        Menu():done(false) {}
        virtual void init() = 0;
        virtual void run() = 0;
        virtual void end() = 0;

        virtual void navSwitchClick(const NavKey key) = 0;
        virtual void navSwitchDoubleClick(const NavKey key) = 0;
        virtual void navSwitchLongPress(const NavKey key) = 0;

        inline const bool isDone() const { return done; }        
    protected:               
        bool done;
    private:
};

#endif