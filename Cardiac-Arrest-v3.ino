int ledLeftStart = 0;
int ledRightStart = 1;
int numLeds = 14;

void setup() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  runPattern(1);
  runPattern(2); 
  runPattern(3); 
  runPattern(4); 
  runPattern(5); 
}

void runPattern(int pattern) {
  switch (pattern) {
    case 1: steadyOn(); break;
    case 2: blinking(); break;
    case 3: twinkling(); break;
    case 4: fading(); break;
    case 5: chasing(); break;

    default: break;
  }
}

void steadyOn() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, HIGH);
  }
  delay(200); // Original delay time
  turnOffLeds();
  delay(200); // Original delay time
}

void blinking() {
  for (int j = 0; j < 2; j++) {
    toggleLeds();
    delay(40); // Original delay time
  }
}

void twinkling() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, HIGH);
    delay(random(5, 20)); // Faster delay time
    digitalWrite(i, LOW);
  }
  delay(200); // Original delay time
}

void fading() {
  fadeLights(255, 10);
  fadeLights(0, 10);
}

void chasing() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(40, 100);
  }
}

void toggleLeds() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, !digitalRead(i));
  }
}

void turnOffLeds() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, LOW);
  }
}

void fadeLights(int endBrightness, int delayTime) {
  for (int brightness = 0; brightness <= endBrightness; brightness++) {
    setAllLedsBrightness(brightness);
    delay(delayTime);
  }
  for (int brightness = endBrightness; brightness >= 0; brightness--) {
    setAllLedsBrightness(brightness);
    delay(delayTime);
  }
}

void sequentialBlink(int blinkDelay, int patternDelay) {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, HIGH);
    delay(blinkDelay);
    digitalWrite(i, LOW);
  }
  delay(patternDelay);
}

void setAllLedsBrightness(int brightness) {
  for (int i = ledLeftStart; i < numLeds; i++) {
    analogWrite(i, brightness);
  }
}
