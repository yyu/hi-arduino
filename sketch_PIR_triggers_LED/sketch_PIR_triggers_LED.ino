const int pirPin = A0;
const int ledPin = 2;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pirPin)) {
    digitalWrite(ledPin, HIGH);
    Serial.print("PIR_HIGH");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.print("pir_low");
  }

  delay(100);
}

