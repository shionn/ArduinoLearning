

#include <Joystick.h>

Joystick_ joystick;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  joystick.begin(false);
}

void loop() {
  for (int c=0;c<4;c++) {
    digitalWrite(2+c, HIGH);
    for (int r=0;r<4; r++) {
      joystick.setButton(c+r*4,digitalRead(6+r));
    }
    digitalWrite(2+c, LOW);
  }
  joystick.sendState();
}
