int gatePin = 2;
int pwmPin = 4;
int secondCow = 25;
int lastBong = 24;
int rimBong = 23;
int centerBong = 22;
int rightBong = 21;

void OnNoteOn(byte channel, byte note, byte velocity) {
    float velo = int(velocity) / 127.0;
    int veloToDelay = int(velo*15+5); // 5 is the lowest the solenoids respond to.
    
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
    digitalWrite(gatePin, LOW);
    digitalWrite(pwmPin, HIGH);
    analogWrite(26, 2000);
  }
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  if (byte(65) > note) {
    digitalWrite(gatePin, HIGH);
    digitalWrite(pwmPin, LOW);  
    analogWrite(26,2400);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(gatePin,OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(secondCow, OUTPUT);
  digitalWrite(secondCow, LOW);
  pinMode(lastBong, OUTPUT);
  pinMode(rimBong, OUTPUT);
  pinMode(centerBong, OUTPUT);
  pinMode(rightBong, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  analogWriteResolution(12);  
}
 
void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.read();
}
