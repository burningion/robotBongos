import liblo  # OSC output
import sys

import rtmidi_python as rtmidi # midi input

target = liblo.Address("192.168.1.130", 1234) # the raspberry pi server

def callback(message, time_stamp):
    print message, time_stamp
    # message is a list with value, note, pressure
    # bongos are currently starting at 4 and go to 8?
    # make offset middle c (or whatever 60 is)
    if (message[1] >= 60) and  (message[1] <= 65): # only allow right messages in for now
        properSolenoid = message[1] - 60 + 4 # 60 is the first note, 4 is the first solenoid
        if message[0] == 144: # noteOn
            liblo.send(target, "/foo", ('i', properSolenoid) , ('i', 4000)) # all the way on for first solenoid
        #elif message[0] == 128: # noteOff
            # liblo.send(target, "/foo", ('i', properSolenoid) , ('i', 0))    # all the way off for first solenoid

midi_in = rtmidi.MidiIn()
midi_in.callback = callback
ports = midi_in.ports
for p in ports:
    print p
midi_in.open_port(0) # the first midi device connected to the computer. if you have more, try doing a print
                     # with midi_in.ports() to pick the one you want

while True:
    n = raw_input()
