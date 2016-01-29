#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int fullness = 1000;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Pet is content");
  lcd.setCursor(0, 1);
  lcd.print(fullness);
}

void loop() {
  fullness--;
  if (fullness < 50) {
    lcd.clear();
    lcd.print("Pet is getting hungry...");
  }

}

