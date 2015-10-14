/*
 * Robot program
 * done :
 *    - led
 *    - ultrasound
 *    - buzzer
 * todo :
 *    - motor
 *    - remote
 * 
 */
#include <NewPing.h>  // Ultrasound library
#include "pitches.h"  // Sound

#define led1Pin       2   // LEDs
#define led2Pin       2   // LEDs
#define buzzerPin     5   // Buzzer

#define TRIGGER_PIN   4   // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      3   // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 100  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// ultrasound
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.
int sonarDistance = 0;        // Distance of the object

// Sound
const int threshold = 0;    // minimum reading of the sensors that generates a note
// notes to play, corresponding to the 3 sensors:
int notes[] = {
  NOTE_A4, NOTE_B4, NOTE_C3
};

void setup()
{
  Serial.begin(9600);               // Initialise Serial comm
  pingTimer = millis();             // Start now the ultrasound
  pinMode(led1Pin,OUTPUT);          // Led output
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
  }
  else {
    digitalWrite(led1Pin, LOW);    // turn the LED off if more than 10cm
  }
  // map the distance range 
  // to the output pitch range (120 - 1500Hz)
  int thisPitch = map(sonarDistance, MAX_DISTANCE, 1, 120, 1500);
  // play the note corresponding to this distance:
  tone(buzzerPin, thisPitch);
  
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
}
