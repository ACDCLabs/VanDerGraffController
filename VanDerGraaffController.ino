/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

#define UP_BUTTON 9
#define DOWN_BUTTON 10
#define MILLIS_TO_WAIT 500 // if a button is pressed logner speed changes faster
#define CHANGE_WAIT_MILLIS 50 // if button is pressed longer the wait time to change speed is increases / decreased by this 

#define MAX_FORWARD_SPEED 180
#define STOP_MOTOR 90
#define MAX_BACKWARD_SPEED 0

int speed = STOP_MOTOR;

void setup() {

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  Serial.begin(115200);
  // Attach the ESC on pin 9
  ESC.attach(8, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  //ESC.attach(9); // (pin, min pulse width, max pulse width in microseconds)
  int i;
  ESC.write(STOP_MOTOR);  // neutral = motor stops used to arm ESC
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
  //ESC.write(90);
  // delay(2000);

  /*
    Serial.print("up:");
    Serial.println(digitalRead(UP_BUTTON));
    Serial.print("down:");
    Serial.println(digitalRead(DOWN_BUTTON));
  */
  int millisToWait;
  millisToWait = MILLIS_TO_WAIT;

  while (digitalRead(UP_BUTTON) == LOW) {
    if ( wait(millisToWait)  == true) {
      if (speed < MAX_FORWARD_SPEED) speed ++;
      ESC.write(speed);
      Serial.print("waitMillies: ");
      Serial.println(millisToWait);
      if (millisToWait > CHANGE_WAIT_MILLIS) millisToWait -= CHANGE_WAIT_MILLIS;
      Serial.print("Speed: ");
      Serial.println(speed);

    }

  }

  while (digitalRead(DOWN_BUTTON) == LOW) {
    if ( wait(millisToWait)  == true) {
      if (speed > MAX_BACKWARD_SPEED) speed --;
      ESC.write(speed);
      Serial.print("waitMillies: ");
      Serial.println(millisToWait);
      if (millisToWait > CHANGE_WAIT_MILLIS) millisToWait -= CHANGE_WAIT_MILLIS;
      Serial.print("Speed: ");
      Serial.println(speed);
    }

  }

}

bool  wait(int millisWait) {

  static bool didStart = false;
  static int startMillis;
  static int millisPassed;


  if (!didStart) {
    didStart = true;
    startMillis = millis();
    millisPassed = 0;
  }

  millisPassed = millis() - startMillis;

  if (millisPassed >= millisWait) {
    didStart = false;
    startMillis = 0;
    return true;
  }
  else return false;

}


void moveMotor() {
  int mySpeed = 180;
  //delay(100);

  Serial.println("Direction one - Accel");
  for (int s = 90; s < mySpeed; s++) {
    ESC.write(s);
    Serial.println(s);
    delay(100);
  }

  Serial.println("Direction one - Decel");
  for (int s = mySpeed; s > 90; s--) {
    ESC.write(s);
    Serial.println(s);
    delay(100);
  }

  Serial.println("Stop");
  delay(2000);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  Serial.println("Direction two - Accel");

  for (int s = 90; s > 0; s--) {
    ESC.write(s);
    Serial.println(s);
    delay(100);
  }


  Serial.println("Direction two - Decel");

  for (int s = 0; s < 90; s++) {
    ESC.write(s);
    Serial.println(s);
    delay(100);
  }


  Serial.println("Stop");
  delay(2000);

  while (true ) ESC.write(90);
  //ESC.writeMicroseconds(1500);


}
