#include <werkstatt.h>

//int gatePin = 2;
//int pwmPin = 4; # using this as our noise generator for now
int secondPinArduino = 2;
int thirdPinArduino = 8;
int fourthPinAruino = 7;
int secondCow = 25;
int lastBong = 24;
int rimBong = 23;
int centerBong = 22;
int rightBong = 21;
int firstCow = 20;


bool touches[] = {false, false, false}; // initialize array for all touchy plants, default to off

noise noise(4);

void OnNoteOn(byte channel, byte note, byte velocity) {
    float velo = int(velocity) / 127.0;
    int veloToDelay = int(velo*15+5); // 5 is the lowest the solenoids respond to.

  if (byte(59) == note) {
    digitalWrite(firstCow, HIGH);
    delay(veloToDelay);
    digitalWrite(firstCow, LOW);
  }    
  if (byte(60) == note) {
    digitalWrite(secondCow, HIGH);
    delay(veloToDelay);
    digitalWrite(secondCow, LOW);
  }
  else if (byte(61) == note) {
    digitalWrite(lastBong, HIGH);
    delay(veloToDelay);
    digitalWrite(lastBong, LOW);
  }
  else if (byte(62) == note) {
    digitalWrite(rimBong, HIGH);
    delay(veloToDelay);
    digitalWrite(rimBong, LOW);
  }

  else if (byte(63) == note) {
    digitalWrite(centerBong, HIGH);
    delay(veloToDelay);
    digitalWrite(centerBong, LOW);
  }
 else if (byte(64) == note) {
    digitalWrite(rightBong, HIGH);
    delay(veloToDelay);
    digitalWrite(rightBong, LOW);
  }

  else {
    //digitalWrite(gatePin, LOW);
    //digitalWrite(pwmPin, HIGH);
    analogWrite(26, 120);
  }
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  if (byte(65) > note) {
    //digitalWrite(gatePin, HIGH);
    //digitalWrite(pwmPin, LOW);  
    analogWrite(26,140);
  }
}

void setup() {
  // put your setup code here, to run once:
  //pinMode(gatePin,OUTPUT);
//  pinMode(pwmPin, OUTPUT);
  noise.generate(2);
  pinMode(secondCow, OUTPUT);
  digitalWrite(secondCow, LOW);

  pinMode(lastBong, OUTPUT);
  digitalWrite(lastBong, LOW);

  pinMode(rimBong, OUTPUT);
  digitalWrite(rimBong, LOW);

  pinMode(centerBong, OUTPUT);
  digitalWrite(centerBong, LOW);

  pinMode(firstCow, OUTPUT);
  digitalWrite(firstCow, LOW);

  pinMode(rightBong, OUTPUT);
  digitalWrite(rightBong, LOW);

  pinMode(secondPinArduino, OUTPUT);
  digitalWrite(secondPinArduino, LOW);

  pinMode(thirdPinArduino, OUTPUT);
  digitalWrite(thirdPinArduino, LOW);

  pinMode(fourthPinAruino, OUTPUT);
  digitalWrite(fourthPinAruino, LOW);

  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  analogWriteResolution(12);  
  //Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.read();
  //noise.generate(2);
  
  if (touchRead(0) > 3500) {
    digitalWrite(secondPinArduino, HIGH);
    if (touches[0] == false) {  // do this so we don't send a bunch of notes when we're being touched.
      usbMIDI.sendNoteOn(110, 100, 2);
      touches[0] == true;
    }
  }
  else {
    if (touches[0] == true) {
      usbMIDI.sendNoteOff(110, 100, 2);
      touches[0] = false;
    }
    digitalWrite(secondPinArduino, LOW);
  }
  
  if (touchRead(1) > 3500) {
    digitalWrite(thirdPinArduino, HIGH);
    if (touches[1] == false) {  // do this so we don't send a bunch of notes when we're being touched.
      usbMIDI.sendNoteOn(113, 100, 2);
      touches[1] == true;
    }
  }
  else {
    digitalWrite(thirdPinArduino, LOW);
     if (touches[1] == true) {
      usbMIDI.sendNoteOff(113, 100, 2);
      touches[1] = false;
    }
  }

  if (touchRead(3) > 5000) {
    digitalWrite(fourthPinAruino, HIGH);
    if (touches[2] == false) {  // do this so we don't send a bunch of notes when we're being touched.
      usbMIDI.sendNoteOn(112, 100, 2);
      touches[2] == true;
    }
  }
  else {
    digitalWrite(fourthPinAruino, LOW);
    if (touches[2] == true) {
      usbMIDI.sendNoteOff(112, 100, 2);
      touches[2] = false;
    }
  }
  
  //long start = millis();
  // throw a touchRead(pin) in here https://www.kickstarter.com/projects/paulstoffregen/teensy-30-32-bit-arm-cortex-m4-usable-in-arduino-a/posts (maybe control oscilator?)
  //long total1 =  cs_4_2.capacitiveSensor(30);
  
  }
