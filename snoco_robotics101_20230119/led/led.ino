#define ledPin 3
#define blinkSpeed 800

unsigned long timer = 0;
unsigned long ledTimer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void blink() {
  digitalWrite(ledPin, !digitalRead(ledPin));
}

void loop() {
  // put your main code here, to run repeatedly:
  timer = millis();
  if (timer > ledTimer) {
    ledTimer += blinkSpeed;
    blink();
  }
}
