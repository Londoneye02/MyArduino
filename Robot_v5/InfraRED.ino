int Resultado;
int PruebaAutocompletion;
void InitIR()
{
	irrecv.enableIRIn(); // Start the receiver
}

void RecibirIR() {
	if (irrecv.decode(&results)) {
		//Serial.println(results.value, HEX);
		Resultado = results.value;

		irrecv.resume(); // Receive the next value

		switch (Resultado) {

		case 0xFFFFCBF0:
			//Boton 1 Avanza solo el motor de la izquierda
			Serial.println("MOTOR_IZQUIERDA");
			PararMotorDerecho();
			AvanzarMotorIzquierdo();
			break;
		case 0xFFFFCBE8:
			//Boton 3 Avanza solo el motor de la derecha
			Serial.println("MOTOR_DERECHA");
			PararMotorIzquierdo();
			AvanzarMotorDerecho();
			break;

		case 0x687CBC8:
			//Boton 2 Avanzan los dos motores a la misma velocidad
			Serial.println("ADELANTE");

			ActivateUltraSoundControl();
			
			
			IgualarMotoresAdelante();

			break;

		case 0x687CBCC:
			//Boton 8 Retroceden los dos motores a la misma velocidad
			Serial.println("ATRAS");
			RetrocederMotorIzquierdo();
			RetrocederMotorDerecho();
			break;

		case 0x687CBC4:
			//Boton 5 Parar los dos motores
			Serial.println("PARAR");
			deActivateUltraSoundControl();
			PararMotores();
			break;

		case 0xFFFFCBE4:
			//Boton 6 Frenamos el motor derecho para girar a la derecha
			Serial.println("DERECHA");
			FrenarMotorDerecho();
			break;
		case 0x687CBF8:
			//Boton 4 Frenamos el motor izquierdo para girar a la izquierda
			Serial.println("IZQUIERDA");
			FrenarMotorIzquierdo();
			break;

		case 0x687CBEC:
			//Boton 9 Avanzamos el motor izquierdo y retrocedemos el derecho para que gire sobre sí mismo hacia la derecha
			Serial.println("PIVOTAR_DERECHA");
			PivotarDerecha();
			break;
		case 0x687CBF4:
			//Boton 7 Avanzamos el motor derecho y retrocedemos el izquierdo para que gire sobre sí mismo hacia la izquierda
			Serial.println("PIVOTAR_IZQUIERDA");
			PivotarIzquierda();
			break;
		case 0x687CBCA:
			Serial.println("VEL +");
			AcelerarMotorDerecho();
			AcelerarMotorIzquierdo();
			break;
		case 0x687CBFA:
			Serial.println("VEL -");
			FrenarMotorDerecho();
			FrenarMotorIzquierdo();
			break;
		default:
			Serial.println(Resultado, HEX);
			// if nothing else matches, do the default
			// default is optional
		}

	}
}
