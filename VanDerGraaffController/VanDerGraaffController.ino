/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

void setup() {

  
  Serial.begin(115200);
  // Attach the ESC on pin 9
  ESC.attach(8,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  //ESC.attach(9); // (pin, min pulse width, max pulse width in microseconds) 
  int i;
  ESC.write(90);  // neutral = motor stops used to arm ESC
  //ESC.writeMicroseconds(1000);
  delay(1000);

  /*
  for ( i =0; i< 180; i++) {
    ESC.write(i);
    delay(1000);
  }
  
  
  Serial.println(i);
  
   */
   //ESC.write(40);  
   //ESC.writeMicroseconds(2000);
  //ESC.write(180);
  //delay(2000);
  //ESC.write(0);
}

void loop() {
  // potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  // potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
    // Send the signal to the ESC
ESC.write(90);
delay(2000);

int mySpeed=180;
  //delay(100);

Serial.println("Direction one - Accel"); 
for (int s = 90; s<mySpeed; s++){
    ESC.write(s);
    Serial.println(s);
    delay(100);
  }

Serial.println("Direction one - Decel");  
for (int s = mySpeed; s>90; s--) {
  ESC.write(s);
  Serial.println(s);
  delay(100);  
}

Serial.println("Stop");
delay(2000);
pinMode(9, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);

Serial.println("Direction two - Accel"); 

for (int s = 90;s>0; s--){
  ESC.write(s);
  Serial.println(s);
  delay(100);
}


Serial.println("Direction two - Decel"); 

for (int s = 0;s<90; s++){
  ESC.write(s);
  Serial.println(s);
  delay(100);
}

  
Serial.println("Stop");
delay(2000);

  while(true ) ESC.write(90);
  //ESC.writeMicroseconds(1500);

}
