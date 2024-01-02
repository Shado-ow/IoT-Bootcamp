#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>
#include<DHTesp.h>

#include <DHT.h>

LiquidCrystal_I2C_Hangul lcd(0x27,16,2); //LCD 클래스 초기화

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.print("Hello World!");

}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.print("");
  lcd.print(" ");

}
