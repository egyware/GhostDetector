#include "MainMenu.h"

#include "ExplorerMenu.h"
#include "main.h"
#include "PIN.h"

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
  //challa
  pinMode(LEFT_DOTMODE, OUTPUT); digitalWrite(LEFT_DOTMODE, HIGH);
  pinMode(RIGHT_DOTMODE, OUTPUT); digitalWrite(RIGHT_DOTMODE, HIGH);
  int x=0;
  delay(CALIBRATION_SAMPLE_INTERVAL);
  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));

    if(x < 10)
    {
      analogWrite(RIGHT_BAR, ledValues[x]);
      analogWrite(LEFT_BAR,  ledValues[x]);
    }
    else
    {
      analogWrite(RIGHT_BAR, ledValues[9 - (x - 10)]);
      analogWrite(LEFT_BAR,  ledValues[9 - (x - 10)]);  
    }
    x = (x + 1)%20;
    delay(CALIBRATION_SAMPLE_INTERVAL);
    
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
 
  analogWrite(RIGHT_BAR, 0);
  analogWrite(LEFT_BAR,  0);
  return val; 
}

void MainMenu::init()
{
    done = false;
    lcd.clearDisplay();
    Ro = MQCalibration(A3);      
}
void MainMenu::run()
{       
    if(dataIndex >= DATA_LEN) return; //fuera de los limites
    unsigned int _dataIndex = dataIndex; //2  
    
    //si esta bandera está activada, borro todo
    if(refreshGraph)
    {
      lcd.fillRect(0,0, 84,37, WHITE);
      refreshGraph = false;
    }
    else
    {
      lcd.fillRect(0,0, _dataIndex * GRAPH_WIDTH,37, WHITE);
    }
    
    float anteriorValor, valor;
    //100.000 ppm puede medir el sensor
    float maximoValor = 100000;
    switch(selectedGasItem)
    {
         case 0: //gas lpg
          valor = MQGetPercentage(MQRead()/Ro, LPGCurve);          
        break;
        case 1: //CO
          valor = MQGetPercentage(MQRead()/Ro, COCurve);          
        break;
        case 2: //HUMO
          valor = MQGetPercentage(MQRead()/Ro, SmokeCurve);          
        break;
        case 3: //Rs
          valor = MQRead();
          maximoValor = 100; //maximo kOhm??
          break;
        case 4: //Ro
          valor = Ro;    
          anteriorValor = Ro;
          maximoValor = 10; //maximo valor 10kOhm
        break;    
        case 5: //Relación
          valor = MQRead()/Ro;
          maximoValor = 10;
        break;
    }
    
    //dibujar el grafico
    for(unsigned int i = 1; i < DATA_LEN && i <= _dataIndex; i++)
    {   
        lcd.drawLine((i-1) * GRAPH_WIDTH, 47-(int)((data[i-1]*47)/maximoValor), i * GRAPH_WIDTH, 47-(int)((data[i]*47)/maximoValor), BLACK);        
    }    
    
    lcd.drawLine(_dataIndex * GRAPH_WIDTH, 0, _dataIndex * GRAPH_WIDTH, 36, BLACK);
    lcd.drawPixel(_dataIndex * GRAPH_WIDTH, 47-(int)((data[_dataIndex]*47)/maximoValor), WHITE);    

    //cuadrado de abajo contendrá las lecturas de las concentraciones
    lcd.fillRect(0, 37, 84, 11, BLACK);
    
    // abajo en el cuadro negro caben 3 numeros 9 digitos en total
    // tendremos en el item 0:  LPG: LPGppm MQRead()/Ro
    //                      1:   CO: COppm   MQRead()/Ro
    //                      2: Humo: Humoppm MQRead()/Ro
    //                      3: Raw : MQRead() MQRead()/Ro
    //                      4:   Ro: Ro

    lcd.setCursor(1,10);  
    lcd.setTextColor(BLACK);
    lcd.print(valor);
    lcd.print(",");
    lcd.print(maximoValor);
    lcd.print(",");
    lcd.print((valor*48)/maximoValor);

    lcd.setTextColor(WHITE);
    lcd.setCursor(1,39);  
    switch(selectedGasItem)
    {
        case 0: //gas lpg
          lcd.print("LPG: ");
          lcd.print(valor);
          lcd.print("ppm");          
        break;
        case 1: //CO
          lcd.print("CO:  ");
          lcd.print(valor);
          lcd.print("ppm");          
        break;
        case 2: //HUMO
          lcd.print("Humo:");
          lcd.print(valor);
          lcd.print("ppm");          
        break;
        case 3: //Rs
          lcd.print("Rs:");
          lcd.print(valor);
          lcd.print("kOhm");
          break;
        case 4: //Ro
          lcd.print("Ro:");
          lcd.print(Ro);
          lcd.print("kOhm");          
        break;    
        case 5: //Relación
          lcd.print("Rs/Ro:");
          lcd.print(MQRead()/Ro);                  
        break;
        
    }   
    
    lcd.display();
}
void MainMenu::end()
{
}


void MainMenu::navSwitchClick(const NavKey key)
{
  //seleccionamos que gases estamos trabajando
   switch(key)
   {
      case NavKey::NavLeft:
        selectedGasItem = (selectedGasItem == 0)?5: selectedGasItem-1;
        refreshGraph = true;
      break;
      case NavKey::NavRight:
        selectedGasItem = (selectedGasItem + 1) % 6;
        refreshGraph = true;
      break;
      case NavKey::NavOk:
        //no tengo planeado nada para este item aún
      break;
      default:
      break;
   }
}
void MainMenu::navSwitchDoubleClick(const NavKey key)
{
}
void MainMenu::navSwitchLongPress(const NavKey key)
{    
  switch(key)
  {
    case NavKey::NavLeft:
    break;
    case NavKey::NavRight:
    break;
    case NavKey::NavOk:
      //ir al menu explorador, pero antes tengo que programarlo eso si
      menuState.push(this);
      menuState.push(&explorerMenu);  
      done = true;
    break;
  }
}