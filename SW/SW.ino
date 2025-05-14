#include <Arduino.h>

#include <IRremote.hpp>

#include "Servo.h"
#include "Wheels.h"

Wheels wheels{};

void setup() {
  Serial.begin(9600);

  const int IN1 = 7; const int IN4 = 12;
  const int IN2 = 8; const int IN3 = 11;
  const int EnA = 5; const int EnB = 10;

  wheels.attach(
    IN1, IN2, EnA,
    IN4, IN3, EnB
  );

  wheels.initDashboard(0x27, 16, 2);
  wheels.setSpeed(100);
}

void loop() {
  while(Serial.available()) {
    const char input = Serial.read();

    switch(input) {
      case 'w':
        wheels.forward(); break;
      case 's':
        wheels.stop(); break;
      case 'x':
        wheels.back(); break;
      default:
        break;
    }

    wheels.updateDashboard();
  }
}