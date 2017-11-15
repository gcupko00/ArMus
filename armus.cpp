#include "Arduino.h"
#include "armus.h"

const char ArMus::notes[] = { 'A', 'b', 'B', 'C',  'd', 'D', 'e', 'E', 'F', 'g', 'G', 'a'};

ArMus::ArMus(): _buzzer(10), _tempo(120) { }

ArMus::ArMus(int buzzerPin): _buzzer(buzzerPin), _tempo(120) { }

ArMus::ArMus(int buzzerPin, int tempo) : _buzzer(buzzerPin), _tempo(tempo) { }

void ArMus::setTempo(int tempo) {
    _tempo = tempo;
}

void ArMus::playMelody(char mStr[]) {
    int o; 
    char n;
    float v; 
    bool stacc;
    
    char buff[16];
    
    for (int i = 0; i < strlen(mStr); i++) {
        buff[0] = '\0';
        int j = 0;
        
        // Get next segment
        while (mStr[i] != ' ' && i < strlen(mStr)) {
            buff[j++] = mStr[i++];
        }

        buff[j] = '\0';
        
        bool parsed = false;
        
        // check if rest or note
        if (buff[0] == 'R' || buff[0] == 'r') {
            parsed = parseRest(buff, v);
            if (parsed) {
                // play rest
                rest(v);
            }
        }
        else {
            parsed = parseNote(buff, o, n, v, stacc);
            if (parsed) {
                // play note
                note(n, o, v, stacc);
            }
        }
    } 
}

void ArMus::clockAlarm() {
    for (int i = 0; i < 4; i++) {
        tone(_buzzer, ALARM_FREQ);
        delay(100);
        noTone(_buzzer);
        delay(100);      
    }
}

void ArMus::ring(int f) {
    for (int i = 0; i < 40; i++) { 
        tone(_buzzer, f);
        delay(15);
        noTone(_buzzer);
        delay(25);
    }    
}

void ArMus::siren(int limit1, int limit2, int duration) {
    if (limit1 == limit2) return;  
    int d = duration / abs(limit1 - limit2);  
  
    // keeps delay in reasonable range
    if (d > 15) d = 15;
    else if (d < 1) d = 1;

    if (limit2 > limit1) {
        for (int i = limit1; i < limit2; i++) { 
            tone(_buzzer, i);
            delay(d);
        }
    }
    else {
        for (int i = limit1; i > limit2; i--) { 
            tone(_buzzer, i);
            delay(d);
        }    
    }
}

bool ArMus::parseNote(char nStr[], int& o, char& n, float& v, bool& stacc) {
    int i = 0;
    char buff[16];

    // defaults
    o = 0;
    v = 4.0;
    stacc = false;
    
    buff[0]  = '\0';
    
    // parse optional octave distance
    if (nStr[i] == '-') {
        // for negative octave
        buff[0] = nStr[i++];
        buff[1] = nStr[i++];
        buff[2] = '\0';
        o = atoi(buff);    
    }
    else if (!isNote(nStr[i])) {
        // for positive octave
        buff[0] = nStr[i++];
        buff[1] = '\0';
        o = atoi(buff);
    }

    // get note after octave
    n = nStr[i];
    ++i;

    // stop if note name is invalid
    if (!isNote(n)) {
        return false;
    }

    // parse note value
    if (isDigit(nStr[i])) {
        int j = 0;
        while (i < strlen(nStr) && (isDigit(nStr[i]) || nStr[i] == '.')) {
            buff[j++] = nStr[i++];
            buff[j] = '\0';
        }
        v = atof(buff);
    }

    // parse staccato
    if (nStr[i] == '*') {
        stacc = true;
    }

    if (i > strlen(nStr)) {
        return false;
    }

    return true;
}

bool ArMus::parseRest(char rStr[], float& v) {
    int i = 1;
    char buff[16];

    // default
    v = 4;

    if (isDigit(rStr[i])) {
        // parse rest value
        int j = 0;
        while (i < strlen(rStr) && (isDigit(rStr[i]) || rStr[i] == '.')) {
            buff[j++] = rStr[i++];
            buff[j] = '\0';
        }
        v = atof(buff);
    }
    else {
        return false;
    }

    if (i != strlen(rStr) || v < 1) {
        return false;
    }

    return true;
}

void ArMus::note(char n, int o, float v, bool stacc) {  
    float f = f0;
    float s = 0;

    // if note is not valid, don't try to play it
    if (!isNoteValid(n, o, v)) return;

    // find how far the note is from A
    for (int i = 0; i < sizeof(notes); ++i) {
        if (n == notes[i]) {
            s = (float)i;
            break;
        }
    }
    // Move to correct octave
    s = s + 12.0 * o;

    // Calculate frequency using formula f = f0 * (2^(1/12))^s
    f = f * pow(pow(2.0, 1.0/12.0), s);

    // Calculate note duration based on tempo and note value
    int d = 4.0 * (60000.0 / _tempo) / v;

    // Play note on buzzer
    tone(_buzzer, f);

    // If note is staccato play only for half of total duration
    if (stacc) {
        delay (d/2);
        noTone(_buzzer);
        delay (d/2);
    }
    else {
        delay(d - 10);
        // Very short rest to separate notes when playing melody
        noTone(_buzzer);
        delay(10);
    } 
}

void ArMus::rest(float v) {
    int d = 4.0 * (60000.0 / _tempo) / v;
    noTone(_buzzer);
    delay(d);    
}

bool ArMus::isNoteValid(char n, int o, float v) {
    if (!isNote(n)) return false;
    if (o < minOctave || o > maxOctave) return false;
    if (v < 1.0) return false;
    return true;
}

bool ArMus::isNote(char &n) {
    for (int i = 0; i < sizeof(notes); i++) {
        if (n == notes[i]) return true;
    }

    return false;
}
