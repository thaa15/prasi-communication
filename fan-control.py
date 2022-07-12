#!/usr/bin/python3

import RPi.GPIO as GPIO
import signal
import sys
import time
import re,subprocess

fan_pin = 17

def get_temperature():
    temp = 0
    e,msg = subprocess.getstatusoutput('vcgencmd measure_temp')
    if not e:
        temp = float(re.search(r'-?\d\.?\d*',msg).group())
    return temp

def signal_handler(sig,frame):
    GPIO.cleanup()
    sys.exit(0)

if __name__ == "__main__":
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(fan_pin, GPIO.OUT)
    signal.signal(signal.SIGINT,signal_handler)
    while True:
        temperature=get_temperature()
        if temperature > 52:
            GPIO.output(fan_pin, GPIO.HIGH)
        else:
            GPIO.output(fan_pin, GPIO.LOW)
        time.sleep(0.2)
