
int vueltas[2], mejorVuelta[2];
unsigned long tiempoInicial[2];
unsigned long mejorTiempo[2] = {4294967295, 4294967295};
bool finalizado[2];


void registrarPasoCoche(byte indiceCoche) {

  unsigned long tiempoActual = millis();
  unsigned long tiempoVuelta;
//  Serial.print ("registrado paso coche ");
//Serial.println(indiceCoche);
  if (vueltas[indiceCoche] == -1) {
    vueltas[indiceCoche] = 0;

    Serial.print("Primer paso Coche ");
    Serial.println (indiceCoche);
    tiempoAnterior[indiceCoche] = tiempoActual;
    tiempoInicial[indiceCoche] = tiempoActual;

  }

  else {
    tiempoVuelta = (tiempoActual - tiempoAnterior[indiceCoche]);

    if (tiempoVuelta > 1000) { //Nos aseguramos de que haya pasado más de un segundo para evitar falsos positivos
      printTime(vueltas[indiceCoche]+1,indiceCoche, tiempoVuelta);

      tiempoAnterior[indiceCoche] = tiempoActual;

      encenderLED(indiceCoche);
      vueltas[indiceCoche] += 1;

      if (tiempoVuelta < mejorTiempo[indiceCoche]) {//Para calcular la vuelta rapida
        mejorTiempo[indiceCoche] = tiempoVuelta;
        mejorVuelta[indiceCoche] = vueltas[indiceCoche];
        encenderLED(indiceCoche + 10); //Si marcamos mejor vuelta se enciende el LED
        tone(pinBocina, 440, 500); //Emitimos pitido más agudo
      }
      else {
        tone(pinBocina, 220, 500); //Emitimos pitido mas grave

      }



      if (printLap(indiceCoche, vueltas[indiceCoche]) == false) {
        delay (600);
        pitidoLlegada();
        Serial.println("Final de carrera");
        Serial.print("Tiempo total Coche ");
        Serial.print(indiceCoche);
        Serial.print ("  ");
        Serial.println(escribirTiempo(tiempoActual - tiempoInicial[indiceCoche]));
        Serial.print("Mejor Vuelta Coche ");
        Serial.print(indiceCoche);
        Serial.println(" :");
        Serial.print("Vuelta ");
        Serial.print(mejorVuelta[indiceCoche]);
        Serial.print(" ");
        Serial.println(escribirTiempo(mejorTiempo[indiceCoche]));


        enCarrera = false;

      }
    }
  }
}

void encenderLED(byte indice) {
switch (indice) {
  case 0:
     digitalWrite(pinLedRojo, HIGH);
    break;
    case 1:
     digitalWrite(pinLedVerde, HIGH);
     break;
   case 10:
     digitalWrite(pinLedAma2, HIGH);
      break;
    case 11:
     digitalWrite(pinLedAma1, HIGH);
     break;

 }


}


