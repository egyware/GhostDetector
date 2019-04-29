#include "MainMenu.h"
#include "main.h"
#include "PIN.h"

// void setup()
// {
//   Serial.print("Calibrating...\n");                
//   Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
//    lcd.begin(16, 2);                                                  //when you perform the calibration                    
//   Serial.print("Calibration is done...\n"); 
//   Serial.print("Ro=");
//   Serial.print(Ro);
//   Serial.print("kohm");
//   Serial.print("\n");
// }
 
/*************************** MQCalibration **************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
**********************************************************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;
 
  delay(CALIBRATION_SAMPLE_INTERVAL);
  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
 
  return val; 
}

void MainMenu::init()
{
    lcd.clearDisplay();
    Ro = MQCalibration(A3);  

    pinMode(LEFT_DOTMODE,  INPUT); 
    pinMode(RIGHT_DOTMODE, INPUT); 
}
void MainMenu::run()
{    
  static int barValue = 0;
  static int dir = 1;
  if(barValue > 180) { barValue = 180; dir = -1; }
  if(barValue < 0) { barValue = 0; dir = 1; }
  analogWrite(LEFT_BAR,  barValue);
  analogWrite(RIGHT_BAR, barValue);
  delay(5);  
  barValue+=dir;

//       Serial.print("LPG:"); 
//    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,LPGCurve );
//    Serial.print( "ppm" );
//    Serial.print("    ");   
//    Serial.print("CO:"); 
//    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO) );
//    Serial.print( "ppm" );
//    Serial.print("    ");   
//    Serial.print("SMOKE:"); 
//    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE) );
//    Serial.print( "ppm" );
//    Serial.print("\n");
//         lcd.setCursor(0, 0);
//         lcd.print("LPG:");
// lcd.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG) );
// //lcd.print( "ppm" );
// lcd.print("     ");  
//   lcd.setCursor(9, 0);
// lcd.print("CO:"); 
// lcd.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO) );
// //lcd.print( "ppm" );
// lcd.print("       "); 
//  lcd.setCursor(0, 1);  
// lcd.print("SMOKE:"); 
// lcd.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE) );
// //lcd.print( "ppm" );
// lcd.print("         ");
//    delay(200);
    //lcd.clearDisplay();      
    if(dataIndex >= DATA_LEN) return; //fuera de los limites
    unsigned int _dataIndex = dataIndex;

    //sección superior iconos
    lcd.fillRect(0, 0, 84, 6, BLACK);
    
    //
    lcd.fillRect(0,6, _dataIndex * GRAPH_WIDTH,37, WHITE);
    
    for(unsigned int i = 1; i < DATA_LEN && i <= _dataIndex; i++)
    {   
        lcd.drawLine((i-1) * GRAPH_WIDTH, 6+(data[i-1]*42)/1024 , i * GRAPH_WIDTH, 6+(data[i]*42)/1024, BLACK);        
    }    
    lcd.drawLine(_dataIndex * GRAPH_WIDTH,  6, _dataIndex * GRAPH_WIDTH, 36, BLACK);
    lcd.drawPixel(_dataIndex * GRAPH_WIDTH, 6+(data[_dataIndex]*42)/1024, WHITE);    

    
    lcd.fillRect(0, 37, 84, 11, BLACK);
    lcd.setTextColor(WHITE);
    //lcd.setCursor(30,38);  //lcd.print("GHOST");
    lcd.setTextColor(WHITE);
    lcd.setCursor(0,38);  
    lcd.print(MQGetPercentage(MQRead()/Ro, LPGCurve));
    lcd.print(',');
    lcd.print(MQGetPercentage(MQRead()/Ro, COCurve));
    lcd.print(',');
    lcd.print(MQGetPercentage(MQRead()/Ro, SmokeCurve));
    
    
    lcd.display();
}
void MainMenu::end()
{
}


void MainMenu::navSwitchClick(const NavKey key)
{
}
void MainMenu::navSwitchDoubleClick(const NavKey key)
{
}
void MainMenu::navSwitchLongPress(const NavKey key)
{    
}