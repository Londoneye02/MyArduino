
void setupCuentaVueltas() {

  valorPulsador = analogRead(pinPulsador);


  // Serial.println (valorPulsador);
  if (valorPulsador == 0) {
    estadoBotonera = 0;
    tiempoAnteriorCoche2 = millis(); //Lo vamos a establecer como referencia para saber cuando fue la última vez que ningun boton estuvo pulsado
  }
  if (valorPulsador > 502 && valorPulsador < 522) { //Caso de Boton A
    if (estadoBotonera == 0) { //Esto es para que solo actue cuando anteriormente no estada ningun boton pulsado
      estadoBotonera = 1;
      enSetup = true;

      if (valorEstablecido < 1000) {
        valorEstablecido += 1;
      }
      Serial.println ("Boton A");
      Serial.println(valorEstablecido);
           mostrarValor(); 

    }

  }

  else if (valorPulsador > 990 && valorPulsador < 1010) {//Caso de Boton B

    if (estadoBotonera == 0)
    {
      Serial.println ("Boton B");
      estadoBotonera = 2;
      //valorEstablecido = 1;
      if (enSetup == true) { //Esto significa que hemos cambiado los valores de tiempo o vueltas y queremos empezar
        Serial.println ("Empieza la carrera");
        LimpiarPantalla();
        PrintLCD(0,4,"COMIENZA");
        PrintLCD(1,3,"LA CARRERA");
        cuentaAtrasSemaforo();
        inicializarValores;

        VueltasCoche1 = -1;
        VueltasCoche2 = -1;
        vueltas[1] = -1;
        vueltas[0] = -1;
        //        for (byte contadorCoches=0;contadorCoches=1;contadorCoches++){
        //        vueltas[contadorCoches]=-1;
        //        }


        enCarrera = true;
      }
      else {
        LimpiarFila(0);
        if (carreraTime == true) {
          carreraTime = false;
          Serial.println("Modo LAPS");
          PrintLCD(0, 0, "Modo LAPS");
        }
        else {
          carreraTime = true;
          Serial.println("Modo TIME");
          PrintLCD(0, 0, "Modo TIME");
        }
      }
    }
    else if (estadoBotonera == 2)
    {
      tiempoAnteriorCoche1 = millis(); //Lo vamos a utilizar como tiempo Actual
      if ((tiempoAnteriorCoche1 - tiempoAnteriorCoche2) > 3000) {
        Serial.println("ReSET");
      }
    }
  }

  else if (valorPulsador == 1023) //Caso de Boton C
  {
    if (estadoBotonera == 0) {
      estadoBotonera = 3;
      if (valorEstablecido > 1) {
        valorEstablecido -= 1;
      }

      Serial.println ("Boton C");
      Serial.println(valorEstablecido);
      mostrarValor();
    }
  } //aqui meter el codigo de los botones


}


void cuentaAtrasSemaforo()
{
  digitalWrite(pinLedRojo, HIGH);
  tone(pinBocina, 220, 500);
  PrintLCD(0,0,"4");
  PrintLCD(0,15,"4");
  delay(1000);
  digitalWrite(pinLedAma2, HIGH);
  tone(pinBocina, 220, 500);
  PrintLCD(0,0,"3");
  PrintLCD(0,15,"3");
  delay(1000);
  digitalWrite(pinLedAma1, HIGH);
  tone(pinBocina, 220, 500);
  PrintLCD(0,0,"2");
  PrintLCD(0,15,"2");
  delay(1000);
  digitalWrite(pinLedVerde, HIGH);
  tone(pinBocina, 440, 500);
  PrintLCD(0,0,"1");
  PrintLCD(0,15,"1");
  delay(1000);
  PrintLCD(0,0,"0");
  PrintLCD(0,15,"0");
  digitalWrite(pinLedRojo, LOW);
  digitalWrite(pinLedAma1, LOW);
  digitalWrite(pinLedAma2, LOW);
  digitalWrite(pinLedVerde, LOW);
}

void pitidoLlegada () {
  for (int contador = 0; contador < 4; contador++) {
    tone(pinBocina, 440, 165);
    delay(181);
    noTone(9);

  }
}

void mostrarValor(){

LimpiarFila(1);
      PrintLCD(1, 0, String(valorEstablecido));


      if (carreraTime == false)
      {
        PrintLCD(1, 2, "VUELTA");
      }
      else
      {
        PrintLCD(1, 2, "MINUTO");
      }
      if (valorEstablecido > 1)
      {
        PrintLCD(1, 8, "S");
      }




}

