/*
 *
 * LCD:
 *   - 16x2
 *   - LiquidCrystal Library
 *   - circuit:
 *     - LCD RS pin to digital pin 12
 *     - LCD Enable pin to digital pin 11
 *     - LCD D4 pin to digital pin 5
 *     - LCD D5 pin to digital pin 4
 *     - LCD D6 pin to digital pin 3
 *     - LCD D7 pin to digital pin 2
 *     - LCD R/W pin to ground
 *     - 10K resistor:
 *     - ends to +5V and ground
 *     - wiper to LCD VO pin (pin 3)
 *   - See Also: http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status
int ln = 0;

void setup() {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {    
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
    disp("");
    disp("");
    lcd.setCursor(0,0);
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
  if (Serial.available()) {
    String s = Serial.readStringUntil('\n');
    disp(s);
  }
}

void disp(String s) {
    s = fit16(s);

    ln = 1 - ln;
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, ln);
  
    lcd.print(s);
    Serial.println("lcd:");
    Serial.println(s);
}

String fit16(String s) {
  int len = s.length();
  if (len > 16) {
    s = s.substring(0, 13);
    s.concat("...");
  } else {
    s.concat("                ");
    s.substring(0, 16);
  }
  return s;
}

