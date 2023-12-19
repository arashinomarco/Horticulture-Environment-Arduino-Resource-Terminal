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
    Serial.println("Say nalan bilang ya temperatura ay masyadong ambetel ed kapaligiran parad tanaman. Ya saragtong hadlangan su ikabaleg to ed kalusugan.");
         } else if (temperature < 20) {
    Serial.println("Say nalan ya bilang na temperatura ed kapaligiran ay ambetel , ayay bali baling pantanim.");
         } else if (temperature < 25) {
    Serial.println("No say nalam na bilang ya temperatura na dalin et komportablen maong, maabig so kipapasen na tanaman mo.");
         } else if (temperature < 30) {
    Serial.println(" No say nalam bilang ya temperature na kaliberliber et anpetang,  pian mabalibali so tubo ya tanaman.");
         } else {
    Serial.println("No say nalan datos ya temperatura na kaliberliber et pinasiya so petang, et nayarin makaderal ya tanem lapud  sobran petang.");
         }

        break;

      case 2:

        Serial.print("Reading Humidity: ");
        Serial.print(humidity);
        Serial.println("%.");

        if (humidity < 30) {
    Serial.println("Napakalubsab ya humidity, ag to ni iter ya kyun na need ki moisture para sa tanaman.");
        } else if (humidity < 40) {
    Serial.println("Lubsab ya humidity, ag to ni iter ya kyun na sapat na need ki moisture para sa tanaman.");
        } else if (humidity < 60) {
    Serial.println("Parehas labat ya humidity, ideal para tanaman binmaleg.");
        } else if (humidity < 80) {
    Serial.println("Tataguy ya humidity, masanting parag tanaman.");
        } else {
    Serial.println("Tataguy yi maong, potentially nakakadiral ud umbaleg ng tanaman.");
        }


        break;
        
      case 3:

        soilMoistureValue = analogRead(soilMoisturePin);
        moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
        Serial.print("Reading Soil Moisture: ");
        Serial.print(moisturePercentage);
        Serial.println("%.");

        if (moisturePercentage < 20) {
    Serial.println("An dalin ay masyadong mapituk, sa lug mo ramay tanaman ya tampot.");
        } else if (moisturePercentage < 40) {
    Serial.println("An dalin ay mapituk, sa lug mo tanaman para magano magano baleg ya tampot.");
        } else if (moisturePercentage < 60) {
    Serial.println("Say dalin ay tamang basa tu, masanting sa condition yan tanaman .");
        } else if (moisturePercentage < 80) {
    Serial.println("Say dalin ay ambasa basa, masanting yan tanaman baleg ay tampol.");
        } else {
    Serial.println("Say dalin too much ambasa basa, ta kyun su tanaman ke stress.");
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
    Serial.println("Say kin na danom alitsab ya maong, kargaan mo ramay panganinan danom.");
        } else if (distance < 10) {
    Serial.println("Say kin na danom alitsab na manaya, iprepare mo ramay pananginan danom.");
        } else if (distance < 12) {
    Serial.println("Say danom pagluy su lebel tu, wala na niy danom ah sapat supply.");
        } else if (distance < 14) {
    Serial.println("Taguy ang lebel ng danom sa pananingan, wala na niy danom yah sapat supply pangangailangan.");
        } else {
    Serial.println("Masyadong ataguy ang lebel ng danom, alisan mo ray danom sa supply.");
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
