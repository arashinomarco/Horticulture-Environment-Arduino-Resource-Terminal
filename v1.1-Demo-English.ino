// LCD not included...

#include <Keypad.h>
#include <DHT.h>

const int soilMoisturePin = A0;
const int trigPin = 7;
const int echoPin = 8;

int soilMoistureValue;
DHT dht(4, DHT11);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'R', 'U', '-', '+'},
  {'9', '>', '6', '3'},
  {'8', '0', '5', '2'},
  {'7', '<', '4', '1'}
};
byte rowPins[ROWS] = {39, 42, 40, 44};
byte colPins[COLS] = {45, 43, 41, 38};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int currentSensor = 1; 

void startReadings() {
  
  while (true) {
    int moisturePercentage;
    int distance;
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    char key = keypad.waitForKey();
    if (key == 'R') {
      break;
    }

    switch (key) {
      case '1':
        currentSensor = 1;
        break;
      case '2':
        currentSensor = 2;
        break;
      case '3':
        currentSensor = 3;
        break;
      case '4':
        currentSensor = 4;
        break;
    }

    switch (currentSensor) {
      case 1:

        Serial.print("Reading Temperature: ");
        Serial.print(temperature);
        Serial.println("°C.");

          if (temperature < 10) {
    Serial.println("The environment's temperature reading is too cold for your plant, which may hinder its growth and health.");
         } else if (temperature < 20) {
    Serial.println("The environment's temperature reading is cool, this may be ideal for some plants.");
         } else if (temperature < 25) {
    Serial.println("The environment's temperature reading is moderate, providing comfortable conditions for your plant.");
         } else if (temperature < 30) {
    Serial.println("The environment's temperature reading is warm, this is suitable for your plant's growth.");
         } else {
    Serial.println("The environment's temperature reading is too hot, this may harm your plant due to excessive heat.");
         }

        break;
      
      case 2:

        Serial.print("Reading Humidity: ");
        Serial.print(humidity);
        Serial.println("%.");

        if (humidity < 30) {
    Serial.println("The environment's humidity level is too low, this may not provide sufficient moisture for your plant's health.");
        } else if (humidity < 40) {
    Serial.println("The environment's humidity level is low, this may not provide adequate moisture for your plant's health.");
        } else if (humidity < 60) {
    Serial.println("The environment's humidity level is moderate, creating an ideal environment for your plant to thrive.");
        } else if (humidity < 80) {
    Serial.println("The environment's humidity level is relatively high, this can be favorable for your plant's growth.");
        } else {
    Serial.println("The environment's humidity level is too high, potentially leading to excessive moisture and affecting your plant's development.");
        }


        break;
      
      case 3:

        soilMoistureValue = analogRead(soilMoisturePin);
        moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
        Serial.print("Reading Soil Moisture: ");
        Serial.print(moisturePercentage);
        Serial.println("%.");

        if (moisturePercentage < 20) {
    Serial.println("The soil moisture level is too low, water the plant immediately.");
        } else if (moisturePercentage < 40) {
    Serial.println("The soil moisture level is low, water the plant to support plant growth.");
        } else if (moisturePercentage < 60) {
    Serial.println("The soil moisture level is moderate, providing suitable conditions for plant health.");
        } else if (moisturePercentage < 80) {
    Serial.println("The soil moisture level is high, creating a favorable environment for plants to thrive.");
        } else {
    Serial.println("The soil moisture level is excessively high, potentially leading to waterlogged soil and plant stress.");
        }

        break;

      case 4:
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);

        digitalWrite(trigPin, LOW);
        long duration = pulseIn(echoPin, HIGH);
        distance = duration * 0.034 / 2;

        Serial.print("Reading Water Level: ");
        Serial.print(distance);
        Serial.println(" cm.");

        if (distance < 5) {
    Serial.println("The water level in the container is too low, please refill the water supply immediately.");
        } else if (distance < 10) {
    Serial.println("The water level in the container is low, prepare to refill the water supply.");
        } else if (distance < 12) {
    Serial.println("The water level in the container is at a moderate level, you still have enough water for intended use.");
        } else if (distance < 14) {
    Serial.println("The water level in the container is high, you have enough water for your needs.");
        } else {
    Serial.println("The water level in the container is excessively high, please drain the water supply immediately.");
        }

        break;
    }

    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  startReadings();
}
