// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 3, 4, 5, 6, 7);
byte ii=0;

void InicializarPantalla(){
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  // set up the switch pin as an input

lcd.clear();
  // Print a message to the LCD.
  lcd.print("CuentaVueltas");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("7.0");
}

void PrintLCD(byte fila, byte columna, String texto){
lcd.setCursor(columna,fila);
lcd.print(texto);
delay(5);

}
void LimpiarPantalla(){
lcd.clear();
}

void LimpiarFila(byte fila){


lcd.setCursor(0,fila);
  for (ii = 0; ii < 16; ii = ii + 1) {
    lcd.print(" ");
  }
  }
