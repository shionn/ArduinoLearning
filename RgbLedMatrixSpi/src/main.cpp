#include <SPI.h>                  //  include the head file to enable the  library.

static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};         // defined a data matrix
static uint8_t i = 1;                                                    // defined a variable vector
const int CE = 10;                                                      // defined  the CE function pin

void heartbig()                                                  // defined a function called "heart big".
{
  int j;
  int x = 2;
  static uint8_t heart[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};    // you need to calculate which led should be light up by this array, it defined line by line on your matrix, for example , 0x00 means the led of the first line is off,  and the 0x66 means the second line's first led will go off and the fourth led will go off and fifth led will go off and eight led will go off. others will turn on....and so on.

  for ( j = 0; j < 8; j++)
  {
    data[0] = ~heart[j];       // color red
    data[2] = 0xFF;             // color green
    data[1] = 0xFF;             // color blue
    data[3] = 0x01 << j ;    // display the data on matrix.
    digitalWrite(CE, LOW);     // when CE is low, it begin to receive data.
    SPI.transfer(data[0]);         //transfer data[0] to the matrix(red)
    SPI.transfer(data[2]);         //transfer data[2] to the matrix(green)
    SPI.transfer(data[1]);        // transfer   data[1] to the matrix(blue)
    SPI.transfer(data[3]);      // tansfer data[3] to the matrix( scanning and display the data on matrix)
    digitalWrite(CE, HIGH);    // when CE is High, means that matrix begin to display the array's information to the matrix.
    delay(x);                          // a little bit delay, let the led light up and stay for a while so that it looks like it brightness.
  }
};

void heartsmall()
{
  int j;
  int x = 2;
  static uint8_t heart[8] = {0x00, 0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00};          // change the hard to be the smaller one, all you need to do is change this parameter.
  for ( j = 0; j < 8; j++)
  {
    data[0] = ~heart[j];
    data[2] = 0xFF;
    data[1] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(CE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(CE, HIGH);
    delay(x);
  }
};

void matrixoff()
{
  int j;
  int x = 2;
  static uint8_t heart[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};        // you can see, all of the led will go off here.
  for ( j = 0; j < 8; j++)
  {
    data[0] = ~heart[j];
    data[2] = 0xFF;
    data[1] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(CE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(CE, HIGH);
    delay(x);
  }
};

void setup() {
  pinMode(CE, OUTPUT);                          //initialized the pin's mode.
  SPI.begin();                                              // start spi function
}

void loop()                                                  //defined a loop function
{
  int m = 10;
  for ( m = 10; m > 0; m--) {                     // make a for loop to let the data displayed on the matrix.
    heartbig();
  };
  matrixoff();                                          // turn off the matrix
  delay(100);                                         // delay 100 ms
  for ( m = 10; m > 0; m--) {                 // let the data displayed on the matrix
    heartsmall();
  };
  matrixoff();
  delay(100);
}
