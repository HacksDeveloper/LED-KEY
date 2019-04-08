#include <EEPROM.h>
const int strobe = 7;
const int clock = 9;
const int data = 8;
int address = 1;
int val;

void sendCommand(uint8_t value)
{
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, value);
  digitalWrite(strobe, HIGH);
}

void reset()
{
  sendCommand(0x41); // set auto increment mode
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc0);   // set starting address to 0
  for(int i = 0; i < 16; i++)
  {
    shiftOut(data, clock, LSBFIRST, 0x00);
  }
  digitalWrite(strobe, HIGH);
}
byte numberSegments[10] = {
  0x3f, //0
  0x06, //1
  0x5B, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f, //9
};

void setup()
{
  pinMode(strobe, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  sendCommand(0x8f);  // activate
  reset();
}

void loop()
{
  EEPROM.write(address, 15);
  val = EEPROM.read(address);
  for(int i = 0; i<256;i++){
      if (i<=9){
        if (i == val){
             digitalWrite(strobe, LOW);
             shiftOut(data, clock, LSBFIRST, 0xc0); 
             shiftOut(data, clock, LSBFIRST, numberSegments[i] );
             digitalWrite(strobe, HIGH);
        }
      }
      else if (i == 10){
        if (i == val){
             digitalWrite(strobe, LOW);
             shiftOut(data, clock, LSBFIRST, 0xc0);
             shiftOut(data, clock, LSBFIRST, numberSegments[1] );
             digitalWrite(strobe, HIGH);
             digitalWrite(strobe, LOW);
             shiftOut(data, clock, LSBFIRST, 0xc2); 
             shiftOut(data, clock, LSBFIRST, numberSegments[0] );
             digitalWrite(strobe, HIGH);
             }
      }
      else if(11<=i && i<=99){
          if(i == val){
              int val2 = i % 10;
              int val1 = (i - val2)/10;
              digitalWrite(strobe, LOW);
              shiftOut(data, clock, LSBFIRST, 0xc0); 
              shiftOut(data, clock, LSBFIRST, numberSegments[val1] );
              digitalWrite(strobe, HIGH);
              digitalWrite(strobe, LOW);
              shiftOut(data, clock, LSBFIRST, 0xc2);
              shiftOut(data, clock, LSBFIRST, numberSegments[val2]);
              digitalWrite(strobe,HIGH);
            }
        }
        else if (i == 100){
         if (i == val){
             digitalWrite(strobe, LOW);
             shiftOut(data, clock, LSBFIRST, 0xc0); 
             shiftOut(data, clock, LSBFIRST, numberSegments[1] );
             digitalWrite(strobe, HIGH);
             digitalWrite(strobe, LOW);
             shiftOut(data, clock, LSBFIRST, 0xc2); 
             shiftOut(data, clock, LSBFIRST, numberSegments[0] );
             digitalWrite(strobe, HIGH);
             digitalWrite(strobe, LOW);
             shiftOut(data, clock, LSBFIRST, 0xc4); 
             shiftOut(data, clock, LSBFIRST, numberSegments[0] );
             digitalWrite(strobe, HIGH);
             }
        }
      else if(101<=i && i<=255){
        if(i == val){
              int temp = i % 100;
              int val3 = temp % 10;
              int val2 = (temp - val3)/10;
              int val1 = (i - temp)/100;
              
              digitalWrite(strobe, LOW);
              shiftOut(data, clock, LSBFIRST, 0xc0); 
              shiftOut(data, clock, LSBFIRST, numberSegments[val1] );
              digitalWrite(strobe, HIGH);
              digitalWrite(strobe, LOW);
              shiftOut(data, clock, LSBFIRST, 0xc2); 
              shiftOut(data, clock, LSBFIRST, numberSegments[val2] );
              digitalWrite(strobe, HIGH);
              digitalWrite(strobe, LOW);
              shiftOut(data, clock, LSBFIRST, 0xc4); 
              shiftOut(data, clock, LSBFIRST, numberSegments[val3] );
              digitalWrite(strobe, HIGH);
        }
        }
    }
}
