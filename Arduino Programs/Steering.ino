
int feedbackPin = A0, inputPin = A2; //Connect the feedback pot to A0 on the Teensy and the steering pot to A2
int PWMPin = 10, DIRPin=3; //Connect the PWM input of the H-bridge to pin 10 on the Teensy and the Direction input to pin 3    
int feedback, velocity, angle, steer, input;
int offset=25; //The offset sets a starting duty cycle to make the big motors more responsive
int tolerance=8; //Tolerance gives a little bit of play in the pot before the motor starts trying to correct
int rate=1.2 ;  //The rate is the ratio between the error and motor speed

void setup() {
  Joystick.useManualSend(true);
  pinMode(PWMPin, OUTPUT); 
 pinMode(DIRPin, OUTPUT); 
 pinMode(0,INPUT_PULLUP);
  byte mask = B11111000;
  TCCR4B &= mask; //Sets the timing registor to 11111000
  TCCR4B |= (0<<CS42) | (1<<CS41) | (0<<CS40); //This sets the PWM frequency by setting the prescaler for the peripheral clock. 001 = 31.2KHz, 010 = 15.6KHz, 011 = 7.8KHz, 101 = 3.9KHz
}
byte buffer[2]={128,128}; //Initialises a buffer to store the received bytes in
void servo(int input); //This function will be a basic servo function which will allow the motor to position itself

void loop() {

    RawHID.recv(buffer, 0); //Receives a packet from the PC abnd puts it into the buffer
   input = buffer[0]; //The first byte in the array contains the roll data 
   servo(input); //Sets the position of the motor to the given angle
   Joystick.X( 8*(analogRead(inputPin)-700)); //Sets the joystick's X-axis to the value of the steering pot (amplified because of the way I had it set up, should have really used a map)
   Joystick.button(1, !digitalRead(0)); //The throttle switch is connected to pin0 and maps to the joystick button 1
   Joystick.send_now(); //Sends the joystick data
}

void servo(int input){
  
  do{
     feedback = map(analogRead(feedbackPin), 0, 1023, 0, 255);//Maps the 10bit analogue input to an 8bit number for comparison with the data byte. The first range can be edited depending on the required output angle, at the moment it's the full travel of the pot.
          if(input > feedback + tolerance){ 
            velocity = offset+(rate*(input-feedback));
            digitalWrite(DIRPin, HIGH);
              if (velocity > 254){
                  velocity = 255;
              }
            analogWrite(PWMPin, velocity);  
          }
 
         else if(input < feedback- tolerance){
           velocity = offset+(rate*(feedback-input));
          digitalWrite(DIRPin, LOW);
           if (velocity > 254){
                velocity = 255;
          }
          analogWrite(PWMPin, velocity);  
         } 
         else{
          digitalWrite(DIRPin, LOW);
          analogWrite(PWMPin, 0);
         }
   }
  while(input > feedback+tolerance || input < feedback-tolerance ); //Keeps looping until the motor is close enough to the required position that it sits inside the tolerance band
  digitalWrite(DIRPin, LOW);
  analogWrite(PWMPin, 0);

}
