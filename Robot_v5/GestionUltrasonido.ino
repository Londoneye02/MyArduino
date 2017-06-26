long distancia;
long tiempo;


const int pinTrigger = 9;
const int PinEcho = 10;
int RotateTime = 500;
void InitUltraSound() {

	pinMode(pinTrigger, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
	pinMode(PinEcho, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
}


void ActivateUltraSoundControl(){

	delay(100);
	ControlActive=true;
	ControlByUltraSound();
}


void deActivateUltraSoundControl(){

	delay(100);
	ControlActive=false;

}
long MeasureDistance (){
	int MyDistance;
	digitalWrite(pinTrigger, LOW); /* Por cuestión de estabilización del sensor*/
	delayMicroseconds(5);
	digitalWrite(pinTrigger, HIGH); /* envío del pulso ultrasónico*/
	delayMicroseconds(10);
	tiempo = pulseIn(PinEcho, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
deja de hacerlo, LOW, la longitud del pulso entrante*/
MyDistance = int(0.017 * tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
MyDistance = int(0.021 * tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/

Serial.print("Distancia ");
Serial.print(MyDistance);
Serial.println(" cm");
delay (100);
return MyDistance;


}


void ControlByUltraSound() {

	distancia= MeasureDistance();
	/*Monitorización en centímetros por el monitor serial*/
	if (distancia < 35 && ControlActive==true) {
		int distanciaCentro =distancia;
		int distanciaDerecha;
		int distanciaIzquierda;
		int distanciaMaxima;
		Serial.println("objeto muy cercano");
		Serial.println(distancia);
		PararMotores();
		delay(100);

		while (distanciaCentro!= distanciaMaxima){
			RotateServo(45);

			distanciaIzquierda= MeasureDistance();
			RotateServo(135);
			distanciaDerecha= MeasureDistance();
			
			RotateServo(90);

			distanciaMaxima=max(distanciaIzquierda,distanciaDerecha);
			if (distanciaIzquierda==distanciaMaxima){
				PivotarIzquierda();
			}
			else{
				PivotarDerecha();
			}
			delay (RotateTime);
			PararMotores();

			distanciaCentro=MeasureDistance();
			distanciaMaxima= max (distanciaMaxima,distanciaCentro);
		}

		IgualarMotoresAdelante();




		ControlActive=true;
	}
}


