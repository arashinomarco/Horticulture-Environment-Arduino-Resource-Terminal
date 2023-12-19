#include <SPI.h>
#include <SD.h>

const int chipSelect = 25

void setup() {
  Serial.begin(9600);

  if (SD.begin(chipSelect)) {
    Serial.println("SD card initialization successful.");
  } else {
    Serial.println("Error initializing SD card.");
  }
}

void loop() {
}
