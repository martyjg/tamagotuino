#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int feedButton = 6;
int fullness = 10;
bool isHungry = false;

int activatedFeedButton = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(feedButton, INPUT);
  

}

void loop() {

  activatedFeedButton = digitalRead(feedButton);
//      if (activatedFeedButton == HIGH) {
//      fullness = 10;
//    }

  
  if (fullness <= 0) {
    diedDisplay();
  } else if (fullness < 6) {
    gettingHungryDisplay();
    isHungry = true;
    live();
  } else {
    contentDisplay();
    live();
  }

    if (activatedFeedButton == HIGH && isHungry == true) {
      isHungry = false;
      fullness = 10;
    }
}

void live() {
  delay(800);
  fullness--;
}

void feed() {
  fullness = 10;
}

void contentDisplay() {
  lcd.clear();
  lcd.print("Pet is content");
  lcd.setCursor(0, 1);
  lcd.print("(^_^)");
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

