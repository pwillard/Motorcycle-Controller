#include <Servo.h>
int roll_angle, pitch_angle;
Servo roll_motor, pitch_motor; //Sets up to servo objects
const int rollMotorPin = 1; //Attatch the signal pin of your roll servo to pin 1 on the Teensy
const int pitchMotorPin = 2; //Attatch the signal pin of your pitch servo to pin 2 on the Teensy


void setup() {
 roll_motor.attach(rollMotorPin); 
  pitch_motor.attach(pitchMotorPin);
 //Attatches the servo objects to their corresponding pins
}
byte buffer[2]; //Creates a buffer into which the Raw data is held


void loop() {

RawHID.recv(buffer, 0); //Receives a packet of data and puts it into the buffer array with no delay

roll_angle = 0.711*buffer[0];
roll_motor.write(roll_angle);

pitch_angle = 0.711*buffer[1]; 
pitch_motor.write(180-pitch_angle);

//Each 8-bit number is converted into an angle and then written straight to the servos
}

