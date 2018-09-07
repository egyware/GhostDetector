#include <Arduino.h>

//#include <PCD8544.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneButton.h>
#include <StackArray.h>

#include "PowerOnMenu.h"
#include "MainMenu.h"
#include "LedMenu.h"

#define SCLK 13
#define DIN 12
#define DC  9
#define RST 7
#define CS 8

//PCD8544 lcd(SCLK, DIN, DC, RST, CS);
//Adafruit_PCD8544 lcd(DC, CS, RST);
Adafruit_PCD8544 lcd(SCLK, DIN, DC, CS, RST);

OneButton rightButton(A0, true);
OneButton  leftButton(A2, true);
OneButton    okButton(A1, true);

int ledValues[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

PowerOnMenu powerOnMenu;
MainMenu mainMenu;
LedMenu ledMenu;
StackArray<Menu*, 4> menuState;
Menu* currentMenu = NULL;


void leftPress()
{
  if(currentMenu) currentMenu->leftPress();
}
void rightPress()
{
  if(currentMenu) currentMenu->rightPress();
}
void okPress()
{
  if(currentMenu) currentMenu->okPress();
}
void okLongPress()
{
  if(currentMenu) currentMenu->okLongPress();
}

void setup()
{
  pinMode(3, OUTPUT); digitalWrite(3,HIGH);
  pinMode(4, OUTPUT); digitalWrite(4,HIGH);
  analogWrite(5, 255);
  analogWrite(6, 255);

  lcd.begin();
  lcd.setContrast(60);

  //pusheamos el menu de encendido para que haga toda la challa
  menuState.push(&ledMenu);

  leftButton.attachClick(leftPress);
  rightButton.attachClick(rightPress);
  okButton.attachClick(okPress);
  okButton.attachLongPressStart(okLongPress);
}

void loop()
{
    if(currentMenu == NULL)
    {
      if(!menuState.pop(currentMenu))
      {
          menuState.push(&powerOnMenu); //ir al inicio
          return;
      }      
      currentMenu->init();
      while(!currentMenu->isDone())
      {
        leftButton.tick();
        rightButton.tick();
        okButton.tick();
        currentMenu->run();
      }
      currentMenu->end();
      currentMenu = NULL;
    }
  
}