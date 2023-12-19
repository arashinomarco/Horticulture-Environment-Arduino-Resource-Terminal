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
    Serial.println("Nalamiis unay ti temperatura ti aglawlaw para iti mulam, napeggad dayta iti mula ken mabalin a lapdanna ti panagdakkelna.");
         } else if (temperature < 20) {
    Serial.println("Nalamiis ti temperatura ti aglawlaw, a mabalin a nasayaat para iti dadduma a mula.");
         } else if (temperature < 25) {
    Serial.println("Kalkalainganna ti temperatura ti aglawlaw, mangipaay dayta iti komportable a kasasaad para iti mulam.");
         } else if (temperature < 30) {
    Serial.println("Nabara ti temperatura ti aglawlaw, maibagay dayta iti panagdakkel ti mulam.");
         } else {
    Serial.println("Napudot unay ti temperatura ti aglawlaw, mabalin a dadaelenna ti mulam gapu iti nalabes a pudot.");
         }

        break;

      case 2:

        Serial.print("Reading Humidity: ");
        Serial.print(humidity);
        Serial.println("%.");

        if (humidity < 30) {
    Serial.println("Nababa unay ti dam-eg ti aglawlaw, mabalin a saan nga umdas ti agnebna para iti salun-at ti mulam.");
        } else if (humidity < 40) {
    Serial.println("Nababa ti dam-eg ti aglawlaw, a mabalin a saan nga umdas ti agneb para iti salun-at ti mulam.");
        } else if (humidity < 60) {
    Serial.println("Kalkalainganna ti kinadam-eg ti aglawlaw, a mangpataud iti nasayaat nga aglawlaw tapno rumang-ay ti mulam.");
        } else if (humidity < 80) {
    Serial.println("Medio nangato ti dam-eg ti aglawlaw, a mabalin a matarigagayan para iti panagdakkel ti mulam.");
        } else {
    Serial.println("Nangato unay ti dam-eg ti aglawlaw, mabalin nga agtungpal dayta iti sobra a agneb ken apektaranna ti panagdakkel ti mulam.");
        }


        break;
        
      case 3:

        soilMoistureValue = analogRead(soilMoisturePin);
        moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
        Serial.print("Reading Soil Moisture: ");
        Serial.print(moisturePercentage);
        Serial.println("%.");

        if (moisturePercentage < 20) {
    Serial.println("Nababa unay ti soil moisture level, sibugan a dagus ti mula.");
        } else if (moisturePercentage < 40) {
    Serial.println("Nababa ti lebel ti agneb ti daga, sibugan ti mula tapno suportaran ti panagdakkel ti mula.");
        } else if (moisturePercentage < 60) {
    Serial.println("Kalkalainganna ti lebel ti agneb ti daga, a mangipaay kadagiti maitutop a kasasaad para iti salun-at ti mula.");
        } else if (moisturePercentage < 80) {
    Serial.println("Nangato ti lebel ti agneb ti daga, a mangpataud iti paborable nga aglawlaw tapno rumang-ay dagiti mula.");
        } else {
    Serial.println("Nalabes ti kangato ti lebel ti agneb ti daga, a mabalin nga agtungpal iti nadanum a daga ken stress ti mula.");
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
    Serial.println("Nababa unay ti water level iti container, pangngaasiyo ta punnuenyo a dagus ti suplay ti danum.");
        } else if (distance < 10) {
    Serial.println("Nababa ti lebel ti danum iti pagkargaan, agsagana a mangpunno manen iti suplay ti danum.");
        } else if (distance < 12) {
    Serial.println("Ti lebel ti danum iti pagkargaan ket adda iti kalalainganna a lebel, adda pay laeng umdas a danummo para iti nairanta a pannakausar.");
        } else if (distance < 14) {
    Serial.println("Nangato ti lebel ti danum iti pagkargaan, umdas ti danummo para kadagiti kasapulam.");
        } else {
    Serial.println("Nangato unay ti water level iti container, pangngaasiyo ta iruaryo a dagus ti suplay ti danum.");
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
