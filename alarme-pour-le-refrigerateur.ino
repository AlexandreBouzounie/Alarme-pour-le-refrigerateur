/*
 * bipforrefrigerator.ino
 * © Donkey Kong Informatique
 * This coding as been created and modified by DKI (@AlexandreBouzounie in GitHub https://github.com/AlexandreBouzounie).
 * This coding is in Arduino Web Editor and GitHub depot (https://github.com/AlexandreBouzounie/Alarme-pour-le-refrigerateur/blob/main/bipforrefrigerator.ino).
 * The general depot for Bip for refrigerator is in https://github.com/AlexandreBouzounie/Alarme-pour-le-refrigerateur .
 */

#include <Adafruit_LEDBackpack.h>
#include <Wire.h>

Adafruit_7segment led_display1 = Adafruit_7segment();

const int STMP = A3;
const int VCCBUZZER = 2;
const int VCCTMP = 12;

int c = 0;
int ac = 0;
int tmax = 5;
int tmin = 0;

void setup() {
  led_display1.begin(112);
  pinMode(VCCTMP, OUTPUT);
  pinMode(STMP, INPUT);
  pinMode(VCCBUZZER, OUTPUT);
  digitalWrite(VCCBUZZER, LOW);
  digitalWrite(VCCTMP, HIGH);
}

void loop() {
  maj();
  if (c >= tmax) {
    while (ac < c) {
      digitalWrite(VCCBUZZER, HIGH);
      delay(5);
      digitalWrite(VCCBUZZER, LOW);
      delay(495);
      digitalWrite(VCCBUZZER, HIGH);
      delay(5);
      digitalWrite(VCCBUZZER, LOW);
      delay(495);
    }
  
  }
  if (c <= tmin) {
    while (ac > c) {
      digitalWrite(VCCBUZZER, HIGH);
      delay(5);
      digitalWrite(VCCBUZZER, LOW);
      maj();
      delay(245);
      digitalWrite(VCCBUZZER, HIGH);
      delay(5);
      digitalWrite(VCCBUZZER, LOW);
      maj();
      delay(745);
    }
    
  }
  delay(500);
}

void maj() {
  ac = c;
  c = map(((analogRead(STMP) - 20) * 3.04), 0, 1023, -40, 125);
  led_display1.println(c);
  led_display1.writeDisplay();
}

// End of the file
