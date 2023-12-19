#include <SPI.h>
#include <SD.h>

const int chipSelect = 10; // CS pin

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
