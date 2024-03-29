#define ledPin 3  // D3 -- LED -- resister -- GND
#define btnPin 7  // D7 -- BUTTON -- GND (use builtin pullup)

int speedOptions[] = {1000, 500, 250, 100};
int speedOptionNumber = 4;
int speedOptionIndex = 0;

unsigned long timer = 0;
unsigned long ledTimer = 0;

bool btnWasOn = false;
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

void changeSpeed() {
  speedOptionIndex = (speedOptionIndex + 1) % speedOptionNumber;
}

void debugPrint(char* s) {
    Serial.print(s);
    Serial.print(" ");
    Serial.print("speed:"); Serial.print(speedOptions[speedOptionIndex]);
    Serial.print(", timer:"); Serial.print(timer);
    Serial.print(", btnTurnedOffTime:"); Serial.print(btnTurnedOffTime);
    Serial.print(", btnTurnedOnTime:"); Serial.print(btnTurnedOnTime);
    Serial.print(", btnTriggered:"); Serial.print(btnTriggered(timer));
    Serial.print(", tooFast:"); Serial.print(tooFast(timer));
    Serial.print(", speedChangeTime:"); Serial.print(speedChangeTime);
    Serial.println(".");
}

// the loop function runs over and over again forever
void loop() {
  timer = millis();

  bool btnPressed = !digitalRead(btnPin);
  if (btnPressed) {
    if (!btnWasOn) {
      // the debounce logic will ignore:
      //                              |<-----100----->|
      //      on  -----------------------+ +------------------- on
      //                                 | |
      //      off                        +-+                    off
      //
      //      on  -----------------------+ +-+ +-+ +----------- on
      //                                 | | | | | |
      //      off                        +-+ +-+ +-+            off
      //
      //      on  -----------------------+ +-+ +-+              off
      //                                 | | | | |
      //      off                        +-+ +-+ +------------- on
      //
      //      on  -----------------------+ +-+ +-+              on
      //                                 | | | | |
      //      off                        +-+ +-+ +------------- off
      //
      // will trigger only once, even if it bounces:
      //      on                         +-+                    on
      //                                 | |
      //      off -----------------------+ +------------------- off
      //
      //      on                         +-+ +-+ +-+            on
      //                                 | | | | | |
      //      off -----------------------+ +-+ +-+ +----------- off
      //
      //      on                         +--------------------- on
      //                                 |
      //      off -----------------------+                      off
      //
      //      on                         +-+ +-+ +------------- on
      //                                 | | | | |
      //      off -----------------------+ +-+ +-+              off
      if (timer - btnTurnedOffTime > 100) {  // debounce
        btnTurnedOnTime = timer;
      }
    }
    btnWasOn = true;
  } else {
    if (btnWasOn) {
      btnTurnedOffTime = timer;  // always recognize ON->OFF events
    }
    btnWasOn = false;
  }

  if (btnTriggered(timer) && !tooFast(timer)) {
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
