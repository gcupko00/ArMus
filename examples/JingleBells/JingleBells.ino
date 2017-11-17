#include <armus.h>

char m1[] = "G G 1E 1D 1C";
char ghd[] = "G1.5";
char ahd[] = "1A1.5";
char m2[] = "1A 1A 1E 1D 1C";
char m3[] = "1B 1B 1B 1B";
char m4[] = "1G 1G 1F 1D 1E1.5";
char m5[] = "1G 1G 1G 1G";
char m6[] = "2A 1G 1F 1D 1C1";
char m7[] = "1E 1E 1E2";
char m8[] = "1E 1G 1C 1D 1E1";
char m9[] = "1F 1F 1F 1F 1F 1E 1E 1E";
char m10[] = "1E 1D 1D 1E 1D2 1G2";
char m11[] = "1G 1G 1F 1D 1C1";

ArMus a(10, 150);

void setup() { }

void loop() {

  /*  part one  */
  
  a.playMelody(m1);   // dashing through the
  a.playMelody(ghd);  // snow
  a.playMelody(m1);   // in a one horse open
  a.playMelody(ahd);  // sleigh
  
  a.playMelody(m2);   // o'er the hills we
  a.playMelody(m3);   // go
  a.playMelody(m4);   // laughing all the way
  
  a.playMelody(m1);   // bells on bobtail
  a.playMelody(ghd);  // ring
  a.playMelody(m1);   // making spirits
  a.playMelody(ahd);  // bright
  
  a.playMelody(m2);   // what fun it is to
  a.playMelody(m5);   // ride and sing
  a.playMelody(m6);   // a sleighing song tonight

  /*  part two  */
  
  a.playMelody(m7);   // jingle bells
  a.playMelody(m7);   // jingle bells
  a.playMelody(m8);   // jingle all the way
  a.playMelody(m9);   // oh what fun it is to ride
  a.playMelody(m10);  // in a one horse open sleigh
  
  a.playMelody(m7);   // jingle bells
  a.playMelody(m7);   // jingle bells
  a.playMelody(m8);   // jingle all the way
  a.playMelody(m9);   // oh what fun it is to ride
  a.playMelody(m11);  // in a one horse open sleigh
  
  delay(1000);
}

