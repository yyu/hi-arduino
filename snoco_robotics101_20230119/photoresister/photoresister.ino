// A3 -- photoresister -- GND

void setup() {
  // put your setup code here, to run once:
  pinMode(17, INPUT_PULLUP);  // Arduino Nano: A3 is D17 - See https://content.arduino.cc/assets/Pinout-NANO_latest.pdf
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(3);  // read A3
  Serial.println(light);
  delay(50);
}
