/*
Motor:
    Function           Channel A     Channel B
    ---------------    ----------    ----------
    Direction          Digital 12    Digital 13
    Speed (PWM)        Digital  3    Digital 11
    Brake              Digital  9    Digital  8
    Current Sensing    Analog   0    Analog   1
    
Sonar:
    HC-SR04 Ping distance sensor
    http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS
*/

const int dir_A_pin   = 12;
const int dir_B_pin   = 13;
const int speed_A_pin =  3;
const int speed_B_pin = 11;
const int brake_A_pin =  9;
const int brake_B_pin =  8;


const int trigPin = 5;
const int echoPin = 4;
const int led     = 7;
const int led2    = 6;

void setup() {
  InitMotorPins();
  InitSonarPins();
}

void loop(){
  // TestMotors();
  TestSonar();
}

/**************************************************/

void InitMotorPins() {
  pinMode(dir_A_pin,   OUTPUT); //Initiates Motor Channel A pin
  pinMode(brake_A_pin, OUTPUT); //Initiates Brake Channel A pin
  pinMode(dir_B_pin,   OUTPUT); //Initiates Motor Channel B pin
  pinMode(brake_B_pin, OUTPUT); //Initiates Brake Channel B pin
}

void TestMotors() {
  //forward @ full speed
  digitalWrite(dir_A_pin,  HIGH); //Establishes forward direction of Channel A
  digitalWrite(brake_A_pin, LOW); //Disengage the Brake for Channel A
  analogWrite(speed_A_pin,  255); //Spins the motor on Channel A at full speed
  digitalWrite(dir_B_pin,  HIGH); //Establishes forward direction of Channel B
  digitalWrite(brake_B_pin, LOW); //Disengage the Brake for Channel B
  analogWrite(speed_B_pin,  255); //Spins the motor on Channel B at full speed
  
  delay(3000);
  
  digitalWrite(brake_A_pin, HIGH); //Eengage the Brake for Channel A
  digitalWrite(brake_B_pin, HIGH); //Eengage the Brake for Channel B

  delay(1000);
  
  //backward @ half speed
  digitalWrite(dir_A_pin,   LOW); //Establishes backward direction of Channel A
  digitalWrite(brake_A_pin, LOW);   //Disengage the Brake for Channel A
  analogWrite(speed_A_pin,  123);   //Spins the motor on Channel A at half speed
  digitalWrite(dir_B_pin,   LOW); //Establishes backward direction of Channel B
  digitalWrite(brake_B_pin, LOW);   //Disengage the Brake for Channel B
  analogWrite(speed_B_pin,  123);   //Spins the motor on Channel B at half speed
  
  delay(3000);
  
  digitalWrite(brake_A_pin, HIGH); //Eengage the Brake for Channel A
  digitalWrite(brake_B_pin, HIGH); //Eengage the Brake for Channel B
  
  delay(1000);
}

/**************************************************/

void InitSonarPins() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void TestSonar() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
  } else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
