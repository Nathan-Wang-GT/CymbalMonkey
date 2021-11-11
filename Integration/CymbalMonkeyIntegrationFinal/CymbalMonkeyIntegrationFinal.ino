
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
//#include <cmath>
//#include <iostream>
//#include <Speaker.h>

//#define Octave 5


//Music Notes based on Octave--
#define C 16.3516// * pow(2, Octave)
#define D 18.35405// * pow(2, Octave)
#define E 20.60172// * pow(2, Octave)
#define F 21.82676// * pow(2, Octave)
#define G 24.49971// * pow(2, Octave)
#define A 27.5// * pow(2, Octave)
#define B 30.86771// * pow(2, Octave)
#define high_C 32.70320// * pow(2, Octave)
#define rest 0

#define soundDetectorAnalogPin A0

#define soundDetectorPin 2
#define motorPin1 9
#define motorPin2 10
#define speakerPIN 11
#define potPin 12

int octave = 5;
int songLength = 54;  

int note_play[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};

int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};

int noteIndex = 0;
//int song_tempo = 250;
int tempo = 150;

int motorSpeed = 50;

//bool updateOctave = true;

bool soundDetected = false;
int soundValue = 0;


//int tempo = 2;

bool motorClockwise = true;
void setup() {
  // put your setup code here, to run once:
  //pinMode(speakerPIN, OUTPUT);
  //pinMode(motorPIN, OUTPUT);
  Serial.begin(9600);

  pinMode(soundDetectorPin, INPUT);
  //pinMode(potPin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  adjustOctave();

  if (soundDetected) {

    
    /*
    if (updateOctave) {
      adjustOctave();
      updateOctave = false;
    }
    */
    
  

    int duration = beats[noteIndex] * tempo;//beats[noteIndex] * 1000;//1000 / beats[noteIndex] / tempo;

    //int pause = // beats[1] / tempo * 1.3;//beats[1] * 1000;//1000 / beats[1] / tempo;

    int analogValue = analogRead(A1);

    int adjustedOctave = int(analogValue * 5 / 1023 + 2);

    if (adjustedOctave != octave) {
      octave = adjustedOctave;
      Serial.print(octave);
      adjustOctave();
    }
    //int(analogValue * 7 / 1023 + 1);//map(analogValue, 0, 1023, 1, 8);

    
    
    
    motorMove(noteIndex);
    tone(speakerPIN, notes[noteIndex], duration);//1000/duration / tempo); //* tempo/512);
    //tone(speakerPIN, notes[1], pause);
    delay(1000);
    noteIndex+= 2;
    if (noteIndex >= songLength) {
      //delay(pause);
      noteIndex = 0;
    }

    //int pause = 1000;
    
    //tone(speakerPIN, notes[noteIndex + 1], pause);
    
    //delay(1000);
    //noTone(8);  
  }
  else {
    soundValue = analogRead(soundDetectorAnalogPin);
    if (soundValue > 40) {
      soundDetected = true;
      Serial.print("Sound Detected\n");
    }
  }
  
  
}

void motorMove(int noteIndex) {

//  if (notes[noteIndex] != rest) {
//
//    Serial.print(notes[noteIndex]);
//    Serial.print("\n");
//    if (motorClockwise == true) {
//      Serial.print("Move clockwise\n");
//      analogWrite(motorPin1, motorSpeed);
//      analogWrite(motorPin2, 0);
//      motorClockwise = false;
//    }
//    else {
//      Serial.print("Move counterclockwise\n");
//      analogWrite(motorPin1, 0);
//      analogWrite(motorPin2, motorSpeed);
//      motorClockwise = true;
//    }
//  }
//  else {
//    analogWrite(motorPin1, 0);
//    analogWrite(motorPin2, 0);
//  }
  analogWrite(motorPin1, 30);
  analogWrite(motorPin2, 0);
}

void adjustOctave() {
  for (int x = 0; x < 54; x++) {
    notes[x] = note_play[x] * pow(2, octave);
  }
}
