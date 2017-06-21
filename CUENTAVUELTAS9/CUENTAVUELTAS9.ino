const int pinBocina = 8; //El pin correcto es pin 9 Si no está es para deshabilitar los sonidos
const int pinCoche0 = A1, pinCoche1 = A2;
const int pinPulsador = A0;

const int pinLedVerde = 10, pinLedAma1 = 11, pinLedAma2 = 12, pinLedRojo = 13;

int valorCoche0 = 0, valorCoche1 = 0; //Para leer el valor que nos da cada fotoresistencia
int valorAnteriorCoche0, valorAnteriorCoche1; //Compararemos la anterior con esta para detectar el paso de los coches


int valorPulsador = 0; //Usaremos este valor para la botonera

int VueltasCoche1, VueltasCoche2; //contador de vueltas de los coches
int mejorVueltaCoche1, mejorVueltaCoche2; //Para almacenar la mejor vuelta de cada coche

int valorEstablecido = 1; //Se utilizara para vueltas o para minutos

unsigned long tiempoAnteriorCoche1, tiempoInicialCoche1, mejorTiempoCoche1 = 4294967295;
unsigned long tiempoAnteriorCoche2, tiempoInicialCoche2, mejorTiempoCoche2 = 4294967295;

unsigned long tiempoAnterior[2];

//unsigned long tiempoAnteriorCoche3;
bool enCarrera = false, enSetup = false , enResumen=false;//para poder iniciar la carrera despues del setup
int estadoBotonera = 0; //Variable para ver qué boton está pulsado
bool carreraTime = true; //hacemos true para modo TIME, false para modo LAPS

void setup() {
  // put your setup code here, to run once:
  pinMode(pinBocina, OUTPUT);
//  pinMode(pinCoche0, INPUT);
//  pinMode(pinCoche1, INPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedAma1, OUTPUT);
  pinMode(pinLedAma2, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);

  tiempoAnteriorCoche1 = millis();
  tiempoAnteriorCoche2 = tiempoAnteriorCoche1;
  //cuentaAtrasSemaforo();
  Serial.begin(9600);

  //Serial.print("resultado de tiempo 60000: " );
  //  char paco[ ] = escribirTiempo(60000);
  //  Serial.println (paco);
  //Serial.println (escribirTiempo(1501245));
  InicializarPantalla();
}

void loop()
{

  unsigned long tiempoActual = millis();//BORRAR
  unsigned long tiempoVuelta;//BORRAR
  valorCoche0 = analogRead(pinCoche0);
  valorCoche1 = analogRead(pinCoche1);
//Serial.println(valorCoche1);
  delay(10); //Si no se mete este delay no ve bien el paso de los coches. Tal vez se pueda quitar cuando llenemos más codigo
  if (enCarrera == true) {
    if (tiempoActual > tiempoAnterior[0] + 500) {
      digitalWrite(pinLedRojo, LOW);
      digitalWrite(pinLedAma2, LOW);
    }
    if (tiempoActual > tiempoAnterior[1] + 500) {
      digitalWrite(pinLedVerde, LOW);
      digitalWrite(pinLedAma1, LOW);
    }

    if (valorCoche0 < 220 && valorAnteriorCoche0 > 220){
Serial.println("que pasa el  0");
     registrarPasoCoche(0);
}
    if   (valorCoche1 < 220 && valorAnteriorCoche1 > 220) {
      Serial.println("que pasa el  1");
      registrarPasoCoche(1);

    }
    valorAnteriorCoche0 = valorCoche0;
    valorAnteriorCoche1 = valorCoche1;
  }
  else {
    digitalWrite(pinLedRojo, LOW); ///Para que no se quede encendido ningun LED al final de la carrera
    digitalWrite(pinLedAma2, LOW);
    digitalWrite(pinLedVerde, LOW);
    digitalWrite(pinLedAma1, LOW);
    setupCuentaVueltas();

  }
}
