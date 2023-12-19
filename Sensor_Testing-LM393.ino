const int soilMoisturePin = A0;
int soilMoistureValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  soilMoistureValue = analogRead(soilMoisturePin);
  int moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  Serial.print("The soil moisture of your soil is ");
  Serial.print(moisturePercentage);
  Serial.println("%.");

  if (moisturePercentage < 20) {
    Serial.println("The water level in the container is too low, please refill the water supply immediately.");
  } else if (moisturePercentage < 40) {
    Serial.println("The water level in the container is low, prepare to refill the water supply.");
  } else if (moisturePercentage < 60) {
    Serial.println("The water level in the container is at a moderate level, you still have enough water for intended use.");
  } else if (moisturePercentage < 80) {
    Serial.println("The water level in the container is high, you have enough water for your needs.");
  } else {
    Serial.println("The water level in the container is excessively high, please drain the water supply immediately.");
  }

  delay(2000);
}
