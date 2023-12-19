#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(5000);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("The temperature is ");
  Serial.print(temperature);
  Serial.println("°C.");

  Serial.print("The humidity is ");
  Serial.print(humidity);
  Serial.println("%.");

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
}
