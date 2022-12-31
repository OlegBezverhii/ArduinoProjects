/*
This is an example on how to use the display known as Nokia 5110 SPI with PCD8544 driver using the U8GLIB library.

Nokia 5110 SPI display pins for Arduino Uno/Nano:
 * RST =    8
 * CE =     10
 * DC =     9
 * DIN =    11
 * CLK =    13
 * VCC =    5V
 * LIGHT =  GROUND
 * GND =    GROUND

Hardware SPI Pins:
 * Arduino Uno   CLK=13, DIN=11
 * Arduino Nano  CLK=13, DIN=11
 * Arduino Due   CLK=76, DIN=75
 * Arduino Mega  CLK=52, DIN=51

There are some modules that label the backlight as "BL".
If that's the case, BL goes to 5V.

SPI pin names can be confusing. These are the alternative names for the SPI pins:
MOSI = DIN = R/W = SDO = DI = SI = MTSR = SDA = D1
CS = CE = RS = SS
DC = A0 = SDI = DO = DOUT = SO = MRST
RESET = RST
SCLK = CLK = E = SCK = SCL = D0


We use this library: https://github.com/olikraus/U8glib_Arduino

User Reference Manual: https://github.com/olikraus/u8glib/wiki/userreference
List of fonts: https://github.com/olikraus/u8glib/wiki/fontsize


This sketch was featured on my video tutorial for this display: https://www.youtube.com/watch?v=1ZvY_lb6BoU

Sketch made by: InterlinkKnight
Last modification: 11/22/2017
*/
 
#include "U8glib.h"  // Include U8glib library


// Create display and set pins:
U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);	 // (CLK=13, DIN=11, CE=10, DC=9, RST=8)

int Variable1;  // Create a variable to have something dynamic to show on the display


void setup(void)  // Start of setup
{

  // Select a font:
  // This is the list of fonts that support right text alignment:
  //u8g.setFont(u8g_font_profont12);
  //u8g.setFont(u8g_font_profont15);
  //u8g.setFont(u8g_font_profont17);
  //u8g.setFont(u8g_font_profont22);
  //u8g.setFont(u8g_font_profont29);
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_4x6);
  //u8g.setFont(u8g_font_5x7);
  //u8g.setFont(u8g_font_5x8);
  u8g.setFont(u8g_font_6x10);
  //u8g.setFont(u8g_font_6x12);
  //u8g.setFont(u8g_font_6x13);
  //u8g.setFont(u8g_font_6x13B);
  //u8g.setFont(u8g_font_6x13O);
  //u8g.setFont(u8g_font_7x13);
  //u8g.setFont(u8g_font_7x13B);
  //u8g.setFont(u8g_font_7x13O);
  //u8g.setFont(u8g_font_7x14);
  //u8g.setFont(u8g_font_7x14B);
  //u8g.setFont(u8g_font_8x13);
  //u8g.setFont(u8g_font_8x13B);
  //u8g.setFont(u8g_font_9x15);
  //u8g.setFont(u8g_font_9x15B);
  //u8g.setFont(u8g_font_9x18);
  //u8g.setFont(u8g_font_9x18B);
  //u8g.setFont(u8g_font_10x20);


  


  // Change display orientation:
  //u8g.setRot90();
  //u8g.setRot180();
  //u8g.setRot270();

}  // End of setup




void loop(void)  // Start of loop
{

  Variable1++;  // Increase variable by 1
  delay(1000);
  if(Variable1 > 150)  // If Variable1 is greater than 150
  {
    Variable1 = 0;  // Set Variable1 to 0
  }



  // Convert Variable1 into a string, so we can change the text alignment to the right:
  // It can be also used to add or remove decimal numbers.
  char string[10];  // Create a character array of 10 characters
  // Convert float to a string:
  dtostrf(Variable1, 3, 0, string);  // (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)


  
  u8g.firstPage(); // Beginning of the picture loop
  do  // Include all you want to show on the display:
  {

    u8g.drawStr(0, 7, "Hello World!");  // (x,y,"Text")
    u8g.drawBox(0, 9 ,25 , 15);  // Draw a filled square (x,y,width,height)
    u8g.drawRBox(0, 26, 17, 19, 3);  // Draw a filled rounded square (x,y,width,height,radius)
    u8g.drawCircle(41, 21, 12, U8G_DRAW_ALL);  // Draw a circle (x,y,radius,option)
    u8g.drawDisc(27, 38, 7, U8G_DRAW_ALL);  // Draw a filled circle (x,y,radius,option)
    u8g.drawTriangle(38,45,    48,34,    58,45);  // Draw a filled triangle (x0,y0,    x1,y1,    x2,y2)
    u8g.drawLine(0, 47, 83, 47);  // Draw a line (x0,y0,x1,y1)

    u8g.drawFrame(59, 10, 25, 13);  // Draw a square (x,y,width,height)
    // Variable with left text alignment:
    u8g.setPrintPos(63, 20);  // (x,y)
    u8g.print(Variable1);  // Value to print

    u8g.drawRFrame(59, 26, 25, 13, 3);  // Draw a rounded square (x,y,width,height,radius)
    // Variable with right text alignment:
    u8g.setPrintPos(63, 36);  // (x,y)
    u8g.print(string);  // Value to print



  } while(u8g.nextPage());  // End of the picture loop
  




  
}  // End of loop
