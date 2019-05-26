/* Simple Stepper Motor Homing code
 
Created by Yvan / https://Brainy-Bits.com
This code is in the public domain...
You can: copy it, use it, modify it, share it or just plain ignore it!
Thx!

*/

// Define the Pins used
#define step_pin 9    // Pin 5 connected to Steps pin on EasyDriver

#define home_switch 4 // Pin 9 connected to Home Switch (MicroSwitch)

int direction;    // Variable to set Rotation (CW-CCW) of the motor
int steps;        // Used to set HOME position after Homing is completed

void setup() {
   pinMode(step_pin, OUTPUT);
   pinMode(home_switch, INPUT_PULLUP);
   
// Start Homing procedure of Stepper Motor at startup

  while (digitalRead(home_switch)) {  // Do this until the switch is activated   
    digitalWrite(dir_pin, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(step_pin, HIGH);
    delay(5);                       // Delay to slow down speed of Stepper
    digitalWrite(step_pin, LOW);
    delay(5);   
}

  while (!digitalRead(home_switch)) { // Do this until the switch is not activated
    digitalWrite(dir_pin, LOW); 
    digitalWrite(step_pin, HIGH);
    delay(10);                       // More delay to slow even more while moving away from switch
    digitalWrite(step_pin, LOW);
    delay(10);
  }

  steps=0;  // Reset position variable to zero
   
}

void loop() {

// Enable movement of Stepper Motor using the Joystick

  while (analogRead(x_pin) >= 0 && analogRead(x_pin) <= 100) {
    if (steps > 0) {  //  To make sure the Stepper doesn't go beyond the Home Position
      //digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      delay(1);
      digitalWrite(step_pin, LOW);
      delay(1);
      steps--;   // Decrease the number of steps taken
    }      
  }
   
    while (analogRead(x_pin) > 900 && analogRead(x_pin) <= 1024) {
      if (steps < 650) {      // Maximum steps the stepper can move away from the Home Position
        digitalWrite(dir_pin, LOW);
        digitalWrite(step_pin, HIGH);
        delay(1);
         digitalWrite(step_pin, LOW);
        delay(1);
        steps++;  // Increase the number of steps taken
      }
    }
}
