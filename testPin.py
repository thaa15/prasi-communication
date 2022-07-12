#!/usr/bin/python3

import RPi.GPIO as GPIO
import signal
import sys
import time

def signal_handler(sig, frame):
    GPIO.cleanup()
    sys.exit(0)

if __name__ == "__main__":
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(6,GPIO.IN)
    testing_pin = GPIO.input(6)
    signal.signal(signal.SIGINT,signal_handler)
    while True:
        print(testing_pin)
        time.sleep(1)
