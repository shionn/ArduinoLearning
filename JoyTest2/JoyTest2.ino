
#include <Arduino.h>
#include <Joystick.h>

Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 14, 0, true, true, true, true, true, true, false, false, false, false, false);

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);

  joystick.begin(false);
  joystick.setXAxisRange(-1, 1);
  joystick.setYAxisRange(-1, 1);
}

void loop() {
  digitalWrite(2, LOW);
  joystick.setXAxis((digitalRead(7)?0:1) - (digitalRead(9)?0:1));
  joystick.setYAxis((digitalRead(6)?0:1) - (digitalRead(8)?0:1));
  digitalWrite(2, HIGH);
  for (int c=0;c<3;c++) {
    digitalWrite(3+c, LOW);
    for (int r=0;r<4; r++) {
      joystick.setButton(c*4+r, !digitalRead(6+r));
    }
    digitalWrite(3+c, HIGH);
  }

  joystick.setButton(12, !digitalRead(14));
  joystick.setButton(13, !digitalRead(15));

  joystick.setRxAxis(analogRead(A0));
  joystick.setZAxis(analogRead(A1));
  joystick.setRzAxis(analogRead(A2));
  joystick.setRyAxis(analogRead(A3));
  joystick.sendState();
}
