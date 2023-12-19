const int ledLeftStart = 0;
const int ledRightStart = 1;
const int numLeds = 14;

void setup() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int pattern = 1; pattern <= 20; pattern++) {
    runPattern(pattern);
    delay(5000);
  }
}

void runPattern(int pattern) {
  switch (pattern) {
    case 1: steadyOn(); break;
    case 2: blinking(); break;
    case 3: twinkling(); break;
    case 4: fading(); break;
    case 5: chasing(); break;
    case 6: colorChanging(); break;
    case 7: sequentialFlashing(); break;
    case 8: alternatingFade(); break;
    case 9: cascading(); break;
    case 10: randomFlashing(); break;
    case 11: crossfade(); break;
    case 12: meteorShower(); break;
    case 13: sparkle(); break;
    case 14: fireworkBurst(); break;
    case 15: pulse(); break;
    case 16: dripDrop(); break;
    case 17: wave(); break;
    case 18: spiral(); break;
    case 19: flashAndFade(); break;
    case 20: doubleHelix(); break;
    default: break;
  }
}

void steadyOn() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, HIGH);
  }
  delay(2000);
  turnOffLeds();
  delay(2000);
}

void blinking() {
  for (int j = 0; j < 2; j++) {
    toggleLeds();
    delay(200);
  }
}

void twinkling() {
  for (int i = ledLeftStart; i < numLeds; i++) {
    digitalWrite(i, HIGH);
    delay(random(50, 200));
    digitalWrite(i, LOW);
  }
  delay(2000);
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

void colorChanging() {
  for (int color = 0; color < 255; color++) {
    setAllLedsColor(color);
    delay(20);
  }
}

void sequentialFlashing() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(40, 100);
  }
}

void alternatingFade() {
  for (int j = 0; j < 4; j++) {
    alternateFade(500);
  }
}

void cascading() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(40, 100);
  }
}

void randomFlashing() {
  for (int j = 0; j < 4; j++) {
    randomBlink(40, 100);
  }
}

void crossfade() {
  fadeLights(255, 20);
  fadeLights(0, 20);
}

void meteorShower() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(20, 100);
  }
}

void sparkle() {
  for (int j = 0; j < 4; j++) {
    randomBlink(100, 100);
    randomBlink(100, 100);
  }
}

void fireworkBurst() {
  for (int j = 0; j < 4; j++) {
    setAllLedsColor(255);
    delay(100);
    turnOffLeds();
    delay(100);
  }
}

void pulse() {
  for (int j = 0; j < 4; j++) {
    pulseEffect(10);
  }
}

void dripDrop() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(50, 50);
    delay(200);
  }
}

void wave() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(40, 100);
  }
}

void spiral() {
  for (int j = 0; j < 4; j++) {
    spiralEffect(40);
  }
}

void flashAndFade() {
  for (int j = 0; j < 4; j++) {
    sequentialBlink(40, 100);
    fadeLights(255, 20);
  }
}

void doubleHelix() {
  for (int j = 0; j < 4; j++) {
    spiralEffect(40);
    reverseSpiralEffect(40);
  }
}

// Helper functions

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

void alternateFade(int fadeDelay) {
  for (int i = ledLeftStart; i < numLeds; i += 2) {
    analogWrite(i, 255);
    analogWrite(i + 1, 0);
  }
  delay(fadeDelay);
  for (int i = ledLeftStart; i < numLeds; i += 2) {
    analogWrite(i, 0);
    analogWrite(i + 1, 255);
  }
  delay(fadeDelay);
}

void setAllLedsColor(int color) {
  for (int i = ledLeftStart; i < numLeds; i++) {
    analogWrite(i, color);
  }
}

void setAllLedsBrightness(int brightness) {
  for (int i = ledLeftStart; i < numLeds; i++) {
    analogWrite(i, brightness);
  }
}

void randomBlink(int blinkDelay, int patternDelay) {
  int randomLed = random(ledLeftStart, numLeds);
  digitalWrite(randomLed, HIGH);
  delay(blinkDelay);
  digitalWrite(randomLed, LOW);
  delay(patternDelay);
}

void pulseEffect(int delayTime) {
  for (int intensity = 0; intensity <= 255; intensity++) {
    setAllLedsBrightness(intensity);
    delay(delayTime);
  }
  for (int intensity = 255; intensity >= 0; intensity--) {
    setAllLedsBrightness(intensity);
    delay(delayTime);
  }
}

void spiralEffect(int delayTime) {
  for (int r = 0; r < numLeds / 2; r++) {
    for (int i = 0; i < numLeds; i++) {
      if (i >= r && i < numLeds - r) {
        digitalWrite(i, HIGH);
      }
    }
    delay(delayTime);
    turnOffLeds();
  }
}

void reverseSpiralEffect(int delayTime) {
  for (int r = numLeds / 2; r >= 0; r--) {
    for (int i = 0; i < numLeds; i++) {
      if (i >= r && i < numLeds - r) {
        digitalWrite(i, HIGH);
      }
    }
    delay(delayTime);
    turnOffLeds();
  }
}
