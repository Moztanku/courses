#include <Arduino.h>

#include "Wheels.h"

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() 
{ }

Wheels::~Wheels()
{
  delete dashboard;
}

void Wheels::attachRight(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::initDashboard(uint8_t address, uint8_t columns, uint8_t rows)
{
    if (dashboard)
        delete dashboard;

    dashboard = new LiquidCrystal_I2C(
        address,
        columns,
        rows
    );
}

void Wheels::setSpeedRight(uint8_t s)
{
    analogWrite(this->pinsRight[2], s);
}

void Wheels::setSpeedLeft(uint8_t s)
{
    analogWrite(this->pinsLeft[2], s);
}

void Wheels::setSpeed(uint8_t s)
{
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
{
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::forwardLeft() 
{
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
}

void Wheels::forwardRight() 
{
    SET_MOVEMENT(pinsRight, HIGH, LOW);
}

void Wheels::backLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
}

void Wheels::backRight()
{
    SET_MOVEMENT(pinsRight, LOW, HIGH);
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, LOW);
}

void Wheels::stopRight()
{
    SET_MOVEMENT(pinsRight, LOW, LOW);
}

void Wheels::stop()
{
    this->stopLeft();
    this->stopRight();
}

void Wheels::updateDashboard(int distance_left)
{
    constexpr auto get_direction = [](int In1, int In2) -> char {
      return
        In1 == HIGH && In2 == LOW ?  'F' :  // Forward
        In1 == LOW && In2 == HIGH ?  'B' :  // Backward
        'S';                                // Stopped
    };

    dashboard->clear();
    dashboard->setCursor(0,0);
    dashboard->print(String(distance_left));

    dashboard->setCursor(0, 1);
    dashboard->print(
      get_direction(pinsLeft[0], pinsLeft[1])
    );

    dashboard->setCursor(15,1);
    dashboard->print(
      get_direction(pinsRight[0], pinsRight[1])
    );
}

