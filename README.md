# Robot Bongos

bonga bonga bonga
have some robot bongos

Uses a Raspberry Pi, a PWM shield from Adafruit, and some solenoids to play the drums.

Drums <- Solenoids <-> MOSFETs / 24v Power Supply <-> PWM Shield  <-> Raspberry Pi running OSC Server


Raspberry Pi is controlled with OSC via Python script that takes the first midi device. I've used this to run a sequencer in Ableton, or just a midi keyboard. Take a look at the code, it's pretty straightforward.




