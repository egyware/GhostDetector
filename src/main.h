#ifndef __MAIN_H__
#define __MAIN_H__

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <StackArray.h>
#include <OneButton.h>

class Menu;
class PowerOnMenu;
class MainMenu;
class LedMenu;

extern Adafruit_PCD8544 lcd;

extern OneButton rightButton;
extern OneButton  leftButton;
extern OneButton    okButton;

extern StackArray<Menu*, 4> menuState;
extern PowerOnMenu powerOnMenu;
extern MainMenu mainMenu;
extern LedMenu ledMenu;

extern int ledValues[10];

#endif