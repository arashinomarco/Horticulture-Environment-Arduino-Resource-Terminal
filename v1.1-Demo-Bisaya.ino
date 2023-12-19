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
    Serial.println("Ang pagbasa sa temperatura sa palibot bugnaw kaayo alang sa imong tanum, nga mahimong makababag sa pagtubo ug kahimsog niini.");
         } else if (temperature < 20) {
    Serial.println("Ang pagbasa sa temperatura sa palibot kay bugnaw, kini mahimong maayo alang sa pipila ka mga tanum.");
         } else if (temperature < 25) {
    Serial.println("Ang pagbasa sa temperatura sa palibot kasarangan, nga naghatag komportable nga mga kondisyon alang sa imong tanum.");
         } else if (temperature < 30) {
    Serial.println("Ang pagbasa sa temperatura sa palibot init, kini angay alang sa pagtubo sa imong tanum.");
         } else {
    Serial.println("Ang pagbasa sa temperatura sa palibot init kaayo, kini mahimong makadaot sa imong tanum tungod sa sobra nga kainit.");
         }

        break;

      case 2:

        Serial.print("Reading Humidity: ");
        Serial.print(humidity);
        Serial.println("%.");

        if (humidity < 30) {
    Serial.println("Ang lebel sa humidity sa palibot ubos kaayo, dili kini makahatag og igong kaumog alang sa kahimsog sa imong tanum.");
        } else if (humidity < 40) {
    Serial.println("Ubos ang lebel sa humidity sa palibot, dili kini makahatag og igong kaumog alang sa kahimsog sa imong tanum.");
        } else if (humidity < 60) {
    Serial.println("Ang lebel sa humidity sa palibot kasarangan, nga nagmugna usa ka sulundon nga palibot alang sa imong tanum nga molambo.");
        } else if (humidity < 80) {
    Serial.println("Ang lebel sa humidity sa palibot medyo taas, kini mahimong paborable alang sa pagtubo sa imong tanum.");
        } else {
    Serial.println("Taas kaayo ang lebel sa humidity sa palibot, nga posibleng mosangpot sa sobrang kaumog ug makaapekto sa paglambo sa imong tanom.");
        }


        break;
        
      case 3:

        soilMoistureValue = analogRead(soilMoisturePin);
        moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
        Serial.print("Reading Soil Moisture: ");
        Serial.print(moisturePercentage);
        Serial.println("%.");

        if (moisturePercentage < 20) {
    Serial.println("Ang lebel sa kaumog sa yuta ubos kaayo, tubig dayon ang tanum.");
        } else if (moisturePercentage < 40) {
    Serial.println("Ang lebel sa kaumog sa yuta gamay, tubig ang tanum aron masuportahan ang pagtubo sa tanum.");
        } else if (moisturePercentage < 60) {
    Serial.println("Ang lebel sa kaumog sa yuta kasarangan, nga naghatag og angay nga kondisyon alang sa kahimsog sa tanum.");
        } else if (moisturePercentage < 80) {
    Serial.println("Ang lebel sa kaumog sa yuta taas, nga nagmugna og paborableng palibot alang sa mga tanum nga molambo.");
        } else {
    Serial.println("Ang lebel sa kaumog sa yuta sobra ka taas, nga mahimong mosangput sa tubig nga yuta ug stress sa tanum.");
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
    Serial.println("Ubos kaayo ang lebel sa tubig sa sudlanan, palihug pun-i dayon ang suplay sa tubig.");
        } else if (distance < 10) {
    Serial.println("Ang lebel sa tubig sa sudlanan ubos, pag-andam sa pagpuno sa suplay sa tubig.");
        } else if (distance < 12) {
    Serial.println("Ang lebel sa tubig sa sudlanan anaa sa kasarangan nga lebel, aduna ka pay igong tubig alang sa gituyo nga paggamit.");
        } else if (distance < 14) {
    Serial.println("Taas ang lebel sa tubig sa sudlanan, adunay ka igo nga tubig alang sa imong mga panginahanglan.");
        } else {
    Serial.println("Ang lebel sa tubig sa sudlanan sobra ka taas, palihug habwa dayon ang suplay sa tubig.");
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
