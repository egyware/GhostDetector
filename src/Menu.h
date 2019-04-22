#ifndef __MENU_H__
#define __MENU_H__

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
        void okLongPress();

        //funciones internas
        virtual void _okPress() = 0;
        virtual void _leftPress() = 0;
        virtual void _rightPress() = 0;
        
        inline const bool isDone() const { return done; }        
    protected:               
        bool done;
    private:
};

#endif