#include <SPI.h>

#define CS_PIN 10

// Команды M95512
#define CMD_READ  0x03  // Read Data
#define CMD_RDSR  0x05  // Read Status Register

bool testComplete = false;

// Размер памяти M95512: 64 KByte
#define MEMORY_SIZE 65535

void setup() {
  Serial.begin(9600); //
  while (!Serial) { ; }
  
  Serial.println(F("Чтение всей памяти M95512"));
  Serial.println(F("=========================="));
  
  // Настройка SPI
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV8); // 16/8=2
  
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); //Устанавливаем SlaveSelect в HIGH (то есть мастер не соединен с slave)
  
    // Быстрая проверка соединения
  if (!checkConnection()) {
    Serial.println(F("❌ ОШИБКА: Чип не отвечает!"));
    testComplete = true;
    return;
  }

  // Запуск чтения
  if(testComplete=true)
  {
    Serial.println(F("Переходим к тестам!"));
    readAllMemory();
  }

}


// Проверка соединения с чипом
bool checkConnection() {
  digitalWrite(CS_PIN, LOW); //Старт коммуникации с SLAVE
  SPI.transfer(CMD_RDSR);
  uint8_t status = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH); //Устанавливаем SlaveSelect в HIGH (то есть мастер не соединен с slave)
  
  if (status == 0xFF) return false;  // Нет ответа
  
  Serial.print(F("✅ Соединение установлено. Status Register: 0x"));
  Serial.println(status, HEX);
  return true;
}


void readAllMemory() {
  uint32_t bytesRead = 0;
  uint32_t startTime = millis();
  
  Serial.println(F("\nАдрес: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
  Serial.println(F("------- ------------------------------------------------"));
  
  // Читаем всю память блоками по 16 байт для красивого вывода
  for (uint16_t addr = 0; addr < MEMORY_SIZE; addr += 16) {
    // Выводим адрес
    if (addr < 0x1000) Serial.print(F("0"));
    if (addr < 0x100) Serial.print(F("0"));
    if (addr < 0x10) Serial.print(F("0"));
    Serial.print(addr, HEX);
    Serial.print(F(": "));
    
    // Читаем и выводим 16 байт
    for (int i = 0; i < 16; i++) {
      uint16_t currentAddr = addr + i;
      if (currentAddr < MEMORY_SIZE) {
        byte data = readByte(currentAddr);
        
        // Выводим байт в HEX
        if (data < 0x10) Serial.print(F("0"));
        Serial.print(data, HEX);
        Serial.print(F(" "));
        
        bytesRead++;
      } else {
        Serial.print(F("   ")); // Пропуск для несуществующих адресов
      }
    }
    
    // ASCII представление
    Serial.print(F(" |"));
    for (int i = 0; i < 16; i++) {
      uint16_t currentAddr = addr + i;
      if (currentAddr < MEMORY_SIZE) {
        byte data = readByte(currentAddr);
        if (data >= 32 && data <= 126) {
          Serial.write(data);
        } else {
          Serial.print(F("."));
        }
      }
    }
    Serial.println(F("|"));
    
    // Небольшая задержка для стабильности
    if (addr % 1024 == 0) {
      delay(20);
    }
  }
  
  uint32_t endTime = millis();
  float timeSec = (endTime - startTime) / 1000.0;
  
  Serial.println(F("\n=========================="));
  Serial.print(F("Прочитано байт: "));
  Serial.println(bytesRead);
  Serial.print(F("Время чтения: "));
  Serial.print(timeSec);
  Serial.println(F(" сек"));
  Serial.print(F("Скорость: "));
  Serial.print(bytesRead / timeSec / 1024);
  Serial.println(F(" KB/сек"));
}

byte readByte(uint16_t addr) {
  digitalWrite(CS_PIN, LOW);
  
  SPI.transfer(CMD_READ);
  SPI.transfer(addr >> 8);    // Старший байт адреса
  SPI.transfer(addr & 0xFF);   // Младший байт адреса
  
  byte data = SPI.transfer(0x00);
  
  digitalWrite(CS_PIN, HIGH);
  
  //delay(50);
  return data;
}

void loop() {
  // Ничего не делаем
}