int first;

void forward()
{
  analogWrite(5,127);//input a simulation value to set the speed
  analogWrite(6,127);
  digitalWrite(7,HIGH);//turn DC Motor B move clockwise
  digitalWrite(8,HIGH);//turn DC Motor A move clockwise
}

void right()
{
  analogWrite(5,127);//input a simulation value to set the speed
  analogWrite(6,127);
  digitalWrite(7,HIGH);//turn DC Motor B move clockwise
  digitalWrite(8,LOW);//turn DC Motor A move anticlockwise
}

void left()
{
  analogWrite(5,127);//input a simulation value to set the speed
  analogWrite(6,127);
  digitalWrite(7,LOW);//turn DC Motor B move clockwise
  digitalWrite(8,HIGH);//turn DC Motor A move anticlockwise
}

void backward()
{
  analogWrite(5,127);//input a simulation value to set the speed
  analogWrite(6,127);
  digitalWrite(7,LOW);//turn DC Motor B move anticlockwise
  digitalWrite(8,LOW);//turn DC Motor A move anticlockwise
}

void stop()
{
  digitalWrite(5,LOW);// Unenble the pin, to stop the motor. this should be done to avid damaging the motor.
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);//turn DC Motor B move clockwise
  digitalWrite(8,LOW);//turn DC Motor A move clockwise
  delay(1000);
}

void setup()
{
  first = 1;
  pinMode(7,OUTPUT);//I2
  pinMode(5,OUTPUT);//speedPinA
  pinMode(8,OUTPUT);//i4
  pinMode(6,OUTPUT);//speedPinB
}


void loop()
{
  if (first == 1) {
    first = 0;
    delay(1000);
    forward();
    delay(1000);
    right();
    delay(1000);
    left();
    delay(1000);
    backward();
    delay(1000);
    stop();
  }
}
