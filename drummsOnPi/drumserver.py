from __future__ import print_function
from Adafruit_PWM_Servo_Driver import PWM

from time import sleep
import argparse
import math
import sys

from liblo import *

# ininitalize PWM device driver for shield
pwm = PWM(0x40)

pwmMin = 0
pwmMax = 4000

# raw_input renamed to input in python3
try:
    input = raw_input
except NameError:
    pass

class MyServer(ServerThread):
    def __init__(self):
        ServerThread.__init__(self, 1234)

    @make_method('/foo', 'ii')
    def foo_callback(self, path, args):
        pwm.setPWM(args[0], 0, args[1])  # 0 to 15 on my board for args[0], and args[1] 0 to 4096
        sleep(0.03) # best minimum that worked for me, you might want to play with this
        pwm.setPWM(args[0], 0, 0)
        print("received message '%s' with arguments: %d, %d" % (path, args[0], args[1]))

    @make_method(None, None)
    def fallback(self, path, args):
        print("received unknown message '%s'" % path)

try:
    server = MyServer()
except ServerError as err:
    print(err)
    sys.exit()

server.start()
input("press enter to quit...\n")
