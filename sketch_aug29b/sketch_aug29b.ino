#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

void setup() {
  lcd.begin(20, 5);
  lcd.print("hello, world!");
}

void loop() {
  lcd.home();
  lcd.print("XXX");
}

