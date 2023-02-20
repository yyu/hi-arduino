#define ledPin 3
#define btnPin 7

int speedOptions[] = {1000, 800, 700, 500};
int speedOptionNumber = 4;
int speedOptionIndex = 0;

unsigned long timer = 0;
unsigned long ledTimer = 0;

bool btnWasOn = false;
unsigned long btnReleaseTime;    // last time button is seen released
unsigned long btnTurnedOnTime;   // timestamp for state change OFF->ON (debounced)
unsigned long btnTurnedOffTime;  // timestamp for state change ON->OFF
unsigned long speedChangeTime;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  speedOptionNumber = sizeof(speedOptions) / sizeof(speedOptions[0]);
}

void blink() {
  digitalWrite(ledPin, !digitalRead(ledPin));
}

bool btnTriggered(unsigned long timer) {
  return timer - btnTurnedOnTime < 500;
}

bool tooFast(unsigned long timer) {
  return timer < speedChangeTime + 1000;
}

bool btnHolding() {
  return timer - btnReleaseTime > 500;
}

void changeSpeed() {
  speedOptionIndex = (speedOptionIndex + 1) % speedOptionNumber;
}

void debugPrint(char* s) {
    Serial.print(s);
    Serial.print(" ");
    Serial.print("speed:"); Serial.print(speedOptions[speedOptionIndex]);
    Serial.print(", timer:"); Serial.print(timer);
    Serial.print(", btnReleaseTime:"); Serial.print(btnReleaseTime);
    Serial.print(", btnTurnedOffTime:"); Serial.print(btnTurnedOffTime);
    Serial.print(", btnTurnedOnTime:"); Serial.print(btnTurnedOnTime);
    Serial.print(", btnTriggered:"); Serial.print(btnTriggered(timer));
    Serial.print(", tooFast:"); Serial.print(tooFast(timer));
    Serial.print(", btnHolding:"); Serial.print(btnHolding());
    Serial.print(", speedChangeTime:"); Serial.print(speedChangeTime);
    Serial.println(".");
}

// the loop function runs over and over again forever
void loop() {
  timer = millis();

  bool btnPressed = !digitalRead(btnPin);
  if (btnPressed) {
    if (!btnWasOn) {
      if (timer - btnTurnedOffTime > 100) {
        btnTurnedOnTime = timer;
      }
    }
    btnWasOn = true;
  } else {
    if (btnWasOn) {
      btnTurnedOffTime = timer;
    }
    btnWasOn = false;
    btnReleaseTime = timer;
  }

  if (btnTriggered(timer) && !tooFast(timer) && !btnHolding()) {
    debugPrint("*");
    changeSpeed();
    speedChangeTime = timer;
    Serial.println(speedOptionIndex);
  }

  if (timer > ledTimer) {
    ledTimer += speedOptions[speedOptionIndex];
    debugPrint(" ");
    blink();
  }
}
