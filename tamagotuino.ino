#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int feedButton = 6;
const int heatSensor = A0;
const int temperatureThreshold = 23.0;
int fullness = 10;
float rawTemperature;
int temperature;
int pitch = 1000;
int cryCounter = 0;
bool isHungry;
bool isCold;
bool isDead;
bool soundOn = false;


int activatedFeedButton = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(feedButton, INPUT);
  for (int ledNumber = 8; ledNumber < 11; ledNumber++) {
    pinMode(ledNumber, OUTPUT);
    digitalWrite(ledNumber, LOW);
  }
  checkTemperature();
  contentDisplay();
}

void loop() {

  activatedFeedButton = digitalRead(feedButton);
  int heatValue = analogRead(heatSensor);
  float voltage = (heatValue/1024.0) * 5;
  rawTemperature = (voltage -.5) * 100;
  temperature = (int) rawTemperature;
  checkTemperature();
  if (isDead == false) ledStatus();
  
  if (fullness <= 0 || temperature < (temperatureThreshold - 5)) {
    if (cryCounter == 0 && soundOn == true) {
    deathCry();
    cryCounter++;
    }
    diedDisplay();
  } else if (fullness < 6) {
    gettingHungryDisplay();
    isHungry = true;
    if (soundOn == true) {
      gettingHungrySound();
    }
    live();
  } else if (isCold == true) {
    gettingColdDisplay();
    live();
  } else {
    contentDisplay();
    live();
  }

  if (activatedFeedButton == HIGH && isHungry == true) {
    feed();
  }
  
}

void live() {
  delay(500);
  fullness--;
}

void feed() {
  isHungry = false;
  fullness = 10;
}

void checkTemperature() {
  
  if (temperature < temperatureThreshold) {
    isCold = true;
  } else {
    isCold = false;
  }
  
}

void ledStatus() {
  Serial.print("THIS IS BEING CALLED");
  if (temperature >= temperatureThreshold) {
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  } else if (temperature <= (temperatureThreshold - 5)) {
    isDead = true;
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  } else if (temperature < (temperatureThreshold - 3)) {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
}

void gettingHungrySound() {
  tone(7, 100, 150);
  delay(150);
  tone(7, 150, 75);
  delay(75);
  tone(7, 160, 75);
}

void deathCry() {
  tone(7, 80, 150);
  delay(150);
  tone(7, 70, 150);
  delay(150);
  tone(7, 60, 450);
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
  delay(1000);
}

void diedDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You messed up...");
  lcd.setCursor(0, 1);
  lcd.print("(X_X)");
  delay(10000);
}

