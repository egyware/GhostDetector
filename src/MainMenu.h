#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "Menu.h"

//  y esto?
enum GasType
{
    GAS_LGP = 0,
    GAS_CO,
    GAS_SMOKE,

    GAS_LEN
};

inline GasType operator++(GasType & p_oRight, int) // A++
{
    return static_cast<GasType>(static_cast<unsigned int>(p_oRight)+1 % static_cast<unsigned int>(GAS_LEN));
}

inline GasType operator--(GasType & p_oRight, int) // A--
{
    return (static_cast<unsigned int>(p_oRight) < 1)?static_cast<GasType>(GAS_LEN -1):static_cast<GasType>(static_cast<unsigned int>(p_oRight)-1);
} 

class MainMenu: public Menu
{
    private:
        unsigned int selectedGasItem;
        bool refreshGraph;
    public:
        MainMenu():gasTypeSelected(GAS_LGP)
        {            
        }

        void navSwitchClick(const NavKey key);
        void navSwitchDoubleClick(const NavKey key);
        void navSwitchLongPress(const NavKey key);
        
        void init();
        void run();
        void end();    
};

#endif