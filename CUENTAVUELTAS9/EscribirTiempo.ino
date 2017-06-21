char* escribirTiempo_old (unsigned long tiempo)
{
  //Char[] Parte1 ="perico";
  char Parte1[ ] = "arduino";
  //Serial.println (Parte1);
  return (Parte1);
}

String escribirTiempo (unsigned long tiempo)
{
  float segundos;
  byte minutos = 0;
  byte horas;

  String Parte1 = "00";
  String Parte2;


  if (tiempo < 60000) {
    // Serial.println(tiempo);
    segundos = tiempo;
    segundos = segundos / 1000;

  }
  else
  {
    minutos = tiempo / 60000;

    segundos = tiempo - (minutos * 60000);
    segundos = segundos / 1000;

  }
  if (minutos < 10) {
    Parte1 = "0" + String (minutos);
  }
  else {
    Parte1 = String (minutos);
  }
    if (segundos < 10) {
    Parte2 = "0" + String (segundos);
  }
  else {
    Parte2 = String (segundos);
  }
  
  //Parte2 = String(segundos);

  return Parte1 + ":" + Parte2;
  
}

void printTime(int NumeroVuelta,byte numeroCoche, unsigned long tiempo)

{
  Serial.println("");
  Serial.print("Paso coche ");
  Serial.println(numeroCoche);
//  LimpiarFila(numeroCoche);
//  PrintLCD (numeroCoche,0, "Paso coche ");
//  PrintLCD (numeroCoche, 11,String(numeroCoche+1));
  //tone(pinBocina,330,200);

Serial.println(escribirTiempo(tiempo));
  LimpiarFila(numeroCoche);
 PrintLCD (numeroCoche, 0,String(NumeroVuelta));
  PrintLCD (numeroCoche, 1,":");
 PrintLCD(numeroCoche,5,escribirTiempo(tiempo));
}

void printTime_old(byte numeroCoche, unsigned long tiempo)

{
  float segundos;
  byte minutos;
  byte horas;
  Serial.print("Paso coche ");
  Serial.println(numeroCoche);
  //tone(pinBocina,330,200);

  if (tiempo < 60000) {
    // Serial.println(tiempo);
    segundos = tiempo;
    segundos = segundos / 1000;
    Serial.println(segundos);
  }
  else
  {
    minutos = tiempo / 60000;

    segundos = tiempo - (minutos * 60000);
    segundos = segundos / 1000;
    Serial.print (minutos);
    Serial.print (":");
    Serial.println (segundos);
  }
}


bool printLap(byte numeroCoche, int vuelta) {
  Serial.print("Vuelta n:");
  Serial.println(vuelta);



  if (carreraTime == false) {
    int quedanVueltas = valorEstablecido - vuelta;
    if (quedanVueltas == 0) {
      return false;
    }
    else if (quedanVueltas == 1) {
      Serial.println ("Queda 1 vuelta");
      return true;
    }
    else {
      Serial.print ("Quedan " );
      Serial.print (quedanVueltas);
      Serial.println (" vueltas");
      return true;
    }
  }
  else {
    return true;
  }
}
