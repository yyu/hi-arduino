
int trigPin = 4;    // Trigger
int echoPin = 3;    // Echo
long duration, cm, inches;
int motorSpeed = 100;  // simulation

void setup() {
  //Serial Port begin
  Serial.begin (115200);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

  if (27 < cm && cm < 33) {
    motorSpeed = 0;
  } else if (cm < 30) {
    motorSpeed = cm - 30;
  } else {
    motorSpeed = (cm > 130) ? 100 : (cm - 30);
  }

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm. ");
  Serial.print("motorSpeed:");
  Serial.print(motorSpeed);
  Serial.println();
  
  delay(250);
}
