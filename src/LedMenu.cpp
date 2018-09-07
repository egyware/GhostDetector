#include "LedMenu.h"
#include "main.h"


LedMenu::LedMenu():barMode(0),barValue(0), currentIndex(0)
{
}

void LedMenu::init()
{  
    done = false;
    pinMode(3, OUTPUT); digitalWrite(3, HIGH);
    pinMode(4, OUTPUT); digitalWrite(4, HIGH);
    analogWrite(5, 0);
    analogWrite(6, 0);
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
    if(isNavMenu())
    {
        switch(navMenuIndex)
        {
            case 0:
            lcd.fillRect(5, 38, 35, 10, BLACK); lcd.setCursor(11, 40); lcd.setTextColor(WHITE); lcd.print("Ok");
            lcd.drawRect(44,38, 35, 10, BLACK); lcd.setCursor(47, 40); lcd.setTextColor(BLACK); lcd.print("Atras");
            break;
            case 1:
            lcd.drawRect(5, 38, 35, 10, BLACK); lcd.setCursor(11, 40); lcd.setTextColor(BLACK); lcd.print("Ok");
            lcd.fillRect(44,38, 35, 10, BLACK); lcd.setCursor(47, 40); lcd.setTextColor(WHITE); lcd.print("Atras");
            break;
        }
    }
    else
    {
        lcd.drawRect(5, 38, 35, 10, BLACK); lcd.setCursor(11, 40); lcd.print("Ok");
        lcd.drawRect(44,38, 35, 10, BLACK); lcd.setCursor(47, 40); lcd.print("Atras");
    }
    lcd.display();    
}
void LedMenu::end()
{
}

 void LedMenu::_leftPress()
 {
    barValue += 1;
    if(barValue > 255) barValue = 255;
    analogWrite(5, barValue);
    analogWrite(6, barValue);
 }
void LedMenu::_rightPress()
{
    barValue -= 1;
    if(barValue < 0) barValue = 0;
    analogWrite(5, barValue);
    analogWrite(6, barValue);
}
void LedMenu::_okPress()
{
    barMode = !barMode;
    if(barMode)
    {
        pinMode(3, INPUT);
        pinMode(4, INPUT);        
    }
    else
    {
        pinMode(3, OUTPUT); digitalWrite(3, HIGH);
        pinMode(4, OUTPUT); digitalWrite(4, HIGH);
    }
}