#ifndef __MAIN_H__
#define __MAIN_H__

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <StackArray.h>
#include <OneButton.h>

#define DATA_LEN 16
#define GRAPH_WIDTH 84/(DATA_LEN-1)

class Menu;
class PowerOnMenu;
class MainMenu;
class LedMenu;
class ExplorerMenu;

extern Adafruit_PCD8544 lcd;

extern OneButton rightButton;
extern OneButton  leftButton;
extern OneButton    okButton;

extern StackArray<Menu*, 4> menuState;
extern PowerOnMenu powerOnMenu;
extern MainMenu mainMenu;
extern LedMenu ledMenu;
extern ExplorerMenu explorerMenu;

extern unsigned int ledValues[10];        
extern volatile unsigned int data[DATA_LEN];
extern volatile unsigned int dataIndex;

#endif