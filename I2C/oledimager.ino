#include <OLED_I2C.h>

OLED  myOLED(SDA, SCL, 8);

extern uint8_t SmallFont[];
 
void setup()
{
  myOLED.begin();
  myOLED.setFont(SmallFont);
  
//  myOLED.fillScr();
//  myOLED.setPixel(10, 10);
//  myOLED.print("A", 50, 20);  
  myOLED.print("Hello", 50, 20); 
//  myOLED.printNumI(1234, 50, 20);
//  myOLED.printNumF(12.55, 2, 50, 20);
//  myOLED.drawLine(20, 10, 40, 10);
//  myOLED.drawRect(20, 10, 40, 50);
//  myOLED.drawRoundRect(20, 10, 40, 50);
//  myOLED.drawCircle(30, 30, 20);
 
//  myOLED.invertText(1);
//  myOLED.print("Hello", 50, 20); 
  
  myOLED.update();
  
}

void loop()
{
  
}
