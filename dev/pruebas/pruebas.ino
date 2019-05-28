
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int maxPos = 45;

int rStat = 5; //Initializing pin 8 of Arduino as the led pin
int gStat = 6;
int bStat = 7;

// int button_pin = 7;  //Initializing pin 7 of Arduino as the button pin
// int button_state = 0;  //Initializes a variable for storing the button state
int incoming_state = 0;  //Initializes a variable for storing the incoming data from Arduino

void posVasos();

void setup(){
  pinMode(rStat, OUTPUT); //Declaring led pin as output pin
  // pinMode(button_pin, INPUT); //Declaring button pin as the input pin.

  myservo.attach(10);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);  //Started the serial communication at 9600 baudrate
}

void loop(){
  digitalWrite(rStat, 1);
  digitalWrite(gStat, 1);
  digitalWrite(bStat, 1);
  
  if (Serial.available() > 0){  //Looking for incoming data
    incoming_state = Serial.read() - '0';  //Reading the data
    if (incoming_state > 0){ 
      digitalWrite(rStat, 0);  //Making the LED light up or down
      delay (1000);
      posVasos();
    }
  }

  // button_state = digitalRead(button_pin); //Reading the button state
  // Serial.println(button_state);  //Sending the data over serial to Raspberry pi
  // Serial.flush();
}

void posVasos() {
  // Calibration
  for (pos = 0; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
delay (1000);
  
  for (pos = 180; pos >= 25; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
  delay(3000);
  for (pos = 25; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
  delay(3000);
 

  for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
  delay(10000);
 
  for (pos = 90; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(60);                       // waits 15ms for the servo to reach the position
  }
  delay(10000);
}
