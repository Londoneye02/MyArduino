MotorController::MotorController(int PF0,int PF1,int PB0,int PB1,int PE0,int PE1)
{
PinAdelante={PF0,PF1};
PinAtras={PB0,PB1};
PinEnable={PE0,PE1};
MotorSpeed={150,150};
motorDirection = {1,1};

	for (int i = 0; i < 2; i++) 
	{

    //Set digital I/O
    pinMode(PinAdelante[i], OUTPUT);
    pinMode(PinAtras[i], OUTPUT);
    pinMode(PinEnable[i], OUTPUT);

    // pull the enable pin LOW to start
    digitalWrite(PinEnable[i], LOW);
    changeMotorDir(i);
	}
  }

void InitMotors() {
  for (int i = 0; i < 2; i++) {

    //Set digital I/O
    pinMode(PinAdelante[i], OUTPUT);
    pinMode(PinAtras[i], OUTPUT);
    pinMode(PinEnable[i], OUTPUT);

    // pull the enable pin LOW to start
    digitalWrite(PinEnable[i], LOW);
    changeMotorDir(i);
  }
}

void changeMotorDir(byte NumeroMotor) {
  if (motorDirection[NumeroMotor] == 1) {
    digitalWrite(PinAdelante[NumeroMotor], HIGH);
    digitalWrite(PinAtras[NumeroMotor], LOW);
  }
  else {
    digitalWrite(PinAdelante[NumeroMotor], LOW);
    digitalWrite(PinAtras[NumeroMotor], HIGH);
  }
}

void MotorAdelante (byte NumeroMotor) {
  motorDirection[NumeroMotor] = 1;
  changeMotorDir(NumeroMotor);
  //digitalWrite (PinEnable[NumeroMotor], HIGH);
 // analogWrite (PinEnable[NumeroMotor], 150);
 analogWrite(PinEnable[NumeroMotor], motorSpeed[NumeroMotor]);
 delay(100);
 Serial.print ("Encender el Pin: ");
 Serial.print(PinEnable[NumeroMotor]);
 Serial.print(". Velocidad del motor: ");
 Serial.println(motorSpeed[NumeroMotor]);
}
void MotorAdelante_dig (byte NumeroMotor) {
  motorDirection[NumeroMotor] = 1;
  changeMotorDir(NumeroMotor);
  digitalWrite (PinEnable[NumeroMotor], HIGH);
  //analogWrite (PinEnable[NumeroMotor], 150);
  delay(100);
  Serial.print ("Encender el Pin: ");
  Serial.println(PinEnable[NumeroMotor]);
}

void PararMotor (byte NumeroMotor) {

  digitalWrite (PinEnable[NumeroMotor], LOW);
  Serial.print ("Apagar el Pin: ");
  Serial.println(PinEnable[NumeroMotor]);
}

void MotorAtras (byte NumeroMotor) {
  motorDirection[NumeroMotor] = 0;
  changeMotorDir(NumeroMotor);
  //digitalWrite (PinEnable[NumeroMotor], HIGH);
  //analogWrite (PinEnable[NumeroMotor], 50);
  analogWrite(PinEnable[NumeroMotor], motorSpeed[NumeroMotor]);
  delay(100);
  Serial.print ("Encender el Pin: ");
  Serial.println(PinEnable[NumeroMotor]);
}

void AcelerarMotor (byte NumeroMotor) {
  if (motorSpeed[NumeroMotor] < 250) {
    motorSpeed[NumeroMotor] += 25;
    analogWrite(PinEnable[NumeroMotor], motorSpeed[NumeroMotor]);
    Serial.print ("Motor ");
    Serial.print(NumeroMotor);
    Serial.print (" acelerado. Velocidad: ");
    Serial.println(motorSpeed[NumeroMotor]);
  }
}

void FrenarMotor (byte NumeroMotor) {
  if (motorSpeed[NumeroMotor] >0) {
    motorSpeed[NumeroMotor] -= 25;
    analogWrite(PinEnable[NumeroMotor], motorSpeed[NumeroMotor]);
    
    Serial.print ("Motor ");
    Serial.print(NumeroMotor);
    Serial.print (" frenado. Velocidad: ");
    Serial.println(motorSpeed[NumeroMotor]);
  }
}


void AvanzarMotorDerecho() {
  MotorAdelante(1);
}
void PararMotorDerecho() {
  PararMotor(1);
}
void RetrocederMotorDerecho() {
  MotorAtras(1);
}
void AcelerarMotorDerecho() {
  AcelerarMotor(1);
}
void FrenarMotorDerecho() {
  FrenarMotor(1);
}

void AvanzarMotorIzquierdo() {
  MotorAdelante(0);
}
void PararMotorIzquierdo() {
  PararMotor(0);
}
void RetrocederMotorIzquierdo() {
  MotorAtras(0);
}
void AcelerarMotorIzquierdo() {
  AcelerarMotor(0);
}
void FrenarMotorIzquierdo() {
  FrenarMotor(0);
}

void MoverMotores(int ValorMotor1, int ValorMotor2) {
  ChangeMotorDir2(1, ValorMotor1);
  ChangeMotorDir2(2, ValorMotor2);
}

void IgualarMotoresAdelante(){
  int NuevaVelocidad=max(motorSpeed[0],motorSpeed[1]);
  motorSpeed[0]=NuevaVelocidad;
  motorSpeed[1]=NuevaVelocidad;
  AvanzarMotorDerecho();
  AvanzarMotorIzquierdo();
}
void ChangeMotorDir2 (byte NumeroMotor, int ValorVelocidad) {
  if (ValorVelocidad >= 0) {
    digitalWrite(PinAdelante[NumeroMotor], HIGH);
    digitalWrite(PinAtras[NumeroMotor], LOW);
  }
  else {
    digitalWrite(PinAdelante[NumeroMotor], LOW);
    digitalWrite(PinAtras[NumeroMotor], HIGH);
  }



}

void PararMotores(){

  PararMotorIzquierdo();
  PararMotorDerecho();

  
}

void PivotarDerecha(){
  AvanzarMotorIzquierdo();
  RetrocederMotorDerecho();
}

void PivotarIzquierda(){
  AvanzarMotorDerecho();
  RetrocederMotorIzquierdo();
}