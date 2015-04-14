# Robot Bongos

bonga bonga bonga
have some robot bongos

Uses a Teensy LC, some MOSFETS, some plants, and some solenoids to make a robotic bongo that you control with plants. 

Drums <- Solenoids <-> MOSFETs / 24v Power Supply <-> Teensy <-> Arduino w/ DMX Shield <-> DMX Decoder / LEDs


Initially this project ran on the Raspberry Pi. But in NYC I have a lot of Wireless interference, and I couldn't get consistent latency at any time other than the day. So I rewrote everything on the Teensy.

It's way better.

Basically, the Teensy is a MIDI in instrument, and it uses MIDI notes to play each solenoid. Every solenoid has a matching MIDI note. Look at the source code and you'll see.

The Teensy also has a MIDI out for each of the plants. The plants are just running on a capacitive touch pin, and have touchRead called every couple microseconds. When they go above a threshold, a MIDI note is triggered, and a pin out to the Arduino is raised to HIGH, to make the DMX lights light up.


If you still want to use a Raspberry Pi:

Raspberry Pi is controlled with OSC via Python script that takes the first midi device. I've used this to run a sequencer in Ableton, or just a midi keyboard. Take a look at the code, it's pretty straightforward.




