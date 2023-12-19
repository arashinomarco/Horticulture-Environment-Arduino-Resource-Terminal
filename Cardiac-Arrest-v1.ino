int ledLeftStart = 0;
int ledRightStart = 1;
int numLeds = 14;

void setup() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int k = 0; k < 4; k++) {
    for (int i = ledLeftStart; i < numLeds; i += 2) {
      digitalWrite(i, HIGH);
      digitalWrite(i + 1, HIGH);
      delay(40);
      digitalWrite(i, LOW);
      digitalWrite(i + 1, LOW);
    }
    for (int i = numLeds - 1; i >= ledLeftStart; i -= 2) {
      digitalWrite(i, HIGH);
      digitalWrite(i - 1, HIGH);
      delay(40);
      digitalWrite(i, LOW);
      digitalWrite(i - 1, LOW);
    }
    delay(100);
  }
  
  for (int k = 0; k < 4; k++) {
    for (int i = numLeds - 1; i >= ledLeftStart; i -= 2) {
      digitalWrite(i, HIGH);
      digitalWrite(i - 1, HIGH);
      delay(40);
      digitalWrite(i, LOW);
      digitalWrite(i - 1, LOW);
    }
    for (int i = ledLeftStart; i < numLeds; i += 2) {
      digitalWrite(i, HIGH);
      digitalWrite(i + 1, HIGH);
      delay(40);
      digitalWrite(i, LOW);
      digitalWrite(i + 1, LOW);
    }
    delay(100);
  }
  
  for (int j = 0; j < 2; j++) {
    for (int i = ledLeftStart; i < numLeds; i++) {
      digitalWrite(i, HIGH);
    }
    delay(200);
    for (int i = ledLeftStart; i < numLeds; i++) {
      digitalWrite(i, LOW);
    }
    delay(200);
  }
}
