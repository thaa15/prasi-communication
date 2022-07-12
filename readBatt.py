#!/usr/bin/python3

import RPi.GPIO as GPIO
import signal
import sys
import time
import re,subprocess
import smbus
import datetime
import tkinter as tk

address = 0x3c
ADC_Add_1 = 0x14
ADC_Add_2 = 0x15
mywindow = tk.Tk()

class SWBATT:
    def __init__(self, addr, i2c_bus=1):
        self.bus = smbus.SMBus(i2c_bus)
        self.addr = addr

    def readBattery(self,ADC1,ADC2):
        r14 = self.bus.read_byte_data(self.addr,ADC1)
        r15 = self.bus.read_byte_data(self.addr,ADC2)
        vbat = (((r15 << 8) | r14) & 0xFFF)*0.0012
        print(round(vbat,2), end = ' ')

    def readPercentage(self, addres):
        r4f = self.bus.read_byte_data(self.addr,addres)
        r4f = (r4f & 0xFFF)
        print(str(r4f)+"%")

    def readVoltage(self):
        pass

def signal_handler(sig,frame):
    sys.exit(0)

def exit():
    quit()

if __name__ == "__main__":
    GPIO.setmode(GPIO.BCM)
    swBatt = SWBATT(addr=address)
    signal.signal(signal.SIGINT,signal_handler)
    while True:
        swBatt.readBattery(ADC_Add_1,ADC_Add_2)
        #date = datetime.datetime.now().strftime('%H.%M.%S')
        swBatt.readPercentage(0x4F)
        time.sleep(20)
