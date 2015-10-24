/*
 * Robot program
 * done :
 *    - led
 *    - ultrasound
 *    - buzzer
 * todo :
 *    - motor (test to do)
 *    - remote
 * 
 */
#include <NewPing.h>  // Ultrasound library

#define led1Pin       11  // LEDs
#define led2Pin       12  // LEDs
#define ECHO_PIN      9   // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN   10  // Arduino pin tied to trigger pin on ping sensor.
#define buzzerPin     3   // Buzzer
#define remotePin     4   // Ir reciever
#define MOTOR_A_DIR   7   // Motor A pin 1, A-IB, DIR
#define MOTOR_A_PWM   5   // Motor A pin 2, A-IA, PWM
#define MOTOR_B_DIR   8   // Motor B pin 1, B-IB, DIR
#define MOTOR_B_PWM   6   // Motor B pin 2, B-IA, PWM

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW    100      // arbitrary slow speed PWM duty cycle
#define PWM_FAST    150     // arbitrary fast speed PWM duty cycle
#define DIR_DELAY   1000    // brief delay for abrupt motor changes

// ultrasound
#define MAX_DISTANCE 100  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int sonarDistance = 0;        // Distance of the object

int DistanceMinimum;

void setup()
{
  DistanceMinimum = 4;
  Serial.begin(9600);
  pinMode(led1Pin,OUTPUT);          // Led output
  pinMode(led2Pin,OUTPUT);          // Led output
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  stop();
  digitalWrite(led1Pin, HIGH);    
  digitalWrite(led2Pin, HIGH);    
  delay(500);           
  digitalWrite(led1Pin, LOW);   
  digitalWrite(led2Pin, LOW);    
}


void loop()
{
  // Check ultrasound
  int sonarDistanceTemp = sonar.ping_cm();
  if ( sonarDistanceTemp==0) sonarDistance = MAX_DISTANCE;  // Send ping, get distance in cm
  else sonarDistance = sonarDistanceTemp;
  
  Serial.print("Ping: ");
  Serial.print(sonarDistance);
  Serial.println("cm");
  
  if (sonarDistance<10) {
    stop();
    delay(500);
    backward(PWM_SLOW);
    delay(500);
    right(PWM_SLOW);
    delay(500);

  } else {
    forward(PWM_FAST);
  }
}

void forward(int speed)
{
  analogWrite(MOTOR_A_PWM,speed);//input a simulation value to set the speed
  analogWrite(MOTOR_B_PWM,speed);
  digitalWrite(MOTOR_A_DIR,HIGH);//turn DC Motor B move clockwise
  digitalWrite(MOTOR_B_DIR,HIGH);//turn DC Motor A move clockwise
  digitalWrite(led1Pin, HIGH);    
  digitalWrite(led2Pin, HIGH);
}

void right(int speed)
{
  analogWrite(MOTOR_A_PWM,speed);//input a simulation value to set the speed
  analogWrite(MOTOR_B_PWM,speed);
  digitalWrite(MOTOR_A_DIR,HIGH);//turn DC Motor B move clockwise
  digitalWrite(MOTOR_B_DIR,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(led1Pin, HIGH);   
  digitalWrite(led2Pin, LOW);    
}

void left(int speed)
{
  analogWrite(MOTOR_A_PWM,speed);//input a simulation value to set the speed
  analogWrite(MOTOR_B_PWM,speed);
  digitalWrite(MOTOR_A_DIR,LOW);//turn DC Motor B move clockwise
  digitalWrite(MOTOR_B_DIR,HIGH);//turn DC Motor A move anticlockwise
  digitalWrite(led2Pin, HIGH);
  digitalWrite(led1Pin, LOW); 
}

void backward(int speed)
{
  analogWrite(MOTOR_A_PWM,speed);//input a simulation value to set the speed
  analogWrite(MOTOR_B_PWM,speed);
  digitalWrite(MOTOR_A_DIR,LOW);//turn DC Motor B move anticlockwise
  digitalWrite(MOTOR_B_DIR,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(led1Pin, LOW);   
  digitalWrite(led2Pin, LOW); 
}

void stop()
{
  digitalWrite(MOTOR_A_PWM,LOW);// Unenble the pin, to stop the motor. this should be done to avid damaging the motor.
  digitalWrite(MOTOR_B_PWM,LOW);
  digitalWrite(MOTOR_A_DIR,LOW);//turn DC Motor B move clockwise
  digitalWrite(MOTOR_B_DIR,LOW);//turn DC Motor A move clockwise
  digitalWrite(led1Pin, LOW);   
  digitalWrite(led2Pin, LOW); 
}
