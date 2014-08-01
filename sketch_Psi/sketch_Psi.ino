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

/*
 * Motors
 */
const int A = 0;
const int B = 1;
const int BOTH = 2;

const int FORWARD  = 0;
const int BACKWARD = 1;
const int LEFT     = 2;
const int RIGHT    = 3;

const int dir_pin[]   = {12, 13};
const int speed_pin[] = { 3, 11};
const int brake_pin[] = { 9,  8};

/*
 * Sonar
 */
const int trig_pin = 5;
const int echo_pin = 4;

/*
 * LEDs
 */
const int led[] = {7, 6};

void setup() {
  InitMotorPins();
  InitSonarPins();
}

void loop(){
  // TestMotors();
  //TestMotors1();
  //TestMotors2();
  // TestSonar();
  TestSonarAndMotor();
}

//////////////////////////////////////////////////

void TestSonarAndMotor() {
  while (GetDistance() < 50) {  // This is where the led[0] On/Off happens
    digitalWrite(led[0],HIGH); // When the Red condition is met, the Green led[0] should turn off
    digitalWrite(led[1],LOW);
    
    delay(1000);
    psi_back(255, 200);
    delay(1000);
    psi_turn(LEFT, 255);
    delay(1000);
  }

  if (GetDistance() >= 50) {
    digitalWrite(led[0],LOW);
    digitalWrite(led[1],HIGH);
    psi_go(255, 500);
  }
}

//////////////////////////////////////////////////

void InitMotorPins() {
  pinMode(dir_pin[0],   OUTPUT);
  pinMode(brake_pin[0], OUTPUT);
  pinMode(dir_pin[1],   OUTPUT);
  pinMode(brake_pin[1], OUTPUT);
}

void motor_on(int motor, int dir, int spd) {
  if (motor == BOTH) {
    motor_on(A, dir, spd);
    motor_on(B, dir, spd);
  } else {
    if (dir == FORWARD) {
      digitalWrite(dir_pin[motor], HIGH);
    } else if (dir == BACKWARD) {
      digitalWrite(dir_pin[motor], LOW);
    }
    digitalWrite(brake_pin[motor], LOW); // Disengage the Brake
    analogWrite(speed_pin[motor],  spd); // Spin the motor
  }
}

void motor_off(int motor) {
  if (motor == BOTH) {
    motor_off(A);
    motor_off(B);
  } else {
    digitalWrite(brake_pin[motor], HIGH); //Engage the Brake
  }
}

void motor_run(int motor, int dir, int spd, int t) {
  motor_on(motor, dir, spd);
  delay(t);
  motor_off(motor);
}

void psi_go(int spd, int t) {
  motor_on(BOTH, FORWARD, spd);
  delay(t);
  motor_off(BOTH);
}

void psi_back(int spd, int t) {
  motor_on(BOTH, BACKWARD, spd);
  delay(t);
  motor_off(BOTH);
}

void psi_turn(int dir, int spd) {
  if (dir == LEFT) {
    motor_on(A, BACKWARD, spd);
    motor_on(B, FORWARD,  spd);
  } else if (dir == RIGHT) {
    motor_on(A, FORWARD,  spd);
    motor_on(B, BACKWARD, spd);
  }
  delay(200);
  motor_off(BOTH);
}

void TestMotors1() {
  psi_go(255, 3000);
  delay(1000);
  psi_back(123, 3000);
  delay(1000);
}

void TestMotors2() {
  psi_turn(LEFT, 255);
  delay(1000);
  psi_turn(RIGHT, 255);
  delay(1000);
}

void TestMotors0() {
  //forward @ full speed
  digitalWrite(dir_pin[0],  HIGH); //Establishes forward direction of Channel A
  digitalWrite(brake_pin[0], LOW); //Disengage the Brake for Channel A
  analogWrite(speed_pin[0],  255); //Spins the motor on Channel A at full speed
  digitalWrite(dir_pin[1],  HIGH); //Establishes forward direction of Channel B
  digitalWrite(brake_pin[1], LOW); //Disengage the Brake for Channel B
  analogWrite(speed_pin[1],  255); //Spins the motor on Channel B at full speed
  
  delay(3000);
  
  digitalWrite(brake_pin[0], HIGH); //Eengage the Brake for Channel A
  digitalWrite(brake_pin[1], HIGH); //Eengage the Brake for Channel B

  delay(1000);
  
  //backward @ half speed
  digitalWrite(dir_pin[0],   LOW); //Establishes backward direction of Channel A
  digitalWrite(brake_pin[0], LOW);   //Disengage the Brake for Channel A
  analogWrite(speed_pin[0],  123);   //Spins the motor on Channel A at half speed
  digitalWrite(dir_pin[1],   LOW); //Establishes backward direction of Channel B
  digitalWrite(brake_pin[1], LOW);   //Disengage the Brake for Channel B
  analogWrite(speed_pin[1],  123);   //Spins the motor on Channel B at half speed
  
  delay(3000);
  
  digitalWrite(brake_pin[0], HIGH); //Eengage the Brake for Channel A
  digitalWrite(brake_pin[1], HIGH); //Eengage the Brake for Channel B
  
  delay(1000);
}

//////////////////////////////////////////////////

void InitSonarPins() {
  Serial.begin (9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
}

long GetDistance() {
  long duration, distance;
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

void TestSonar() {
  long distance = GetDistance();
  if (distance < 4) {  // This is where the led[0] On/Off happens
    digitalWrite(led[0],HIGH); // When the Red condition is met, the Green led[0] should turn off
    digitalWrite(led[1],LOW);
  } else {
    digitalWrite(led[0],LOW);
    digitalWrite(led[1],HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

