#include <LiquidCrystal_I2C.h>

// Construct an LCD object and pass it the
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.

//Colocar los valores modulos de pantalla y i2c pegados
//MODULO-->esp
//GND--gnd
//VCC--VU
//SDA-> D2
//SCL->D1
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int incomingByte = 0;
String a;

void setup() {

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(16, 2);
  lcd.init();

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  // Turn on the backlight.
  lcd.backlight();
  lcd.setBacklight(520);
  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(0, 0);

  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HOLA");

  // Move the cursor to the next line and print
  // WORLD.
  lcd.setCursor(0, 1);
  lcd.print("ARAIA");
}

void loop() {

  while (Serial.available()) {

    a = Serial.readString(); // read the incoming data as string
lcd.setCursor(0, 1);
    Serial.println(a);
    lcd.noCursor();
    lcd.print(a);
    delay(3000);
    lcd.setCursor(0, 1);
       delay(2000);
    lcd.print("                          ");
    lcd.setCursor(0, 1);
     lcd.cursor();
  }
delay(300);
lcd.noCursor();
delay(300);
lcd.cursor();

}
