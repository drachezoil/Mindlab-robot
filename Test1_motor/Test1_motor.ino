#define led1Pin       11  // LEDs
#define led2Pin       12  // LEDs
#define ECHO_PIN      7   // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN   8   // Arduino pin tied to trigger pin on ping sensor.
#define buzzerPin     3   // Buzzer
#define remotePin     4   // Ir reciever
#define MOTOR_A_B     9   // Motor A pin 1, A-IB, DIR
#define MOTOR_A_A     5   // Motor A pin 2, A-IA, PWM
#define MOTOR_B_B     10  // Motor B pin 1, B-IB, DIR
#define MOTOR_B_A     6   // Motor B pin 2, B-IA, PWM

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW    100      // arbitrary slow speed PWM duty cycle
#define PWM_FAST    150     // arbitrary fast speed PWM duty cycle
#define DIR_DELAY   1000    // brief delay for abrupt motor changes

int first;


void setup()
{
  first = 1;
 Serial.begin(9600);
  pinMode(led1Pin,OUTPUT);          // Led output
  pinMode(led2Pin,OUTPUT);          // Led output
  pinMode( MOTOR_A_A, OUTPUT );
  pinMode( MOTOR_A_B, OUTPUT );
  pinMode( MOTOR_B_A, OUTPUT );
  pinMode( MOTOR_B_B, OUTPUT );
  stop();
  digitalWrite(led1Pin, HIGH);    
  digitalWrite(led2Pin, HIGH);    
  delay(500);           
  digitalWrite(led1Pin, LOW);   
  digitalWrite(led2Pin, LOW);    
}


void loop()
{
  /*if (first == 1) {
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
  }*/
  for(int i = 0; i<250 ; i=i+10){
    forward(i);
    Serial.print("speed: ");
    Serial.println(i);
    delay(1000);
    
  }
}

void forward(int speed)
{
  digitalWrite(MOTOR_A_A,LOW);
  digitalWrite(MOTOR_B_A,LOW);
  analogWrite(MOTOR_A_B,speed);
  analogWrite(MOTOR_B_B,speed);
  digitalWrite(led1Pin, HIGH);    
  digitalWrite(led2Pin, HIGH);
}

void right(int speed)
{
  analogWrite(MOTOR_A_A,speed);
  digitalWrite(MOTOR_B_A,LOW);
  digitalWrite(MOTOR_A_B,LOW);
  analogWrite(MOTOR_B_B,speed);
  digitalWrite(led1Pin, HIGH);   
  digitalWrite(led2Pin, LOW);    
}

void left(int speed)
{
  digitalWrite(MOTOR_A_A,LOW);
  analogWrite(MOTOR_B_A,speed);
  analogWrite(MOTOR_A_B,speed);
  digitalWrite(MOTOR_B_B,LOW);
  digitalWrite(led2Pin, HIGH);
  digitalWrite(led1Pin, LOW); 
}

void backward(int speed)
{
  analogWrite(MOTOR_A_A,speed);
  analogWrite(MOTOR_B_A,speed);
  digitalWrite(MOTOR_A_B,LOW);
  digitalWrite(MOTOR_B_B,LOW);
  digitalWrite(led1Pin, LOW);   
  digitalWrite(led2Pin, LOW); 
}

void stop()
{
  digitalWrite(MOTOR_A_A,LOW);
  digitalWrite(MOTOR_B_A,LOW);
  digitalWrite(MOTOR_A_B,LOW);
  digitalWrite(MOTOR_B_B,LOW);
  digitalWrite(led1Pin, LOW);   
  digitalWrite(led2Pin, LOW); 
}
