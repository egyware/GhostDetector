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

//Constantes
//este codigo ha sido sacado desde aqui https://www.hackster.io/karimmufte/arduino-and-mq2-gas-sensor-57f98c
//lo he cortado y desmenuzado para mi propio beneficio

// Variables globales para obtener las concentraciones
//asumo que estos puntos corresponden a temperatura ambiente

const float     LPGCurve[3]  =  {2.3,0.21,-0.47};   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 

const float     COCurve[3]  =  {2.3,0.72,-0.34};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15) 

const float     SmokeCurve[3] ={2.3,0.53,-0.44};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)                                                     

//Ro is initialized to 10 kilo ohms
float           Ro           =  10;                 
 


//PCD8544 lcd(SCLK, DIN, DC, RST, CS);
//Adafruit_PCD8544 lcd(DC, CS, RST);
Adafruit_PCD8544 lcd(PIN_SCLK, PIN_DIN, PIN_DC, PIN_CS, PIN_RST);

//utilizo la biblioteca OneButton para usar los botones que hice con el navswitch
OneButton rightButton(PIN_BUTTON_RIGHT, true);
OneButton  leftButton(PIN_BUTTON_LEFT, true);
OneButton    okButton(PIN_BUTTON_OK, true);

unsigned int ledValues[10] = {17, 34, 51, 68, 85, 102, 119, 136, 153, 170};//escala de valores en donde se encienden cada uno de los leds
volatile unsigned int data[DATA_LEN] = {0}; //este arreglo almacenará los datos en bruto del sensor analogo
volatile unsigned int dataIndex = DATA_LEN + DATA_LEN - 1; //se inicializa en este indice para indicar que no hay datos

//cada menú está previamente cargado en memoria, lo hice así porque no se que tan bueno sea usar new/delete en arduino
//además si la memoria me da, seguiré usando la memoria estatica
PowerOnMenu powerOnMenu;
MainMenu mainMenu;
LedMenu ledMenu;
ExplorerMenu explorerMenu;
StackArray<Menu*, 4> menuState; //solo puedo apilar 4 menus, osea podré avanzar y retroceder en los menus. Aún no se si usaré esta función
Menu* currentMenu = NULL;

void captureSensorData()
{  
  dataIndex = (dataIndex + 1) % DATA_LEN;
  data[dataIndex] = analogRead(SENSOR_PIN);  
}

void leftClick()
{
  if(currentMenu) currentMenu->navSwitchClick(NavLeft);
}
void leftDoubleClick()
{
  if(currentMenu) currentMenu->navSwitchDoubleClick(NavLeft);
}
void rightClick()
{
  if(currentMenu) currentMenu->navSwitchClick(NavRight);
}
void rightDoubleClick()
{
  if(currentMenu) currentMenu->navSwitchDoubleClick(NavRight);
}
void okClick()
{
  if(currentMenu) currentMenu->navSwitchClick(NavOk);
}
void okDoubleClick()
{
  if(currentMenu) currentMenu->navSwitchDoubleClick(NavOk);
}
void okLongPress()
{
  if(currentMenu) currentMenu->navSwitchLongPress(NavOk);
}

void setup()
{
  //inicializacion de pins
  //modo punto
  pinMode(LEFT_DOTMODE, OUTPUT); digitalWrite(LEFT_DOTMODE, HIGH);
  pinMode(RIGHT_DOTMODE, OUTPUT); digitalWrite(RIGHT_DOTMODE, HIGH);
  analogWrite(LEFT_BAR,  0);
  analogWrite(RIGHT_BAR, 0);

  //inicializando pantalla
  lcd.begin();
  lcd.setContrast(60);

  //pusheamos el menu de encendido para que haga toda la challa
  menuState.push(&powerOnMenu);  

  leftButton.attachClick(leftClick);
  leftButton.attachDoubleClick(leftDoubleClick);
  rightButton.attachClick(rightClick);
  rightButton.attachDoubleClick(rightDoubleClick);
  okButton.attachClick(okClick);
  okButton.attachDoubleClick(okDoubleClick);
  okButton.attachLongPressStart(okLongPress);

  // captura de datos  
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