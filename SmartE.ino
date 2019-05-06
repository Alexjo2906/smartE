/*      Control SmartE from Pi, activated by push button
              Written by: tenaciousLogan         
         Proyecto de Grado de Ing. Mecatronica          */

////////////////////  Import libraries ////////////////////

#include <Servo.h>

////////////////////   Declare pins    ////////////////////

// int lmtPos = 4;
int lmtAli = 4;
int servPos = 9;
int servAli = 10;

//////////////////// Declare variables ////////////////////

Servo myServo;  // create servo object to control a servo

int btnState = 0;  //Initializes a variable for storing the button state
int inState = 0;  //Initializes a variable for storing the incoming data from Arduino

int posServPos = 0;    // variable to store the servo position
int posServAli = 0;    // variable to store the servo position

//////////////////// Declare functions ////////////////////

int serialCom();
int ardMenu(int instate);

int rstServPos();
int rstServAli();

int movServPos(int posServPos);
int movServAli(int posServAli);

void printState();

//////////////////////////////    SETUP   /////////////////////////////////////////////

void setup() {
  // No interrupt line ???
  
  Serial.begin(9600);  //Started the serial communication at 9600 baudrate
  
  myServo.attach(servPos);  // attaches the servo on the pin stated to the servo object
  myServo.attach(servAli);  // attaches the servo on the pin stated to the servo object
  
  pinMode(lmtAli, INPUT); // Limit switch for position 0
}

//////////////////////////////    LOOP   /////////////////////////////////////////////

void loop() {
  // serialCom();
 // ardMenu(int inState);
  Serial.println("Started process..");
  rstServPos();
  movServAli(posServPos);
}

////////////////////////////    Functions   ///////////////////////////////////////////

int rstServPos(){
  int lmtPos = 0;
  do{
    for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      // Serial.println("Waiting for Limit Switch...");
      lmtPos = digitalRead(4);
      myServo.write(servAli);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("Waiting for Limit Switch...");
    Serial.println(lmtPos);
  }
  while (lmtPos = 0);
  return (posServAli = 0);
}

int movServAli(int maxPos){
    for (int pos = 0; pos <= maxPos; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(servAli);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (int pos = maxPos; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myServo.write(servAli);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    // Serial.println(1);  //Sending the data over serial to Raspberry pi
    Serial.println("Moving Servo...");
}

int serialCom(){
  if (Serial.available() > 0){  //Looking for incoming data
    inState = Serial.read() - '0';  //Reading the data
  }
  return inState;
}

int ardMenu(int inState){
  switch (inState)
  {
    case 0:
      /* code */
      break;
    case 1:
      int posServPos = rstServPos();
      if (posServPos = 0) {
        int maxPos = 90;
        movServPos(maxPos);
      
      }
      break;
    default:
      Serial.print("Incoming state is false");
      break;
  }
  return 0;
}

/*
int movServPos(int maxPos){
  
  for (int pos = 0; pos <= maxPos; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(servPos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (int pos = maxPos; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myServo.write(servPos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println(1);  //Sending the data over serial to Raspberry pi
}
*/
