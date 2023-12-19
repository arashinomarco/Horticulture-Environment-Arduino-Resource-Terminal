#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <TMRpcm.h>
#include <Keypad.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHTPIN dht(DHTPIN, DHTTYPE);

#define LM393_DO_PIN 3
#define HC_SR04_TRIG_PIN 7
#define HC_SR04_ECHO_PIN 8
#define SPEAKER_PIN 6
#define SD_CS_PIN 25

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'U', 'R', '-', '+'},
  {'>', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'<', '7', '4', '1'}
};
byte rowPins[ROWS] = {39, 42, 40, 44};
byte colPins[COLS] = {45, 43, 41, 38};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

TMRpcm tmrpcm;

void playAudio(const char* filenames[], int numFiles) {
  tmrpcm.setVolume(10);
  if (!SD.begin(SD_CS_PIN)) {
    while (true) {
    }
  }

  int randomIndex = random(0, numFiles);
  tmrpcm.play(filenames[randomIndex]);
  while (tmrpcm.isPlaying()) {
    delay(100);
  }
  tmrpcm.stopPlayback();
}

void printLCD(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void animateSadFace() {
  lcd.setCursor(15, 1);
  lcd.write(0);

  const char* sadAudioFiles[] = {
    "sprout_logoutsound000.mp3",
    "sprout_logoutsound001.mp3",
    "sprout_logoutsound002.mp3",
    "sprout_logoutsound003.mp3",
    "sprout_logoutsound004.mp3",
    "sprout_obstruction.mp3",
    "sprout_programmingerror.mp3"
  };

  playAudio(sadAudioFiles, sizeof(sadAudioFiles) / sizeof(sadAudioFiles[0]));
}

void animateHappyFace() {
  lcd.setCursor(15, 1);
  lcd.write(1);

  const char* happyAudioFiles[] = {
    "sprout_logoutsound000.mp3",
    "sprout_logoutsound001.mp3",
    "sprout_logoutsound002.mp3",
    "sprout_logoutsound003.mp3",
    "sprout_logoutsound004.mp3",
    "sprout_obstruction.mp3",
    "sprout_programmingerror.mp3"
  };

  playAudio(happyAudioFiles, sizeof(happyAudioFiles) / sizeof(happyAudioFiles[0]));
}

void initializeCircuit() {
  lcd.begin(16, 2);
  printLCD("♥ Project HEART ♥", "by Group 3");
  delay(1000);

  const char* audioFiles[] = {
    "sprout_iliketrees.mp3",
    "sprout_logonsound000.mp3",
    "sprout_logonsound001.mp3",
    "sprout_logonsound002.mp3",
    "sprout_logonsound003.mp3",
    "sprout_logonsound004.mp3",
    "sprout_nature.mp3",
    "sprout_pathcleared.mp3",
    "sprout_planting.mp3",
    "sprout_testcompleted.mp3"
  };
  int numAudioFiles = sizeof(audioFiles) / sizeof(audioFiles[0]);

  playAudio(audioFiles, numAudioFiles);

  if (SD.begin(SD_CS_PIN)) {
    playAudio(audioFiles, numAudioFiles);
  } else {
    printLCD("Uh oh...", "SD Card Error");
    animateSadFace();
    delay(1000);
    while (true);
  }

  printLCD("♥ Project HEART ♥", "Initializing...");
  animateHappyFace();
  delay(random(1000, 5000));
  playAudio(audioFiles, numAudioFiles);
}

void handleHCSR04() {
  lcd.clear();
  lcd.print("HC-SR04 Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(random(1000, 5000));
  
  const char* initialAudioFiles[] = {
    "sprout_fertilizing.mp3",
    "sprout_flower.mp3",
    "sprout_hello.mp3",
    "sprout_iliketrees.mp3",
    "sprout_nature.mp3",
    "sprout_planting.mp3",
    "sprout_returningtodock.mp3",
  };
  int numInitialAudioFiles = sizeof(initialAudioFiles) / sizeof(initialAudioFiles[0]);

  playAudio(initialAudioFiles, numInitialAudioFiles);

  if (!SD.begin(SD_CS_PIN)) {
    printLCD("Uh oh...", "SD Card Error");
    animateSadFace();
    delay(1000);
    while (true);
  }

  printLCD("♥ Project HEART ♥", "Initializing...");
  animateHappyFace();
  delay(random(1000, 5000));

  int distance = readHCSR04Distance();

  lcd.clear();
  lcd.print("HC-SR04 Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  int selectedLanguageAndGender = setUpLanguage();
  int selectedLanguage = selectedLanguageAndGender / 10;
  int selectedGender = selectedLanguageAndGender % 10;

  const char* folder = "";
  const char* language = "";
  const char* gender = "";

  switch (selectedLanguage) {
    case 1:
      folder = "English";
      language = "english";
      break;
    case 2:
      folder = "Tagalog";
      language = "tagalog";
      break;
    case 3:
      folder = "Ilokano";
      language = "ilokano";
      break;
    case 4:
      folder = "Pangasinense";
      language = "pangasinense";
      break;
    case 5:
      folder = "Bikolano";
      language = "bikolano";
      break;
    case 6:
      folder = "Bisaya";
      language = "bisaya";
      break;
  }

  switch (selectedGender) {
    case 1:
      gender = "male";
      break;
    case 2:
      gender = "female";
      break;
  }

  char audioFileName[50];
  int distanceCategory = (distance / 5) * 5;

  if (distanceCategory < 50) {
    lcd.setCursor(0, 2);
    lcd.print("Status: Too Low");
    sprintf(audioFileName, "%svoice_waterleveltoolow_%s.mp3", gender, language);
  } else if (distanceCategory < 100) {
    lcd.setCursor(0, 2);
    lcd.print("Status: Low");
    sprintf(audioFileName, "%svoice_waterlevellow_%s.mp3", gender, language);
  } else if (distanceCategory < 150) {
    lcd.setCursor(0, 2);
    lcd.print("Status: Moderate");
    sprintf(audioFileName, "%svoice_waterlevelmoderate_%s.mp3", gender, language);
  } else if (distanceCategory < 200) {
    lcd.setCursor(0, 2);
    lcd.print("Status: High");
    sprintf(audioFileName, "%svoice_waterlevelhigh_%s.mp3", gender, language);
  } else {
    lcd.setCursor(0, 2);
    lcd.print("Status: Too High");
    sprintf(audioFileName, "%svoice_waterleveltoohigh_%s.mp3", gender, language);
  }

  playAudio(folder, audioFileName);

  lcd.setCursor(0, 3);
  lcd.print("Press * to go back");
  lcd.setCursor(0, 4);
  lcd.print("# to stay");

  char key = '\0';
  while (key != '#' && key != '*') {
    key = keypad.getKey();
  }
}

int readHCSR04Distance() {
  const int trigPin = 9;
  const int echoPin = 10;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  // The average speed of sound is approximately 343 meters per second (or 0.0343 cm per microsecond), divide it by 2 to get distance.

  int calculatedDistance = duration * 0.0343 / 2;

  return calculatedDistance;
}

void handleLM393() {
  lcd.clear();
  lcd.print("LM393 Soil Moisture Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(random(1000, 5000));

  int sensorReading = readLM393SoilMoisture();

  lcd.clear();
  lcd.print("LM393 Soil Moisture Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Moisture Level: ");
  lcd.print(sensorReading);
  lcd.print("%");

  int selectedLanguageAndGender = setUpLanguage();
  int selectedLanguage = selectedLanguageAndGender / 10;
  int selectedGender = selectedLanguageAndGender % 10;

  const char* status;
  if (sensorReading >= 0 && sensorReading <= 20) {
    status = "Too Low";
  } else if (sensorReading <= 40) {
    status = "Low";
  } else if (sensorReading <= 60) {
    status = "Moderate";
  } else if (sensorReading <= 80) {
    status = "High";
  } else {
    status = "Extremely High";
  }

  char audioFileName[50];
  sprintf(audioFileName, "lm393_audio/voice_moisture%s_%s.mp3", status, language);

  lcd.setCursor(0, 0);
  lcd.print("Status: ");
  lcd.print(status);

  playAudio("lm393_audio", audioFileName);

  lcd.setCursor(0, 1);
  lcd.print("Press + to go back");
  lcd.setCursor(0, 4);
  lcd.print("- to stay");

  char key = '\0';
  while (key != '#' && key != '*') {
    key = keypad.getKey();
  }
}

int readLM393SoilMoisture() {
  return random(0, 101);
}

void handleDHT11(int sensorType) {
  lcd.clear();
  lcd.print("DHT11 Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  dht.begin();

  float value;

  if (sensorType == 1) {
    value = dht.readTemperature();
    lcd.clear();
    lcd.print("DHT11 Sensor");
    lcd.setCursor(0, 1);
    lcd.print("Temperature: ");
    lcd.print(value);
    lcd.print("°C");
  } else if (sensorType == 2) {
    value = dht.readHumidity();
    lcd.clear();
    lcd.print("DHT11 Sensor");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(value);
    lcd.print("%");
  }

  const char* status;
  if (sensorType == 1) {
    if (value < 20) {
      status = "toolow";
    } else if (value < 40) {
      status = "low";
    } else if (value < 60) {
      status = "moderate";
    } else if (value < 80) {
      status = "high";
    } else {
      status = "toohigh";
    }
  } else if (sensorType == 2) {
    if (value < 20) {
      status = "toolow";
    } else if (value < 40) {
      status = "low";
    } else if (value < 60) {
      status = "moderate";
    } else if (value < 80) {
      status = "high";
    } else {
      status = "toohigh";
    }
  }

  char audioFileName[50];
  sprintf(audioFileName, "dht11_audio/voice_waterlevel%s.mp3", status);

  switch (sensorType) {
    case 1: // Temperature
      lcd.setCursor(0, 0);
      lcd.print("Temperature Status: ");
      break;
    case 2: // Humidity
      lcd.setCursor(0, 0);
      lcd.print("Humidity Status: ");
      break;
  }
  lcd.print(status);

  playAudio(audioFileName);

  lcd.setCursor(0, 0);
  lcd.print("Press + to go back");
  lcd.setCursor(0, 1);
  lcd.print("- to stay");

  char key = '\0';
  while (key != '#' && key != '*') {
    key = keypad.getKey();
  }
}

void setup() {
  initializeCircuit();
  int selectedLanguage = setUpLanguage();
}

void loop() {
  initializeCircuit();

  setUpLanguage();

  lcd.clear();
  lcd.print("1- LM393\n2- HC-SR04\n3- DHT11 Temp\n4- DHT11 Humidity");
  playAudio("sensors", "choose_sensor.mp3");

  int selectedSensor = 0;
  char key = '\0';

  while (key != '#') {
    key = handleButtonPress();
    if (key != '\0') {
      lcd.clear();
      lcd.print("Selected: ");
      lcd.print(key);
      delay(1000);
      selectedSensor = key - '0';
      break;
    }
  }

  switch (selectedSensor) {
    case 1:
      handleLM393();
      break;
    case 2:
      handleHCSR04();
      break;
    case 3:
      handleDHT11(1);
      break;
    case 4:
      handleDHT11(2);
      break;
    default:
      break;
  }
