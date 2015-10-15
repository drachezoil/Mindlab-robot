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

#define led1Pin       2   // LEDs
#define led2Pin       3   // LEDs
#define ECHO_PIN      4   // Arduino pin tied to echo pin on ping sensor.
#define TRIGGER_PIN   5   // Arduino pin tied to trigger pin on ping sensor.
#define buzzerPin     6   // Buzzer
#define remotePin     7   // Ir reciever
#define MOTOR_A_DIR   8   // Motor A pin 1, A-IB, DIR
#define MOTOR_A_PWM   9   // Motor A pin 2, A-IA, PWM
#define MOTOR_B_DIR   10  // Motor B pin 1, B-IB, DIR
#define MOTOR_B_PWM   11  // Motor B pin 2, B-IA, PWM
 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW    50      // arbitrary slow speed PWM duty cycle
#define PWM_FAST    200     // arbitrary fast speed PWM duty cycle
#define DIR_DELAY   1000    // brief delay for abrupt motor changes
#define MOTOR_LEFT  MOTOR_A_DIR // easy remeider
#define MOTOR_RIGHT MOTOR_B_DIR // easy remeider
#define MOTOR_FORWARD 1     // easy remeider
#define MOTOR_REVERSE 0     // easy remeider

// ultrasound
#define MAX_DISTANCE 100  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int sonarDistance = 0;        // Distance of the object

void setup()
{
  Serial.begin(9600);               // Initialise Serial comm
  pinMode(led1Pin,OUTPUT);          // Led output
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  digitalWrite(led1Pin, HIGH);    
  delay(500);                     
  digitalWrite(led1Pin, LOW); 
  delay(500);                   
  digitalWrite(led1Pin, HIGH);  
  delay(500);                    
  digitalWrite(led1Pin, LOW);   
}

void loop()
{
  // Check ultrasound
  int sonarDistanceTemp = sonar.ping_cm();
  if ( sonarDistanceTemp!=0) sonarDistance = sonarDistanceTemp;  // Send ping, get distance in cm

  Serial.print("Ping: ");
  Serial.print(sonarDistance);
  Serial.println("cm");
  if (sonarDistance<10){
    digitalWrite(led1Pin, HIGH);    // turn the LED on if less than 10cm
    motor (MOTOR_LEFT, MOTOR_REVERSE, PWM_SLOW);  // go back
    motor (MOTOR_RIGHT, MOTOR_REVERSE, PWM_SLOW);
    delay(500);                     // go back during 1s
    motor (MOTOR_LEFT, MOTOR_FORWARD, PWM_SLOW);  // turn
    motor (MOTOR_RIGHT, MOTOR_REVERSE, PWM_SLOW);
    delay(100);                     // half turn
  }
  else {
    digitalWrite(led1Pin, LOW);    // turn the LED off if more than 10cm
    motor (MOTOR_LEFT, MOTOR_FORWARD, PWM_FAST);
    motor (MOTOR_RIGHT, MOTOR_FORWARD, PWM_FAST);
  }
  // map the distance range 
  // to the output pitch range (120 - 1500Hz)
  int thisPitch = map(sonarDistance, MAX_DISTANCE, 1, 120, 1500);
  // play the note corresponding to this distance:
  //tone(buzzerPin, thisPitch);
  
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
}

void motor (int motorName, int motorDir, int motorSpeed) {
  // always stop motors briefly before abrupt changes
  digitalWrite( motorName, LOW );
  digitalWrite( motorName+1, LOW );
  delay( DIR_DELAY );
  
  if (motorDir){  // direction = forward
    // set the motor speed and direction
    digitalWrite( motorName, HIGH ); // direction = forward
    analogWrite( motorName+1, 255-motorSpeed ); // PWM speed
  }
  else{  // direction = reverse
    // set the motor speed and direction
    digitalWrite( motorName, LOW ); // direction = reverse
    analogWrite( motorName+1, 255-motorSpeed ); // PWM speed
  }
}



