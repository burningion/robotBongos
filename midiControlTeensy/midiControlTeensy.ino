#include <werkstatt.h>

//int gatePin = 2;
//int pwmPin = 4; # using this as our noise generator for now
int secondCow = 25;
int lastBong = 24;
int rimBong = 23;
int centerBong = 22;
int rightBong = 21;
int firstCow = 20;

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
  pinMode(rimBong, OUTPUT);
  pinMode(centerBong, OUTPUT);
  pinMode(firstCow, OUTPUT);
  pinMode(rightBong, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  analogWriteResolution(12);  
  Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.read();
  noise.generate(2);
  //long start = millis();
  // throw a touchRead(pin) in here https://www.kickstarter.com/projects/paulstoffregen/teensy-30-32-bit-arm-cortex-m4-usable-in-arduino-a/posts (maybe control oscilator?)
  //long total1 =  cs_4_2.capacitiveSensor(30);
  
  }
