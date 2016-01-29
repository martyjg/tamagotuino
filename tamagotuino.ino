#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int fullness = 10;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Pet is content");
  lcd.setCursor(0, 1);
  lcd.print("(^_^)");
}

void loop() {
  if (fullness <= 0) {
    diedDisplay();
  } else if (fullness < 5) {
    gettingHungryDisplay();
  }
live();

}

void live() {
  delay(500);
  fullness--;
}

void gettingHungryDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Getting hungry");
  lcd.setCursor(0, 1);
  lcd.print("(o_o)");
}

void diedDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You messed up...");
  lcd.setCursor(0, 1);
  lcd.print("(X_X)");
}

