#!/usr/bin/python

from Adafruit_PWM_Servo_Driver import PWM
import time

# ===========================================================================
# Example Code
# ===========================================================================

# Initialise the PWM device using the default address
pwm = PWM(0x40)
# Note if you'd like more debug output you can instead run:
#pwm = PWM(0x40, debug=True)

servoMin = 150  # Min pulse length out of 4096
servoMax = 600  # Max pulse length out of 4096

solenoidMin = 0 
solenoidMax = 2000

def setServoPulse(channel, pulse):
  pulseLength = 1000000                   # 1,000,000 us per second
  pulseLength /= 60                       # 60 Hz
  print "%d us per period" % pulseLength
  pulseLength /= 4096                     # 12 bits of resolution
  print "%d us per bit" % pulseLength
  pulse *= 1000
  pulse /= pulseLength
  pwm.setPWM(channel, 0, pulse)

pwm.setPWMFreq(60)                        # Set frequency to 60 Hz
while (True):
  # Change speed of continuous servo on channel O
#  pwm.setPWM(1, 0, servoMin)
#  time.sleep(.21)
#  pwm.setPWM(0, 0, servoMin)
#  time.sleep(.51)
#  pwm.setPWM(1, 0, servoMax)
#  time.sleep(.21)
#  pwm.setPWM(0, 0, servoMax)
#  time.sleep(.51)
#  pwm.setPWM(2, 0, servoMin)
#  time.sleep(1)
#  pwm.setPWM(2, 0, servoMax)
#  time.sleep(0.5)
  for i in range(4,9):
    pwm.setPWM(i, 0, solenoidMax)
    time.sleep(0.03)
    pwm.setPWM(i, 0, solenoidMin)
    time.sleep(0.02)
    pwm.setPWM(i, 0, solenoidMax)
    time.sleep(0.03)
    pwm.setPWM(i, 0, solenoidMin)
    time.sleep(0.02)

  time.sleep(1)
'''
  pwm.setPWM(4, 0, solenoidMax)
  time.sleep(0.1)
  pwm.setPWM(4,0, int(solenoidMax/2))
  pwm.setPWM(4, 0, solenoidMin)
  time.sleep(0.5)
  pwm.setPWM(5, 0, solenoidMax)
  time.sleep(0.06)
  pwm.setPWM(4,0, int(solenoidMax/2))
  pwm.setPWM(5, 0, solenoidMin)
'''
