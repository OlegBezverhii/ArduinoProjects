#include <iarduino_OLED_txt.h>                         // Подключаем библиотеку iarduino_OLED_txt.
iarduino_OLED_txt myOLED(0x3C);                        // Объявляем объект myOLED, указывая адрес дисплея на шине I2C: 0x78).
                                                       //
extern uint8_t SmallFontRus[];                         // Подключаем шрифт SmallFontRus.
                                                       //
void setup(){                                          //
    myOLED.begin();                                    // Инициируем работу с дисплеем.
    myOLED.setFont(SmallFontRus);                      // Указываем шрифт который требуется использовать для вывода цифр и текста.
//  myOLED.setCoding(TXT_UTF8);                        // Указываем кодировку текста в скетче. Если на дисплее не отображается Русский алфавит, то ...
}                                                      // раскомментируйте функцию setCoding и замените параметр TXT_UTF8, на TXT_CP866 или TXT_WIN1251.
                                                      
void loop(){                                           
    //myOLED.clrScr();                                   // Чистим экран.
    myOLED.print( "Привет!" ,  0, 0);    // Выводим текст начиная с 0 столбца 0 строки.
   
                                       
}                
