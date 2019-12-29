// Testing sketch for DVD module with TM1628 IC
// Written by Vasyl Yudin, public domain
// www.blockduino.org

const int dataPin = 9;   // VDIO
const int clockPin = 8;  // VCLK
const int strobePin = 7; // VSTR

const int intensity = 1; // яркость 0-7

//unsigned char displ[14]={0x08,0x00,0x80,0x00,0xb5,0x00,0xaf,0x00,0xbd,0x00,0x01,0x00,0xb1,0x00};// b_duino
unsigned char displ[14]={0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00};// b_duino
unsigned char s_addr[8] ={0x03,0x0b,0x0d,0x07,0x05,0x09,0x0d,0x01};
unsigned char s_byte[8] ={0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x01};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(strobePin, OUTPUT);

  digitalWrite(strobePin, HIGH);
  digitalWrite(clockPin, HIGH);

  t_sendCommand(0x40);
  t_sendCommand(0x88 | min(7, intensity));

  digitalWrite(strobePin, LOW);
  t_send(0xC0);
  for (int i = 0; i < 16; i++) {
    t_send(0x00);
  }
  digitalWrite(strobePin, HIGH);
  
// show on display: b_duino
    for (int i=0; i<14; i++) {
    t_sendData(i, displ[i]);
    delay(2);
  }
  delay(3000);
}

void loop() {
//  for (int i=0;i<8;i++){
//    t_sendData(s_addr[i], s_byte[i]);
//    delay(125);
//    t_sendData(s_addr[i], 0x00);
//  }  
}

//custom functions
void updateLEDs() {
   for (int i=0; i<14; i++) {
    t_sendData(i, displ[i]);
  }
}

void t_sendCommand(byte cmd)
{
  digitalWrite(strobePin, LOW);
  t_send(cmd);
  digitalWrite(strobePin, HIGH);
}

void t_sendData(byte address, byte data)
{
  t_sendCommand(0x44);
  digitalWrite(strobePin, LOW);
  t_send(0xC0 | address);
  t_send(data);
  digitalWrite(strobePin, HIGH);
}

void t_send(byte data)
{
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, data & 1 ? HIGH : LOW);
    data >>= 1;
    digitalWrite(clockPin, HIGH);
  }
}
