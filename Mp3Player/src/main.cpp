#include <Arduino.h>
#include <SoftwareSerial.h>

// SUR un UNO, ne marche pas sur un nano
#define ARDUINO_RX 8//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 7//connect to RX of the module

// sur un D1
#define ARDUINO_RX D2 // to TX
#define ARDUINO_TX D1 // To RX

SoftwareSerial myMP3( ARDUINO_RX, ARDUINO_TX );

static int8_t Send_buf[6] = { 0 };

/************Command byte**************************/
/*basic commands*/
#define CMD_PLAY  0X01
#define CMD_PAUSE 0X02
#define CMD_NEXT_SONG 0X03
#define CMD_PREV_SONG 0X04
#define CMD_VOLUME_UP   0X05
#define CMD_VOLUME_DOWN 0X06
#define CMD_FORWARD 0X0A // >>
#define CMD_REWIND  0X0B // <<
#define CMD_STOP 0X0E
#define CMD_STOP_INJECT 0X0F//stop interruptting with a song, just stop the interlude

/*5 bytes commands*/
#define CMD_SEL_DEV 0X35
#define DEV_TF 0X01
#define CMD_IC_MODE 0X35
#define CMD_SLEEP   0X03
#define CMD_WAKE_UP 0X02
#define CMD_RESET   0X05

/*6 bytes commands*/
#define CMD_PLAY_W_INDEX   0X41
#define CMD_PLAY_FILE_NAME 0X42
#define CMD_INJECT_W_INDEX 0X43

/*Special commands*/
#define CMD_SET_VOLUME 0X31
#define CMD_PLAY_W_VOL 0X31

#define CMD_SET_PLAY_MODE 0X33
#define ALL_CYCLE 0X00
#define SINGLE_CYCLE 0X01

#define CMD_PLAY_COMBINE 0X45//can play combination up to 15 songs


void sendBytes( uint8_t nbytes ) {
    for (uint8_t i = 0; i < nbytes; i++)//
    {
        myMP3.write( Send_buf[i] );
    }
}

void mp3Basic( int8_t command ) {
    Send_buf[0] = 0x7e; //starting byte
    Send_buf[1] = 0x02; //the number of bytes of the command without starting byte and ending byte
    Send_buf[2] = command;
    Send_buf[3] = 0xef; //
    sendBytes( 4 );
}

void mp3_5bytes( int8_t command, uint8_t dat ) {
    Send_buf[0] = 0x7e; //starting byte
    Send_buf[1] = 0x03; //the number of bytes of the command without starting byte and ending byte
    Send_buf[2] = command;
    Send_buf[3] = dat; //
    Send_buf[4] = 0xef; //
    sendBytes( 5 );
}
void mp3_6bytes( int8_t command, int16_t dat ) {
    Send_buf[0] = 0x7e; //starting byte
    Send_buf[1] = 0x04; //the number of bytes of the command without starting byte and ending byte
    Send_buf[2] = command;
    Send_buf[3] = (int8_t)(dat >> 8);//datah
    Send_buf[4] = (int8_t)(dat); //datal
    Send_buf[5] = 0xef; //
    sendBytes( 6 );
}


void sendCommand( int8_t command, int16_t dat = 0 ) {
    delay( 20 );
    if ((command == CMD_PLAY_W_VOL) || (command == CMD_SET_PLAY_MODE) || (command == CMD_PLAY_COMBINE))
        return;
    else if (command < 0x10) {
        mp3Basic( command );
    } else if (command < 0x40) {
        mp3_5bytes( command, dat );
    } else if (command < 0x50) {
        mp3_6bytes( command, dat );
    } else return;

}

void playWithVolume( int16_t dat ) {
    mp3_6bytes( CMD_PLAY_W_VOL, dat );
}
void setup() {
    myMP3.begin( 9600 );
    delay( 500 );//Wait chip initialization is complete
    sendCommand( CMD_SEL_DEV, DEV_TF );//select the TF card
    delay( 200 );//wait for 200ms
    playWithVolume( 0X2002 );//play the first song with volume 15(0x0F) class
}

void loop() {
    // put your main code here, to run repeatedly:
}
