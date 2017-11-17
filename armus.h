/* Arduino Music Library
 * https://github.com/gcupko00/ArMus
 * Copyright (c) 2017 Gligorije Cupkovic
 * 
 * This file is part of ArMus.
 *
 * ArMus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ArMus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ArMus. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ArMus_h
#define ArMus_h

#include "Arduino.h"
#include <ctype.h>

#define ALARM_FREQ 1000

class ArMus
{    
    public:
    
        /**
         * Default constructor
         */
        ArMus();
        
        /**
         * A constructor which initializes pin
         *
         * @param buzzerPin - Arduino pin to which buzzer is connected
         */
        ArMus(int buzzerPin);
        
        /**
         * A constructor which initializes pin and tempo
         *
         * @param buzzerPin - Arduino pin to which buzzer is connected
         * @param tempo - tempo to be used to play melody
         */
        ArMus(int buzzerPin, int tempo);
        
        /**
         * This function parses string representing a melody - a string of notes and rests separated with space character
         *
         * @param m - string representing a melody to be parsed and played
         */
        void playMelody(char m[]);
        
        /**
         * Setter for tempo
         *
         * @param tempo - new tempo value
         */
        void setTempo(int tempo);
        
        /**
         * Plays four 1000 Hz beeps
         */
        void clockAlarm();
        
        /**
         * Plays ringing sound
         *
         * @param f - frequency of ringing sound
         */
        void ring(int f);
        
        /**
         * Plays a range of frequencies sequentially (in any direction)
         *
         * @param limit1 - specifies first frequency, from which playing starts
         * @param limit2 - specifies last frequency, with which playing ends
         * @param duration - specifies how long time it takes to play the range of frequencies (in milliseconds)
         */
        void siren(int limit1 = 500, int limit2 = 700, int duration = 1000);
        
    private:
        int _buzzer;
        float _tempo;
        static const char notes[];
        const int minOctave = -3;
        const int maxOctave = 3;
        const float f0 = 440.0;
        
        /**
         * This function parses string representing a note
         * 
         * @param nStr - note string (format ONLS - octave + name + value + staccato)
         * @param o - integer to store octave to
         * @param n - char to store note name to
         * @param v - integer to store note value to
         * @param stacc - boolean to store staccato to
         * 
         * @return true if successfully parsed, false if not 
         */
        bool parseNote(char nStr[], int& o, char& n, float& v, bool& stacc);
        
        /**
         * Parses rest value
         * 
         * @param rStr - string containing rest value
         * @param v - variable used to store rest value
         * @returns true if rest string is successfully parsed and valid, false otherwise
         */
        bool parseRest(char rStr[], float& v);
        
        /**
         * Validates and plays note on buzzer
         * 
         * @param n - note name (must be in { 'A', 'b', 'B', 'C',  'd', 'D', 'e', 'E', 'F', 'g', 'G', 'a'})
         * @param o - octave (relative to base note A0 = 440Hz)
         * @param v - note value (relative value is calculated as 1/l)
         * @param stacc - tells if note should be played as staccato (50% of note value)
         */
        void note(char n, int o = 0, float v = 4, bool stacc = false);
        
        /**
         * Sets no tone on buzzer
         * 
         * @param v - rest value
         */
        void rest(float v);
        
        /**
         * Checks if note is valid
         * 
         * @param n - note character
         * @param o - octave octave (relative to base note A0 = 440Hz)
         * @param v - note value
         * @return true if note satisfies validity criteria, false otherwise
         */
        bool isNoteValid(char n, int o, float v);
        
        /**
         * Cheks if note name is correct
         * 
         * @param n - note to check
         * @return true if note is in array of valid notes, false otherwise
         */
        bool isNote(char &n);
};

#endif