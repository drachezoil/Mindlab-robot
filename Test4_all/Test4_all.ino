/*
 * Robot program
 * done :
 *    - led
 *    - ultrasound
 *    - //buzzer
 *    - motor (test to do)
 *    - remote
 * 
 */
#include <IRLib.h>
#include <NewPing.h>  // Ultrasound library

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

#define UP    0xFF629D
#define DOWN  0xFFA857
#define RIGHT 0xFFC23D
#define LEFT  0xFF22DD
#define OK    0xFF02FD
#define NUM_1 0xFF6897
#define NUM_2 0xFF9867
#define NUM_3 0xFFB04F
#define NUM_4 0xFF30CF
#define NUM_5 0xFF18E7
#define NUM_6 0xFF7A85
#define NUM_7 0xFF10EF
#define NUM_8 0xFF38C7
#define NUM_9 0xFF5AA5
#define NUM_0 0xFF4AB5
#define STAR  0xFF42BD
#define HASH  0xFF52AD

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW    80      // arbitrary slow speed PWM duty cycle
#define PWM_FAST    150     // arbitrary fast speed PWM duty cycle

//Create a receiver object to listen on pin 11
IRrecv My_Receiver(remotePin);
//Create a decoder object
IRdecode My_Decoder;

// ultrasound
#define MAX_DISTANCE 100  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int sonarDistance = 0;        // Distance of the object

int DistanceMinimum;

void setup()
{
  DistanceMinimum = 4;
  Serial.begin(9600);
  My_Receiver.enableIRIn(); // Start the receiver
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
  // Check ultrasound
  int sonarDistanceTemp = sonar.ping_cm();
  if ( sonarDistanceTemp==0) sonarDistance = MAX_DISTANCE;  // Send ping, get distance in cm
  else sonarDistance = sonarDistanceTemp;
  
  Serial.print("Ping: ");
  Serial.print(sonarDistance);
  Serial.println("cm");
  
  if (sonarDistance<10) {
    stop();
    delay(100);
    backward(PWM_SLOW);
    delay(500);
    stop();
    delay(100);
    right(PWM_SLOW);
    delay(500);
    stop();
    delay(100);
  }
  
 if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();   //Decode the data
    switch(My_Decoder.value) {
        case UP: 
          forward(PWM_SLOW);
          break;
        case DOWN:  
          backward(PWM_SLOW);
          break;
        case RIGHT: 
          right(PWM_SLOW);
          break;
        case LEFT: 
          left(PWM_SLOW);
          break;
        case OK: 
          stop();
          break;
      }
    My_Receiver.resume();     //Restart the receiver
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
