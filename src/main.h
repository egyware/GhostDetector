#ifndef __MAIN_H__
#define __MAIN_H__

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <StackArray.h>
#include <OneButton.h>

#define DATA_LEN 16
#define GRAPH_WIDTH 84/(DATA_LEN-1)

#define         RL_VALUE                     (5)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (9.83)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet

/**********************Software Related Macros***********************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 

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

//declaración de variables globales para saber la concentración de gases
extern const float     LPGCurve[3];
extern const float     COCurve[3];
extern const float     SmokeCurve[3];
extern float           Ro;

/**************** MQResistanceCalculation **************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
**********************************************************************************/
inline float MQResistanceCalculation(int raw_adc)
{
  return RL_VALUE*(1023-raw_adc)/(float)raw_adc;
}

#endif