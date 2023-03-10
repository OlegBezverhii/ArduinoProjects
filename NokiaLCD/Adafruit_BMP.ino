#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

static const unsigned char PROGMEM bikeBmp[]=
{
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x80,0x3f,0xfc,0x3,
0xff,0xfc,0x0,0x7,0xf0,0x7,
0xff,0xf0,0x3f,0xf9,0xe0,0xe7,
0xff,0xe1,0xff,0xfe,0x43,0xef,
0xff,0x83,0xff,0xff,0x8f,0xdf,
0xff,0xf,0xff,0xff,0x9f,0xdf,
0xfe,0x1f,0xff,0xff,0x1f,0xff,
0xfc,0x3f,0xff,0xff,0x3f,0xff,
0xfd,0xff,0xff,0xfe,0x7f,0xff,
0xfe,0x7f,0xff,0xfe,0x7f,0xff,
0xf8,0x1f,0xff,0xfc,0xff,0xff,
0xf0,0x3f,0xff,0xfd,0xff,0xff,
0xf0,0x7f,0xff,0xf9,0xff,0x1f,
0xe0,0x7f,0xff,0xfb,0xf8,0x3,
0xe0,0x7f,0xff,0xf3,0xf0,0x7,
0xe0,0xff,0xff,0xf7,0xe0,0xf,
0xe0,0xff,0xff,0xef,0xc0,0x1f,
0xe0,0x7f,0xff,0xcf,0x80,0x1f,
0xc0,0x7f,0xff,0xdf,0x80,0x3f,
0xc0,0x7f,0xff,0x9f,0x0,0x7f,
0xe0,0x3f,0xff,0xbe,0x0,0x7,
0xe0,0x3f,0xff,0x7c,0x0,0x7,
0xe0,0x1f,0xfe,0xf8,0x0,0x7,
0xe0,0x1f,0xfc,0xf0,0x0,0xf,
0xe0,0xf,0xf9,0xe0,0x0,0x1f,
0xf0,0x7,0xf7,0xc0,0x0,0x3f,
0xf0,0x3,0xff,0x80,0x0,0x7f,
0xf0,0x1,0xfe,0x0,0x0,0x7f,
0xf8,0x0,0xe0,0x0,0x0,0xff,
0xfc,0x0,0x38,0x0,0x1,0xff,
0xfc,0x0,0xe,0x0,0x7,0xff,
0xfe,0x0,0x3,0xe0,0xf,0xff,
0xff,0x0,0x0,0x1e,0x1f,0xff,
0xff,0x80,0x0,0x0,0x3f,0xff,
0xff,0xc0,0x0,0x0,0x7f,0xff,
0xff,0xf0,0x0,0x1,0xff,0xff,
0xff,0xfc,0x0,0x3,0xff,0xff,
0xff,0xff,0x0,0x1f,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff
};


Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);

void setup() {
    display.begin();
    display.cp437(true);
    display.setContrast(50); // установка контраста
    display.clearDisplay();
}

void loop() 
{
    display.clearDisplay();
    display.drawBitmap(0, 0, bikeBmp, 48, 48, BLACK);
//    display.drawBitmap(0, 20, bikeBmp, 20, 20, BLACK);
//    display.drawBitmap(0, 40, bikeBmp, 20, 20, BLACK);
    display.display();
    delay(500); // задержка в секунду
//  display.clearDisplay();
    
//    display.drawBitmap(50, 0, bikeBmp, 48, 48, BLACK);
//    display.display();
//    delay(1000);
//    display.clearDisplay();

    display.setTextColor(BLACK);
    display.setCursor(50,0);
    display.setTextSize(1);
    display.println(utf8rus("С"));
    delay(500); // задержка
    display.display();
    display.setCursor(50,10);
    display.println(utf8rus("новым"));
    delay(500); // задержка
    display.display();
    display.setCursor(50,20);
    display.println(utf8rus("годом"));
    delay(500); // задержка
    display.display();
    display.setCursor(50,30);
    display.println(utf8rus("ОСПАС"));
    delay(500); // задержка
    display.display();
    display.setCursor(50,40);
    display.println(utf8rus("ТН ДВ"));
    delay(500); // задержка
    display.display();
    delay(1000); // задержка
    display.clearDisplay();
//  display.clearDisplay();
    delay(1000); // 
}

/* Функция перевода UTF-8 to Windows-1251 */
String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
