#include <IRLib.h>

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

#define UP    FF629D
#define DOWN  FFA857
#define RIGHT FFC23D
#define LEFT  FF22DD
#define OK    FF02FD
#define 1     FF6897
#define 2     FF9867
#define 3     FFB04F
#define 4     FF30CF
#define 5     FF18E7
#define 6     FF7A85
#define 7     FF10EF
#define 8     FF38C7
#define 9     FF5AA5
#define 0     FF4AB5
#define STAR  FF42BD
#define HASH  FF52AD

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW    80      // arbitrary slow speed PWM duty cycle
#define PWM_FAST    150     // arbitrary fast speed PWM duty cycle

//Create a receiver object to listen on pin 11
IRrecv My_Receiver(remotePin);
 
//Create a decoder object
IRdecode My_Decoder;

void setup()
{
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
 //Continuously look for results. When you have them pass them to the decoder
  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();   //Decode the data
    My_Decoder.DumpResults(); //Show the results on serial monitor
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
