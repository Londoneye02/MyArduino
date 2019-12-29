// Testing sketch for DVD module with TM1628 IC
// Written by Vasyl Yudin, public domain
// www.blockduino.org

const int dio = 9;   // VDIO
const int clk = 8;  // VCLK
const int stb = 7; // VSTR




void sendCommand(uint8_t value)
{
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, value);
  digitalWrite(stb, HIGH);
}

void reset()
{
  sendCommand(0x40); // set auto increment mode
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOut(dio, clk, LSBFIRST, 0x00);
  }
  digitalWrite(stb, HIGH);
}


void display(long digit,int cell)
{
  int numb=0;
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0xc0+(cell-1)*2); // what cell we are going to display into

switch (digit)
{

case 0: numb= 0b00111111; break;//digit 0
case 1: numb= 0b00000110; break;//digit 1
case 2: numb= 0b01011011; break;//  .
case 3: numb= 0b01001111; break;//  .
case 4: numb= 0b01100110; break;//  .
case 5: numb= 0b01101101; break;//  .
case 6: numb= 0b01111101; break;//  .
case 7: numb= 0b00000111; break;//  .
case 8: numb= 0b01111111; break;//  .
case 9: numb= 0b01101111; break;// digit 9
}  
  
  shiftOut(dio, clk, LSBFIRST, numb);//display the number
  digitalWrite(stb, HIGH);
}



void display_int(long numb)
{
  if (numb>99999999) return;// can display values from -9999999  upto 99999999 on 8 cells 
   if (numb<-9999999) return;
   int sign=0;//positive number
   if (numb<0) sign=1; // is negative number
int i=8;// 8 digits display
while (abs(numb)>0)

     {

      display(abs(numb)%10,i);//show a single digit from the number which is the one to the right
       numb/=10;// get rids of the digits we already put on the display
       i--;//move a cell to the left
     }
if (sign)
  display_minus(i);//display minus if negative number
}


void  display_minus(int location)
{

      digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0xc0+(location-1)*2); // led on
  
  shiftOut(dio, clk, LSBFIRST, 0b01000000);
  digitalWrite(stb, HIGH);
  
}



void setup()
{
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dio, OUTPUT);

  sendCommand(0x8f);  // activate
  reset();
  sendCommand(0x44);  // set single address
}

void loop()
{
  



display_int(-45279);

 
}
