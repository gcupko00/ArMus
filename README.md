# ArMus

ArMus (Arduino Music) is a simple library which provides basic functions for playing music on piezoelectric speaker connected to Arduino. ArMus is still in development and possibly unstable.

## Functions

Currently supported functionalities:

* Parsing string which represents a melody and reproducing it on the piezo speaker
* Changing tempo
* Playing few common sounds and simple effects: beeping alarm, ringing and siren

More features comming soon.

## Usage

The default configuration consists of piezo speaker connected to Arduino's digital pin 10 as shown on the following illustrations.

![Default configuration](assets/default_conf.jpg?raw=true "Default configuration")

![Default configuration schematic](assets/default_conf_schem.jpg?raw=true "Default configuration schematic")

Three constructors are available:

* `ArMus()` - default constructor.
* `ArMus(int buzzerPin)` - initializes ArMus with custom piezo pin.
* `ArMus(int buzzerPin, int tempo)` - initializes ArMus with custom piezo pin and tempo.

<br>

By default, Arduino's digital pin 10 is considered as piezo pin and default tempo is 120.

ArMus provides `playMelody` function which takes string as an argument. String can contain series of notes and rests separated with spaces. Note is written in format:

`<relative octave><note name><note value><staccato>`

Only note name is required, all other parts are optional.

Note names must be in the set of notes: { A, b, B, C, d, D, e, E, F, g, G, a }. Base note A represents 440 Hz frequency.

Relative octave tells how many octaves is the note distanced from the octave of base note A. It must be a number between -3 and 3. Default relative octave is 0.

Note value specifies the length of note. For example, value of 2 means that the note is half note. Default value is quarter note.

Staccato is a boolean which tell if note should be played as a staccato (only half of its value is played). By default, note is not staccato note. To turn it into staccato, add asterisk after note (e.g. `1E8*`).

Rests are writen in format `R<value>` or `r<value>`. Rest value is basically the same as note value - it specifies how long the rest is.

To change tempo, you can use `setTempo(int tempo)` function.

## Example code

```cpp
#include <armus.h>

ArMus a(10);

void setup() { }

void loop() {

  char m1[] = "A4 B4 C4 D4 E4 F4 r2 G8 F8 E8 D8 C8 B8 r2";
  char m2[] = "A4 B4 C4 D4 E4 F4 r2 1A8 1B8 1C8 1D8 1E8 1F8 r2";

  a.playMelody(m1);
  a.setTempo(150);
  a.playMelody(m2);
}
```

