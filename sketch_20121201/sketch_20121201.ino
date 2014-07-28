const int ledPin = 13;
const int sensorPin = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int rate = analogRead(sensorPin);
  Serial.println(rate);
  digitalWrite(ledPin, HIGH);
  delay(rate);
  digitalWrite(ledPin, LOW);
  delay(rate);
}
