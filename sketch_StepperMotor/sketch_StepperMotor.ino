/*
 * Stepper Motor Demo
 *
 * 28BYJ-48 Unipolar Stepper + ULN2003 Driver
 *
 * https://youtu.be/0qwrnUeSpYQ
 */

#include <Stepper.h>

const float STEPS_PER_REVOLUTION = 32;
const float GEAR_REDUCTION = 64;
const float STEPS_PER_OUT_REVOLUTION = STEPS_PER_REVOLUTION * GEAR_REDUCTION;

// Arduino pins  --(connect to)--  ULN2003 Motor Driver pins
//            8  ----------------  In1
//            9  ----------------  In2
//           10  ----------------  In3
//           11  ----------------  In4
// Pins entered in sequence 1-3-2-4 for proper step sequencing
Stepper stepper(STEPS_PER_REVOLUTION, 8, 10, 9, 11);

int StepsRequired;

void setup() {}

void loop() {
    stepper.setSpeed(1);
    StepsRequired = 4;
    stepper.step(StepsRequired);
    delay(2000);

    // Rotate CW 1/2 turn slowly
    StepsRequired = STEPS_PER_OUT_REVOLUTION / 2;
    stepper.setSpeed(100);
    stepper.step(StepsRequired);
    delay(1000);

    // Rotate CW 1/2 turn quickly
    StepsRequired = -STEPS_PER_OUT_REVOLUTION / 2;
    stepper.setSpeed(700);
    stepper.step(StepsRequired);
    delay(1000);
}

