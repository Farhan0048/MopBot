#include <Servo.h>
Servo myServo;

int r_motor_n = 10; //PWM control Right Motor +
int r_motor_p = 11; //PWM control Right Motor -
int l_motor_p = 9; //PWM control Left Motor -
int l_motor_n = 8; //PWM control Left Motor ++542
int en1 = 5, en2 = 6, en3 = 3;
int pump_p = 4, pump_n = 7;
int mop_p = 12, mop_n = 13;
int serv = 3;
int speedy = 75;
int incomingByte = 0; // for incoming serial data

int param_p = 1, param_m = 1, param_r = 1;

void setup()
{
  //  Serial.begin(57600);
  myServo.attach(2);
  myServo.write(45);
  pinMode(r_motor_n, OUTPUT); //Set control pins to be outputs
  pinMode(r_motor_p, OUTPUT);
  pinMode(l_motor_p, OUTPUT);
  pinMode(l_motor_n, OUTPUT);
  pinMode(pump_p, OUTPUT);
  pinMode(pump_n, OUTPUT);
  pinMode(mop_p, OUTPUT);
  pinMode(mop_n, OUTPUT);
  digitalWrite(r_motor_n, LOW); //set both motors off for start-up
  digitalWrite(r_motor_p, LOW);
  digitalWrite(l_motor_p, LOW);
  digitalWrite(l_motor_n, LOW);
  digitalWrite(pump_p, LOW);
  digitalWrite(pump_n, LOW);
  digitalWrite(mop_p, LOW);
  digitalWrite(mop_n, LOW);
  Serial.begin(9600);
}


void loop()
{

  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    //    Serial.println(incomingByte);
  }

  switch (incomingByte)
  {

    case 'S': // control to stop the robot
      digitalWrite(r_motor_n, LOW); //set both motors off for start-up
      digitalWrite(r_motor_p, LOW);
      digitalWrite(l_motor_p, LOW);
      digitalWrite(l_motor_n, LOW);
      digitalWrite(pump_p, LOW);
      digitalWrite(pump_n, LOW);
      digitalWrite(mop_p, LOW);
      digitalWrite(mop_n, LOW);
      Serial.println("Stop");
      incomingByte = '*';
      break;

    case 'R': //control for right
      digitalWrite(r_motor_n, HIGH);
      digitalWrite(r_motor_p, LOW);
      analogWrite(en1, speedy);
      digitalWrite(l_motor_n, LOW);
      digitalWrite(l_motor_p, HIGH);
      analogWrite(en2, speedy);
      Serial.println("right");
      incomingByte = '*';
      break;


    case 'L': //control for left
      digitalWrite(r_motor_n, LOW);
      digitalWrite(r_motor_p, HIGH);
      analogWrite(en1, speedy);
      digitalWrite(l_motor_n, HIGH);
      digitalWrite(l_motor_p, LOW);
      analogWrite(en2, speedy);
      Serial.println("left");
      incomingByte = '*';
      break;


    case 'F': //control for forward
      digitalWrite(r_motor_n, HIGH);
      digitalWrite(r_motor_p, LOW);
      analogWrite(en1, speedy);
      digitalWrite(l_motor_n, HIGH);
      digitalWrite(l_motor_p, LOW);
      analogWrite(en2, speedy);
      Serial.println("forward");
      incomingByte = '*';
      break;


    case 'B': //control for backward
      digitalWrite(r_motor_n, LOW);
      digitalWrite(r_motor_p, HIGH);
      analogWrite(en1, speedy);
      digitalWrite(l_motor_n, LOW);
      digitalWrite(l_motor_p, HIGH);
      analogWrite(en2, speedy);
      Serial.println("back");
      incomingByte = '*';
      break;


    case 'P': // pump on
      if (param_p == 1)
      {
        digitalWrite(pump_p, HIGH);
        digitalWrite(pump_n, LOW);
        analogWrite(en3, HIGH);
        Serial.println("pump on");
        incomingByte = '*';
        param_p = 2;
      }

      else if (param_p == 2)
      {
        digitalWrite(pump_p, LOW);
        digitalWrite(pump_n, LOW);
        Serial.println("pump off");
        incomingByte = '*';
        param_p = 1;
      }
      break;

    case 'M':
      if (param_m == 1)
      {
        digitalWrite(mop_p, HIGH); // mopper on
        digitalWrite(mop_n, LOW);
        analogWrite(3, speedy);
        Serial.println("mopper on");
        incomingByte = '*';
        param_m = 2;
      }

      else if (param_m == 2)
      {
        digitalWrite(mop_p, LOW);
        digitalWrite(mop_n, LOW); // mopper off
        Serial.println("mopper off");
        incomingByte = '*';
        param_m = 1;
      }
      break;

    case 'U': // roller up
      if (param_r == 1)
      {
        myServo.write(45);
        Serial.println("roller up");
        incomingByte = '*';
        param_r = 2;
      }
      else if (param_r == 2)
      {
        myServo.write(152);
        Serial.println("roller down");
        incomingByte = '*';
        param_r = 1;
      }
      break;


    case 'I':
      if (speedy <100)
        speedy = speedy + 25 ;
      Serial.print("speed= ");
      Serial.println(speedy);
      incomingByte = '*';
      analogWrite(en1, speedy);
      analogWrite(en2, speedy);
      analogWrite(3, speedy);
      break;

    case 'D':
      if (speedy > 50)
        speedy = speedy - 25 ;
      Serial.print("speed= ");
      Serial.println(speedy);
      incomingByte = '*';
      analogWrite(en1, speedy);
      analogWrite(en2, speedy);
      analogWrite(3, speedy);
      break;

      delay(10000);
  }
}
