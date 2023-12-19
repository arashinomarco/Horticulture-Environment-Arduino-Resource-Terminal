#include <Keypad.h>

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

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}
