// Опциональные дефайн-настройки (показаны по умолчанию)
//#define EB_FAST 30     // таймаут быстрого поворота, мс
//#define EB_DEB 50      // дебаунс кнопки, мс
//#define EB_CLICK 400   // таймаут накликивания, мс

#include <EncButton.h>
EncButton<EB_TICK, 2, 3, 4> enc;  // энкодер с кнопкой <A, B, KEY>
//EncButton<EB_TICK, 2, 3> enc;     // просто энкодер <A, B>
//EncButton<EB_TICK, 4> enc;        // просто кнопка <KEY>

//Работаем с дисплеем
#include <iarduino_OLED_txt.h>                         // Подключаем библиотеку iarduino_OLED_txt.
iarduino_OLED_txt myOLED(0x78);                        // Объявляем объект myOLED, указывая адрес дисплея на шине I2C: 0x78).
extern uint8_t SmallFontRus[];                         // Подключаем шрифт SmallFontRus.



void setup() {
  Serial.begin(9600);
  //enc.setButtonLevel(HIGH);     // уровень кнопки: LOW - кнопка подключает GND (по умолч.), HIGH - кнопка подключает VCC
  //enc.setHoldTimeout(1000);     // установить время удержания кнопки, мс (до 8 000)
  //enc.setStepTimeout(500);      // установить период импульсов step, мс (до 4 000)

  //enc.holdEncButton(true);      // виртуально зажать кнопку энкодера (для срабатывания нажатых поворотов)
  //enc.setEncReverse(true);      // true - инвертировать направление энкодера (умолч. false)
  //enc.setEncType(EB_HALFSTEP);  // тип энкодера: EB_FULLSTEP (0) по умолч., EB_HALFSTEP (1) если энкодер делает один поворот за два щелчка
  
  myOLED.begin();                                    // Инициируем работу с дисплеем.
  myOLED.setFont(SmallFontRus);                      // Указываем шрифт который требуется использовать для вывода цифр и текста.
}

void loop() {
  enc.tick();                     // опрос происходит здесь

  // =============== ЭНКОДЕР ===============
  // обычный поворот
  if (enc.turn()) {
    myOLED.clrScr();    
    Serial.println("turn");
    myOLED.print("turn",0, 0);
    // можно ещё:
    Serial.println(enc.counter);  // вывести счётчик
    myOLED.print(enc.counter,  0, 1); 
    Serial.println(enc.fast());   // проверить быстрый поворот
    myOLED.print(enc.fast(),  0, 2); 
    Serial.println(enc.dir());    // вывести направление поворота
    myOLED.print(enc.dir(),  0, 3); 
  }

  // "нажатый поворот"
  if (enc.turnH()) {
    Serial.println("hold + turn");
    myOLED.clrScr();    
    myOLED.print("hold + turn",  OLED_C , 4);
    }

  if (enc.left()) Serial.println("left");     // поворот налево
  if (enc.right()) Serial.println("right");   // поворот направо
  if (enc.leftH()) Serial.println("leftH");   // нажатый поворот налево
  if (enc.rightH()) Serial.println("rightH"); // нажатый поворот направо

  // =============== КНОПКА ===============
  if (enc.press()) {
    Serial.println("press");
    myOLED.clrScr();    
    myOLED.print("press key",  OLED_C , 5);
  }
  if (enc.click()) {
    Serial.println("click");
    myOLED.clrScr();    
    myOLED.print("click",  OLED_C , 6);
  }
  if (enc.release()) { 
    Serial.println("release");
  }

  if (enc.held()) Serial.println("held");     // однократно вернёт true при удержании
  //if (enc.hold()) Serial.println("hold");   // будет постоянно возвращать true после удержания
  if (enc.step()) Serial.println("step");     // импульсное удержание
  if (enc.releaseStep()) Serial.println("release step");  // отпущена после импульсного удержания
  
  // проверка на количество кликов
  if (enc.hasClicks(1)) Serial.println("action 1 clicks");
  if (enc.hasClicks(2)) Serial.println("action 2 clicks");

  // вывести количество кликов
  if (enc.hasClicks()) {
    Serial.print("has clicks ");
    Serial.println(enc.clicks);
    //myOLED.clrScr();    
    myOLED.print(enc.clicks,  OLED_C ,7);
  }
}
