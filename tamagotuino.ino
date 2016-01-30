#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int feedButton = 6;
const int heatSensor = A0;
const float baselineTemp = 22.0;
int fullness = 10;
float rawTemperature;
int temperature;
bool isHungry;
bool isCold;

int activatedFeedButton = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(feedButton, INPUT);

  checkTemperature();

  contentDisplay();

}

void loop() {

  activatedFeedButton = digitalRead(feedButton);
  int heatValue = analogRead(heatSensor);
  Serial.print("Sensor Value: ");
  Serial.print(heatValue);

  checkTemperature();
  
  if (fullness <= 0) {
    diedDisplay();
  } else if (fullness < 6) {
    gettingHungryDisplay();
    isHungry = true;
    live();
  } else if (isCold == true) {
    gettingColdDisplay();
  } else {
    contentDisplay();
    live();
  }

  if (activatedFeedButton == HIGH && isHungry == true) {
    isHungry = false;
    fullness = 30;
  }
  
}

void live() {
  delay(500);
  fullness--;
}

void feed() {
  fullness = 10;
}

void checkTemperature() {
  int heatValue = analogRead(heatSensor);
  float voltage = (heatValue/1024.0) * 5;
  rawTemperature = (voltage -.5) * 100;
  Serial.print(", Volts: ");
  Serial.print(voltage);
  temperature = (int) rawTemperature;
  
  if (temperature < 24) {
    isCold = true;
  } else {
    isCold = false;
  }
  
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

void gettingColdDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Getting cold");
  lcd.setCursor(0, 1);
  lcd.print("(~_~)");
  delay(100);
}

void diedDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You messed up...");
  lcd.setCursor(0, 1);
  lcd.print("(X_X)");
}

