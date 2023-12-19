#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <dht.h>

#define TRIG_PIN 7
#define ECHO_PIN 8
#define LM393_DO_PIN 2
#define DHT11_PIN 3
#define BUTTON_PIN A0
#define SPEAKER_PIN 6
#define ROW_PINS {4, 5, 6, 9}
#define COL_PINS {A1, A2, A3, A4}
#define ASTABLE_PIN 3

LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;

void setup() {
  lcd.begin(16, 2);
  lcd.print("project heart");
  delay(1000);

  waitForButtonPress();

  lcd.clear();
  lcd.print("1 - English");
  lcd.setCursor(0, 1);
  lcd.print("2 - Tagalog");
  
  char language = waitForButtonPress();
  lcd.clear();

  lcd.print("Select Sensor:");
  lcd.setCursor(0, 1);
  lcd.print("1 - LM393");

  char selectedSensor = waitForButtonPress();

  switch (selectedSensor) {
    case '1':
      setupLM393();
      break;

    default:
      break;
  }
}

void loop() {
}

void setupLM393() {
  lcd.clear();
  lcd.print("LM393 Sensor");
  delay(1000);

  lcd.clear();
  lcd.print("Detecting Range");

  pinMode(LM393_DO_PIN, INPUT);

  while (true) {
    int lm393Value = digitalRead(LM393_DO_PIN);

    int rangePercentage = map(lm393Value, LOW, HIGH, 0, 100);

    lcd.clear();
    lcd.print("LM393 Range: " + String(rangePercentage) + "%");
  
    playAudioBasedOnRange(rangePercentage);

    delay(1000);
  }
}

void playAudioBasedOnRange(int rangePercentage) {
  if (rangePercentage >= 0 && rangePercentage <= 20) {
    tone(SPEAKER_PIN, 1000);
  } else if (rangePercentage > 20 && rangePercentage <= 40) {
    tone(SPEAKER_PIN, 1500);
  } else if (rangePercentage > 40 && rangePercentage <= 60) {
    tone(SPEAKER_PIN, 2000);
  } else if (rangePercentage > 60 && rangePercentage <= 80) {
    tone(SPEAKER_PIN, 2500);
  } else if (rangePercentage > 80 && rangePercentage <= 100) {
    tone(SPEAKER_PIN, 3000);
  }
}

char waitForButtonPress() {
  char buttonValue = '0';
  while (digitalRead(BUTTON_PIN) == HIGH) {
  }

  delay(50);

  while (digitalRead(BUTTON_PIN) == LOW) {
    buttonValue = readButton();
  }

  delay(50);

  return buttonValue;
}

char readButton() {
  int adc_key_in = analogRead(BUTTON_PIN);
  if (adc_key_in < 100) return '1';
  if (adc_key_in < 200) return '2';
  if (adc_key_in < 400) return '3';
  if (adc_key_in < 600) return '4';
  return '0';
}
