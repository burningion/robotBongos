from __future__ import print_function

from time import sleep
import argparse
import math
import sys
import wiringpi2

from liblo import *

# ininitalize PWM device driver for shield

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
        wiringpi2.digitalWrite(args[0],1)
        #sleep(0.03)
        scaled = args[1] / 127.0
        wiringpi2.delay(int(scaled*15 + 4)) # five is min, max is uhhh 20 ish?
        wiringpi2.digitalWrite(args[0],0)
        print("received message '%s' with arguments: %d, %d" % (path, args[0], args[1]))

    @make_method(None, None)
    def fallback(self, path, args):
        print("received unknown message '%s'" % path)

try:
    server = MyServer()
except ServerError as err:
    print(err)
    sys.exit()

wiringpi2.wiringPiSetup()
wiringpi2.pinMode(1,1)
wiringpi2.pinMode(2,1)
wiringpi2.pinMode(3,1)
wiringpi2.pinMode(4,1)
wiringpi2.pinMode(5,1)

server.start()
input("press enter to quit...\n")
