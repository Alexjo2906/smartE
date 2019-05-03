###################    Control SmartE from Pi, activated by push button    ###################
###################               Written by: tenaciousLogan               ###################
###################          Proyecto de Grado de Ing. Mecatronica         ###################

########## Import libraries ##########

import serial  # Importing the serial library to communicate with Arduino
import RPi.GPIO as GPIO # Importing the GPIO library to use the GPIO pins of Raspberry pi

from time import sleep # Importing the time library to provide the delays in program

########## Declare pins ##########
redstsLed = # Red Status Led
bluestsLed = # Blue (Yellow) Status Led
greenstsLed = # Green Status Led

coil_A_1_pin = 17 # pink
coil_A_2_pin = 9 # orange
coil_B_1_pin = 4 # blue
coil_B_2_pin = 22 # yellow

pinBomba = 14
pinValvAgua = 18

########## Declare GPIO ##########

GPIO.setmode(GPIO.BCM) # Using BCM numbering (GPIO)
GPIO.setup(redLed, GPIO.OUT) # Declaring the led pin as output pin

GPIO.setup(coil_A_1_pin, GPIO.OUT)
GPIO.setup(coil_A_2_pin, GPIO.OUT)
GPIO.setup(coil_B_1_pin, GPIO.OUT)
GPIO.setup(coil_B_2_pin, GPIO.OUT)

GPIO.setup(pinValvAgua, GPIO.OUT)
GPIO.setup(pinBomba, GPIO.OUT)

########## Declare global variables ##########

incoming_data = 0

StepCount = 8 # adjust if different
Seq = range(0, StepCount)
Seq[0] = [0,1,0,0]
Seq[1] = [0,1,0,1]
Seq[2] = [0,0,0,1]
Seq[3] = [1,0,0,1]
Seq[4] = [1,0,0,0]
Seq[5] = [1,0,1,0]
Seq[6] = [0,0,1,0]
Seq[7] = [0,1,1,0]

# Defined the port and the baudrate at which we will communicate with Arduino.
ser = serial.Serial('/dev/ttyACM1', 9600)

########## Define functions ##########

##### Arduino communication functions ######
# 0 => verPosVasos (verify mechanism of positioning the cups)
# 1 => verAliVasos (verify mechanism of feeding the cups)

def comPi2Ard(numFunc):
    try:
        ser.write('numFunc') # Sending data to the Arduino
        incoming_data = ser.read() # Reading and storing the data coming from Arduino
        while (incoming_data = 0):
            # Indicate error in communication w/ Arduino
            GPIO.output(redLed, 1) 
            sleep(1)
            GPIO.output(redLed, 0) 
            sleep(1)
        return

    except KeyboardInterrupt:
        GPIO.cleanup()

#### MiniStepper Functions ###

def setStep(w1, w2, w3, w4):
    GPIO.output(coil_A_1_pin, w1)
    GPIO.output(coil_A_2_pin, w2)
    GPIO.output(coil_B_1_pin, w3)
    GPIO.output(coil_B_2_pin, w4)

def forward(delay, steps):
    for i in range(steps):
        for j in range(StepCount):
            setStep(Seq[j][0], Seq[j][1], Seq[j][2], Seq[j][3])
            sleep(delay)

def backwards(delay, steps):
    for i in range(steps):
        for j in reversed(range(StepCount)):
            setStep(Seq[j][0], Seq[j][1], Seq[j][2], Seq[j][3])
            sleep(delay)

### Ctrl Relays ###

def tryRelay(Pin):
    while True:
        GPIO.output(pinGPIO, GPIO.HIGH)
        sleep(3) #waiting time in seconds
        GPIO.output(pinGPIO, GPIO.LOW)
        sleep(3)

########## Infinite loop (Main) ##########

while True: 
    try:
        GPIO.output(redstsLed, 1) # Indicate SmartE is powered
        comPi2Ard(0) # verify posVasos
        sleep(1.5) # Pause
        comPi2Ard(1) # verify aliVasos
        GPIO.output(redstsLed, 1) # Indicate SmartE has passed the arduino tests 
        sleep(3) # Sleep to indicate the result from above

        GPIO.output(redstsLed, 0) # Indicate SmartE is still running tests
        delay = 1 # Controls how fast it goes
        steps = 1000 # Controls the revolutions
        forward(int(delay) / 1000.0, int(steps))
        GPIO.output(redstsLed, 1) # Indicate SmartE has passed the mech test
        sleep(3) # Sleep to indicate the result from above

        GPIO.output(redstsLed, 0) # Indicate SmartE is still running tests
        tryRelay(pinValvAgua)
        GPIO.output(redstsLed, 1) # Indicate SmartE has passed the first water test 
        sleep(1.5) # Sleep to indicate the result from above

        tryRelay(pinBomba)
        GPIO.output(redstsLed, 0) # Indicate SmartE has passed the second water test
        sleep(1.5) # Sleep to indicate the result from above
        GPIO.output(redstsLed, 1) # Indicate SmartE has passed the tests
        sleep(3) # Sleep to indicate the result from above

    except KeyboardInterrupt:
        GPIO.cleanup() # Turn off all outputs
        return

    else:
        GPIO.output(redstsLed, 0)
        sleep(0.5)
        ### Three blinks to indicate SmartE is ready to operate ###
        for x in range (2): 
            GPIO.output(redstsLed, 1)
            sleep(0.5)
            GPIO.output(redstsLed, 0)
            sleep(0.5)
        else:
            GPIO.output(bluestsLed, 1) # Indicate SmartE has passed all the tests (Awaiting instructions)
        return