/* 
 Controlling a servo position using a potentiometer (variable resistor) 
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo


void InitServo()
{
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object

      myservo.write(90);                  // sets the servo position according to the scaled value 
  delay(500); 
}

void RotateServo(int value){
myservo.write(value);
Serial.print("Girado a ");
Serial.println(value);
delay(500);
}
