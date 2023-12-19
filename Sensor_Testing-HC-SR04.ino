const int trigPin = 7;
const int echoPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.034 / 2;

  Serial.print("The water level of your container is ");
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

  delay(2000);
}
