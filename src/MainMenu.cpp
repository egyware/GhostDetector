#include "MainMenu.h"
#include "main.h"

void MainMenu::init()
{
    lcd.clearDisplay();
}
void MainMenu::run()
{    
    //lcd.clearDisplay();      
    if(dataIndex == -1)  return;
    int _dataIndex = dataIndex;
    
    lcd.fillRect(0,0, _dataIndex * GRAPH_WIDTH,37, WHITE);
    
    for(int i = 1; i < DATA_LEN && i <= _dataIndex; i++)
    {   
        lcd.drawLine((i-1) * GRAPH_WIDTH, (data[i-1]*48)/1024 , i * GRAPH_WIDTH, (data[i]*48)/1024, BLACK);        
    }    
    lcd.drawLine(_dataIndex * GRAPH_WIDTH, 0, _dataIndex * GRAPH_WIDTH, 36, BLACK);
    lcd.drawPixel(_dataIndex * GRAPH_WIDTH, (data[_dataIndex]*48)/1024, WHITE);    

    lcd.fillRect(0, 37, 84, 11, BLACK);    
    lcd.setTextColor(WHITE);
    lcd.setCursor(30,38);  lcd.print("GHOST");    
    lcd.display();
}
void MainMenu::end()
{
}


void MainMenu::_leftPress()
{
}
void MainMenu::_rightPress()
{
}
void MainMenu::_okPress()
{
}