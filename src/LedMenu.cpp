#include "LedMenu.h"
#include "PIN.h"
#include "main.h"



LedMenu::LedMenu():barMode(0),barValue(0), currentIndex(0)
{
    registerNavMenu(0,    "Ok", &LedMenu::  okAction);
    registerNavMenu(1, "Atras", &LedMenu::backAction);
}

void LedMenu::init()
{  
    done = false;
    pinMode(LEFT_DOTMODE,  OUTPUT); digitalWrite(LEFT_DOTMODE,  HIGH);
    pinMode(RIGHT_DOTMODE, OUTPUT); digitalWrite(RIGHT_DOTMODE, HIGH);
    analogWrite(LEFT_BAR, 0);
    analogWrite(RIGHT_BAR, 0);
}
void LedMenu::run()
{
    lcd.clearDisplay();    
    lcd.fillRect(0,0, 84, 11, BLACK);    
    lcd.setTextColor(WHITE);
    lcd.setCursor(34,2);  lcd.print("LED");
    lcd.setTextColor(BLACK);

    lcd.setCursor( 5,16); lcd.print("PWM");
    lcd.setCursor(22,16); lcd.print(':');
    lcd.setCursor(28,16); lcd.print(barValue);    
    lcd.setCursor(46,16); lcd.println(barMode?"Dot":"Bar");

    for(int i=0; i<10; i++)
    {
        if(ledValues[i] == barValue && barMode)
        {
            lcd.fillRect(4+i*8, 26, 4, 8, BLACK);
        }
        if(ledValues[i] <= barValue && !barMode)
        {
            lcd.fillRect(4+i*8, 26, 4, 8, BLACK);
        }        
        else
        {
            lcd.drawRect(4+i*8, 26, 4, 8, BLACK);
        }
    }
    drawNavMenu();
    lcd.display();    
}
void LedMenu::end()
{
}

 void LedMenu::_leftPress()
 {
    barValue += 1;
    if(barValue > 255) barValue = 255;
    analogWrite(LEFT_BAR,  barValue);
    analogWrite(RIGHT_BAR, barValue);
 }
void LedMenu::_rightPress()
{
    barValue -= 1;
    if(barValue < 0) barValue = 0;
    analogWrite(LEFT_BAR,  barValue);
    analogWrite(RIGHT_BAR, barValue);
}
void LedMenu::_okPress()
{
    barMode = !barMode;
    if(barMode)
    {
        pinMode(LEFT_DOTMODE,  INPUT);
        pinMode(RIGHT_DOTMODE, INPUT);        
    }
    else
    {
        pinMode(LEFT_DOTMODE,  OUTPUT); digitalWrite(LEFT_DOTMODE,  HIGH);
        pinMode(RIGHT_DOTMODE, OUTPUT); digitalWrite(RIGHT_DOTMODE, HIGH);
    }
}

void LedMenu::okAction(void *arg)
{
    //LedMenu *ledMenu = static_cast<LedMenu*>(arg);
}

void LedMenu::backAction(void *arg)
{
    //LedMenu *ledMenu = static_cast<LedMenu*>(arg);
}