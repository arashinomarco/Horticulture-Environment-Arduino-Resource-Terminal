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
    Serial.println("Ang temperatura ng kapaligiran ay masyadong malamig para sa iyong halaman, mapanganib ito sa halaman at maaaring maging hadlang ito sa paglago.");
         } else if (temperature < 20) {
    Serial.println("Ang temperatura ng kapaligiran ay malamig, na maaaring mainam para sa ilang mga halaman.");
         } else if (temperature < 25) {
    Serial.println("Ang temperatura ng kapaligiran ay katamtaman, magbibigay ito ng komportableng kondisyon para sa iyong halaman.");
         } else if (temperature < 30) {
    Serial.println("Ang temperatura ng kapaligiran ay mainit init, ito ay angkop para sa paglago ng iyong halaman.");
         } else {
    Serial.println("Ang temperatura ng kapaligiran ay masyadong mainit, maaaring makapinsala ito sa iyong halaman dahil sa labis na init.");
         }

        break;

      case 2:

        Serial.print("Reading Humidity: ");
        Serial.print(humidity);
        Serial.println("%.");

        if (humidity < 30) {
    Serial.println("Ang kahalumigmigan ng kapaligiran ay masyadong mababa, maaaring hindi ito makakapagbigay ng sapat na kahalumigmigan para sa kalusugan ng iyong halaman.");
        } else if (humidity < 40) {
    Serial.println("Ang kahalumigmigan ng kapaligiran ay mababa, na maaaring hindi magbigay ng sapat na kahalumigmigan para sa kalusugan ng iyong halaman.");
        } else if (humidity < 60) {
    Serial.println("Ang kahalumigmigan ng kapaligiran ay katamtaman, na lumilikha ng isang mainam na kapaligiran para sa iyong halaman upang umunlad.");
        } else if (humidity < 80) {
    Serial.println("Ang kahalumigmigan ng kapaligiran ay medyo mataas, na maaaring maging kanais nais para sa paglago ng iyong halaman.");
        } else {
    Serial.println("Ang kahalumigmigan ng kapaligiran ay masyadong mataas, maaaring humantong ito sa labis na kahalumigmigan at nakakaapekto sa paglago ng iyong halaman.");
        }


        break;
        
      case 3:

        soilMoistureValue = analogRead(soilMoisturePin);
        moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
        Serial.print("Reading Soil Moisture: ");
        Serial.print(moisturePercentage);
        Serial.println("%.");

        if (moisturePercentage < 20) {
    Serial.println("Ang antas ng kahalumigmigan ng lupa ay masyadong mababa, agad na diligan ang halaman.");
        } else if (moisturePercentage < 40) {
    Serial.println("Ang antas ng kahalumigmigan ng lupa ay mababa, diligan ang halaman upang suportahan ang paglago ng halaman.");
        } else if (moisturePercentage < 60) {
    Serial.println("Ang antas ng kahalumigmigan ng lupa ay katamtaman, na nagbibigay ng angkop na mga kondisyon para sa kalusugan ng halaman.");
        } else if (moisturePercentage < 80) {
    Serial.println("Ang antas ng kahalumigmigan ng lupa ay mataas, na lumilikha ng isang kanais-nais na kapaligiran para sa mga halaman upang umunlad.");
        } else {
    Serial.println("Ang antas ng kahalumigmigan ng lupa ay labis na mataas, na posibleng humahantong sa matubig na lupa at stress ng halaman.");
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
    Serial.println("Ang antas ng tubig sa lalagyan ay masyadong mababa, pakipuno agad ang suplay ng tubig.");
        } else if (distance < 10) {
    Serial.println("Ang antas ng tubig sa lalagyan ay mababa, maghanda upang muling punan ang suplay ng tubig.");
        } else if (distance < 12) {
    Serial.println("Ang antas ng tubig sa lalagyan ay nasa katamtamang antas, mayroon ka pa ring sapat na tubig para sa layuning gamitin.");
        } else if (distance < 14) {
    Serial.println("Ang antas ng tubig sa lalagyan ay mataas, mayroon kang sapat na tubig para sa iyong mga pangangailangan.");
        } else {
    Serial.println("Ang antas ng tubig sa lalagyan ay labis na mataas, mangyaring palabasin kaagad ang suplay ng tubig.");
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
