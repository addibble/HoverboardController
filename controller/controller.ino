#include <SoftwareSerial9.h>

#define MOSI 11
#define MISO 12
#define TX MOSI
#define RX MISO
#define LEDPIN 13

SoftwareSerial9 mySerial(RX,TX);

void setup() {
  mySerial.begin(26315);
  Serial.begin(115200);
}

char c = ' ';
signed int sp=0;

void loop() {
  Serial.println(c);
  if(c == ' ') {
    sp=0;
  } else if(c == 'q') {
    sp -= 10;
  } else if(c == 'w') {
    sp += 10;
  } else if(c == '2') {
    sp += 100;
  }  else if(c == '1') {
    sp -= 100;
  }
  Serial.print("speed ");
  Serial.println(sp);
  Serial.print(" low byte ");
  Serial.print((sp & 0xFF), HEX);
  Serial.print(" high byte ");
  Serial.println((sp >> 8) & 0xFF, HEX);
  do {
      mySerial.write9(256);
      mySerial.write9(sp & 0xFF);
      mySerial.write9((sp >> 8) & 0xFF);
      mySerial.write9(sp & 0xFF);
      mySerial.write9((sp >> 8) & 0xFF);
      mySerial.write9(85);
      delayMicroseconds(300);
  } while(!Serial.available());
  c=Serial.read();
}
