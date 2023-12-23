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
    Serial.println("Malipoton ang temperatura na pwede makaraot sa pagbuhay kang tanom.");
         } else if (temperature < 20) {
    Serial.println("Malipot ang temperatura na tama para pagbuhay kang tanom.");
         } else if (temperature < 25) {
    Serial.println("Bako malipot asin bako mainit ang temperatura na tama sana pangbuhah ki tanom.");
         } else if (temperature < 30) {
    Serial.println("Mainit-int ang temperatura na tama sana para sa tanom.");
         } else {
    Serial.println("Mainiton ang temperatura na pwede ining makaraot sa buhay kang tanom.");
         }

        break;

      case 2:

        Serial.print("Reading Humidity: ");
        Serial.print(humidity);
        Serial.println("%.");

        if (humidity < 30) {
    Serial.println("Hababaon ang lebel kang humidity na dai kaini kayang buhayon ang tanom.");
        } else if (humidity < 40) {
    Serial.println("Hababa na sana ang lebel kang humidity, dae na mahusto ang moisture para buhayon ang tanom.");
        } else if (humidity < 60) {
    Serial.println("Tama sana ang lebel kang humidity para mabuhay ang mga tanom.");
        } else if (humidity < 80) {
    Serial.println("Dakol ang lebel kang humidity na marhay sa pagbuhay kang tanom.");
        } else {
    Serial.println("Dakulon ang lebel kang humidity na pwede ining makaapekto sa buhay kang tanom.");
        }


        break;
        
      case 3:

        soilMoistureValue = analogRead(soilMoisturePin);
        moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
        Serial.print("Reading Soil Moisture: ");
        Serial.print(moisturePercentage);
        Serial.println("%.");

        if (moisturePercentage < 20) {
    Serial.println("Diiton na sana ang lebel kang moisture sa daga. Tubigan tulos ang mga tanom tanganing dai magadan. ");
        } else if (moisturePercentage < 40) {
    Serial.println("Diit na sana ang lebel kang moisture sa daga. Tubigan ang mga tanom.");
        } else if (moisturePercentage < 60) {
    Serial.println("Ugwa pang sapat na lebel kang moisture sa daga para buhayon ang mga tanom.");
        } else if (moisturePercentage < 80) {
    Serial.println("Dakol pa ang lebel kang moisture sa daga pambuhay sa mga tanom.");
        } else {
    Serial.println("Sobrahon ang lebel kang moisture sa daga. Pwede ining makaraot sa tanom buda sa daga.");
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
    Serial.println("Diiton na sana ang lebel kang tubig. Pakilaagan tulos tanganing mapalitan. ");
        } else if (distance < 10) {
    Serial.println("Diit na sana ang tubig sa laagan. Mag-ipos na sa pagsalida kang tubig.");
        } else if (distance < 12) {
    Serial.println("Ugwa pang supply kang tubig. Pwede pang gamiton.");
        } else if (distance < 14) {
    Serial.println("Dakol pa ang supply ki tubig, kasyahon pang panggamit kung nanganga-ipo.");
        } else {
    Serial.println("Dakulon ang lebel kang tubig sa lagaan. Bawasan tulos ang tubig.");
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
