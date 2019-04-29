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
   //return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc)); //original
}


/***************************  MQGetPercentage ********************************
Input:   rs_ro_ratio - Rs divided by Ro
         pcurve      - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 
         of the line could be derived if y(rs_ro_ratio) is provided. As it is a 
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
         value.
**********************************************************************************/ 
inline int MQGetPercentage(float rs_ro_ratio, const float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));  
}


/***************************  MQRead *******************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
**********************************************************************************/ 
inline float MQRead()
{
  //ahora solo devuelve el valor inmediato, no el promedio
  unsigned int _dataIndex = dataIndex;
  if(_dataIndex >= DATA_LEN) return -1; //fuera de los limites
  return MQResistanceCalculation(data[_dataIndex]);  
}

#endif
