#include <armus.h>

const int bPin = 10;
ArMus a;

void setup() { }

void loop() {
  alarm(5);
  delay (1000);
  phoneRing(3);
  delay (1000);
  emergSiren(5);
  delay(1000);
}

void alarm(int m) {
  for (int i = 0; i < m; i++) {
    a.clockAlarm();
    delay(500);  
  }
}

void phoneRing(int m) {
  for (int i = 0; i < m; i++) {
    // ring thre times with frequency of 1250 Hz
    for (int j = 0; j < 3; j++) {
      a.ring(1250); 
      delay(1000);  
    }
    // short pause before the next three rings
    delay(750);
  }
}

void emergSiren(int m) {
  a.siren(600, 800, 500);
  // slow siren
  for (int i = 0; i < m; i++) {
    a.siren(800, 1200, 1200);
    // play the peak frequency for the short time
    tone(bPin, 1200);
    delay(100);
    a.siren(1200, 800, 800);
    // play the lowest frequency for the short time
    tone(bPin, 800);
    delay(100);
  }
  // transition to fast siren
  a.siren(800, 1000, 100);
  // fast siren
  for (int i = 0; i < m; i++) {
    a.siren(1000, 1200, 50);
    a.siren(1200, 1000, 70);
  }  
  noTone(bPin);
}


