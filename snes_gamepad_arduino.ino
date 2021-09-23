#include <Joystick.h>

// PINS
int DATA_CLOCK = 5;
int DATA_LATCH = 6;
int DATA_SERIAL = 7;

/** Data store for current state of buttons **/
int buttons[12];

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  /** Set DATA_CLOCK normally HIGH **/
  pinMode (DATA_CLOCK, OUTPUT);
  digitalWrite (DATA_CLOCK, HIGH);
  
  /** Set DATA_LATCH normally LOW **/
  pinMode (DATA_LATCH, OUTPUT);
  digitalWrite (DATA_LATCH, LOW);

  /** Set DATA_SERIAL normally HIGH **/
  pinMode (DATA_SERIAL, OUTPUT);
  digitalWrite (DATA_SERIAL, HIGH);
  pinMode (DATA_SERIAL, INPUT);  

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  Joystick.setYAxis(0);
  Joystick.setXAxis(0);
  Joystick.setButton(0, 0);
  Joystick.setButton(1, 0);
  Joystick.setButton(2, 0);
  Joystick.setButton(3, 0);
  Joystick.setButton(4, 0);
  Joystick.setButton(5, 0);
  Joystick.setButton(6, 0);
  Joystick.setButton(7, 0);
}

// Last state of the buttons
int lastButtonState[5] = {0,0,0,0,0};

void loop() {
  /** Latch for 12us **/
  digitalWrite(DATA_LATCH, HIGH);
//  delayMicroseconds(12);
  digitalWrite(DATA_LATCH, LOW);
//  delayMicroseconds(6);

  /** Read data bit by bit from SR **/
  for (int i = 0; i < 16; i++) {
    digitalWrite (DATA_CLOCK, LOW);
//    delayMicroseconds (6);
    if (i <= 11) {
      buttons[i] = digitalRead (DATA_SERIAL);
    }
    digitalWrite (DATA_CLOCK, HIGH);
//    delayMicroseconds (6);
  }

  /** Set Joystick buttons based on SNES input **/
  
  // UP or DOWN
  if (buttons[4] == 0){
    Joystick.setYAxis(-1);
  } else if (buttons[5] == 0){
    Joystick.setYAxis(1);
  } else {
    Joystick.setYAxis(0);
  }

  // RIGHT or LEFT
  if (buttons[7] == 0){
    Joystick.setXAxis(1);
  } else if (buttons[6] == 0){
    Joystick.setXAxis(-1);
  } else {
    Joystick.setXAxis(0);
  }

  // FIRE1=A
  Joystick.setButton(0,!buttons[8]);
  // FIRE2=B
  Joystick.setButton(1,!buttons[0]);
  // FIRE3=X
  Joystick.setButton(2,!buttons[9]);
  // FIRE4=Y
  Joystick.setButton(3,!buttons[1]);
  // FIRE5=L
  Joystick.setButton(4,!buttons[10]);
  // FIRE6=R
  Joystick.setButton(5,!buttons[11]);
  // FIRE7=SELECT
  Joystick.setButton(6,!buttons[2]);
  // FIRE8=START
  Joystick.setButton(7,!buttons[3]);

  delay(10);
}
