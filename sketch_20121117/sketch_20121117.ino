/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  int i;
  for (i = 0; i < 1000; i += 100) {
    int on_time = i;
    int off_time = 1000 - i;
    digitalWrite(led, HIGH);
    delay(on_time);
    digitalWrite(led, LOW);
    delay(off_time);
  }
}
