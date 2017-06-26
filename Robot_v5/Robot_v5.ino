
#include <IRremote.h>//Libreria para controlar el IR

//Variables para el control Remoto
int RECV_PIN = 11; // pin del receptro IR. Patillaje: Vout/GND/Vin. Poner resistencia de 10K entre patilla 1 y 3
IRrecv irrecv(RECV_PIN);//Instancia de receptor de IR
decode_results results;//Instancia de resultados de entrada IR
////////////////////////////////

//Variables para control de Motores
const int PinAdelante[2] = {3,2}; // connected to pin 7 on the H-bridge
const int PinAtras[2] = {7,4}; // connected to pin 2 on the H-bridge
const int PinEnable[2] = {5,6};   // connected to pin 1 on the H-bridge
int motorSpeed[2] = {150,150}; // speed of the motor
int motorDirection[2] = {1,1}; // current direction of the motor
//Esto es una prueba a ver si funciona



// create some variables to hold values from your inputs
int onOffSwitchState = 0;  // current state of the On/Off switch
int previousOnOffSwitchState = 0; // previous position of the on/off switch
int directionSwitchState = 0;  // current state of the direction switch
int previousDirectionSwitchState = 0;  // previous state of the direction switch

///int motorEnabled = 0; // Turns the motor on/off

//prueba para el control ultrasonido

bool ControlActive = false;


void setup()
{
  Serial.begin(9600);
  InitIR();
  InitMotors();
  InitServo();
  InitUltraSound();
}

void loop() {

  RecibirIR();
  ControlByUltraSound();
  // int PruebaDistancia;
  // PruebaDistancia=MeasureDistance();
  // int DistanciaMedida;
  // DistanciaMedida = MeasureDistance();
  // Serial.print(DistanciaMedida);
  // Serial.println(" cm a obstaculo");
}



