#Import the necessary libraries
import RPi.GPIO as GPIO
import time

pinGPIO = 14
# bomba 14
# valAgua 18

GPIO.setmode(GPIO.BCM)

#Setup pin 18 as an output
GPIO.setmode(GPIO.BCM)
GPIO.setup(pinGPIO, GPIO.OUT)

#This function turns the valve on and off in 10 sec. intervals. 
def valve_OnOff(Pin):
    while True:
        GPIO.output(pinGPIO, GPIO.HIGH)
        print("GPIO HIGH (on), valve should be off") 
        time.sleep(3) #waiting time in seconds
        GPIO.output(pinGPIO, GPIO.LOW)
        print("GPIO LOW (off), valve should be on")
        time.sleep(3)

valve_OnOff(pinGPIO)
GPIO.cleanup()

