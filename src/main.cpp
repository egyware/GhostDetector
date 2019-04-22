#include <Arduino.h>

#include <TimerOne.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneButton.h>
#include <StackArray.h>

#include "PowerOnMenu.h"
#include "MainMenu.h"
#include "LedMenu.h"
#include "ExplorerMenu.h"
#include "Main.h"
#include "PIN.h"


//PCD8544 lcd(SCLK, DIN, DC, RST, CS);
//Adafruit_PCD8544 lcd(DC, CS, RST);
Adafruit_PCD8544 lcd(PIN_SCLK, PIN_DIN, PIN_DC, PIN_CS, PIN_RST);

OneButton rightButton(PIN_BUTTON_RIGHT, true);
OneButton  leftButton(PIN_BUTTON_LEFT, true);
OneButton    okButton(PIN_BUTTON_OK, true);

unsigned int ledValues[10] = {17, 34, 51, 68, 85, 102, 119, 136, 153, 170};
volatile int data[DATA_LEN]; //este arreglo almacenará los datos en bruto del sensor analogo
volatile int dataIndex = -1;

PowerOnMenu powerOnMenu;
MainMenu mainMenu;
LedMenu ledMenu;
ExplorerMenu explorerMenu;
StackArray<Menu*, 4> menuState;
Menu* currentMenu = NULL;

void captureSensorData()
{  
  dataIndex = (dataIndex + 1) % DATA_LEN;
  data[dataIndex] = analogRead(SENSOR_PIN);  
}

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
  pinMode(LEFT_DOTMODE, OUTPUT); digitalWrite(RIGHT_DOTMODE, HIGH);
  pinMode(RIGHT_DOTMODE, OUTPUT); digitalWrite(RIGHT_DOTMODE, HIGH);
  analogWrite(LEFT_BAR, 255);
  analogWrite(RIGHT_BAR, 255);

  lcd.begin();
  lcd.setContrast(60);

  //pusheamos el menu de encendido para que haga toda la challa
  menuState.push(&ledMenu);

  leftButton.attachClick(leftPress);
  rightButton.attachClick(rightPress);
  okButton.attachClick(okPress);
  okButton.attachLongPressStart(okLongPress);

  // captura de datos
  memset(&data, 0, sizeof(data));
  dataIndex = 0;
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(captureSensorData);
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