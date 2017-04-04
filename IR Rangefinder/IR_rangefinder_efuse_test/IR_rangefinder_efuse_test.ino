/************************************************************************/
/*
Origianl Code by Professor Chris Atkeson (CS) of CMU

Modified by Greg Tighe, RBE Major at WPI

Code is for burning the slave address E-Fuses of SHARP IR Sensors;
GP2Y0E02B GP2Y0E03

Arduino must be connected to Serial
Sensor should be plugged into 3.3v, GND, SCL and SDA pins

This code should run on any Arduino with Serial and i2c buses
*/


/************************************************************************/

#include <Wire.h>

/************************************************************************/

#define OLD_ADDRESS (0x40)
#define NEW_ADDRESS (0x78)  // new hex address bit-shifted one bit right 
                            // (chip addr 0x10 becomes 0x08 here)
#define SET_ADDRESS (0x0F)  // the second half of this byte is the first half of
                            // the new address byte you are setting 
                            // 0x01 here becomes 0x10, 0x02 becomes 0x20, etc.

#define DISTANCE_H 0x5E
#define DISTANCE_L 0x5F

/************************************************************************/

void wait_for_user_input( void )
{
  // wait for user input
  while ( !Serial.available() )
    ;

  // then ignore it and continue
  while ( Serial.available() )
    Serial.read();
}

/************************************************************************/

void setup()
{
  Wire.begin();        // join i2c bus 
  Serial.begin( 115200 );  // start serial 
}

/************************************************************************/

void loop()
{
  Serial.println("Program Begin");
  delay(1000);

  unsigned int c;
  int count = 0;


  // step 1
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEC );
  Wire.write( 0xFF );
  Wire.endTransmission();  
  delay( 1 );
  Serial.println( "Apply 3.3V to Vpp. Wait a few seconds and do NOT remove it." );
  Serial.println( "Send 1 character to continue." );
  wait_for_user_input();


  // step 2
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xC8 );
  Wire.write( 0x00 );
  Wire.endTransmission();
  delay( 1 );

  // step 3
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xC9 );
  Wire.write( 0x45 );
  Wire.endTransmission();
  delay( 1 );

  // step 4
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xCD );
  Wire.write( SET_ADDRESS );       // new addr gets set here
  Wire.endTransmission();
  delay( 1 );

  // step 5
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xCA );
  Wire.write( 0x01 );
  Wire.endTransmission();
  delayMicroseconds( 500 );

  // step 6
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xCA );
  Wire.write( 0x00 );
  Wire.endTransmission();
  Serial.println( "Remove 3.3V line from Vpp" );
  Serial.println( "Send 1 character to continue.\n" );
  wait_for_user_input();

  // step 7
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEF );
  Wire.write( 0x00 );
  Wire.endTransmission();
  delay( 1 );

  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xC8 );
  Wire.write( 0x40 );
  Wire.endTransmission();
  delay( 1 );

  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xC8 );
  Wire.write( 0x00 );
  Wire.endTransmission();
  delay( 1 );

  // step 8
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEE );
  Wire.write( 0x06 );
  Wire.endTransmission();
  delay( 1 );

  // step 9
  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEC );
  Wire.write( 0xFF );
  Wire.endTransmission();
  delay( 1 );

  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEF );
  Wire.write( 0x03 );
  Wire.endTransmission();
  delay( 1 );

  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0x27 );
  Wire.endTransmission();

  Wire.requestFrom( OLD_ADDRESS, 1 );    // request 1 byte
  while (!Wire.available()) { };      // Wait for receipt
  c = Wire.read();
  delay( 1 );

  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEF );
  Wire.write( 0x00 );
  Wire.endTransmission();
  delay( 1 );

  Wire.beginTransmission( OLD_ADDRESS );
  Wire.write( 0xEC );
  Wire.write( 0x7F );
  Wire.endTransmission();
  delay( 1 );

  Serial.println("Program Done");
  Serial.print("0x27 data is ");
  Serial.println(c);
  Serial.println("Send one character to test");
  wait_for_user_input();

  while (true) {
    unsigned int c1, c2;
    float dist;

    Wire.beginTransmission( NEW_ADDRESS ); // send Slave ID
    Wire.write( DISTANCE_H );              
    Wire.endTransmission();

    Wire.requestFrom( NEW_ADDRESS, 1 );    // request 1 byte
    while (!Wire.available()) { };      // Wait for receipt
    c1 = Wire.read();

    Wire.beginTransmission( NEW_ADDRESS ); // send Slave ID
    Wire.write( DISTANCE_L );
    Wire.endTransmission();

    Wire.requestFrom( NEW_ADDRESS, 1 );    // request 1 byte
    while (!Wire.available()) { };      // Wait for receipt
    c2 = Wire.read();

    dist = ((float) (c1 * 16 + c2)) / 64.0;

    Serial.print( dist );
    Serial.println( "" );

    delay( 1000 );
  }
}

/************************************************************************/

