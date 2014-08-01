/*
    Function           Channel A     Channel B
    ---------------    ----------    ----------
    Direction          Digital 12    Digital 13
    Speed (PWM)        Digital  3    Digital 11
    Brake              Digital  9    Digital  8
    Current Sensing    Analog   0    Analog   1
*/

const int dir_A_pin   = 12;
const int dir_B_pin   = 13;
const int speed_A_pin =  3;
const int speed_B_pin = 11;
const int brake_A_pin =  9;
const int brake_B_pin =  8;


void setup() {
  //Setup Channel A
  pinMode(dir_A_pin,   OUTPUT); //Initiates Motor Channel A pin
  pinMode(brake_A_pin, OUTPUT); //Initiates Brake Channel A pin
  pinMode(dir_B_pin,   OUTPUT); //Initiates Motor Channel B pin
  pinMode(brake_B_pin, OUTPUT); //Initiates Brake Channel B pin
}

void loop(){
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

