
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
//#include <cmath>
//#include <iostream>
//#include <Speaker.h>

#define Octave 5

//Music Notes based on Octave--
#define C 16.3516 * pow(2, Octave)
#define D 18.35405 * pow(2, Octave)
#define E 20.60172 * pow(2, Octave)
#define F 21.82676 * pow(2, Octave)
#define G 24.49971 * pow(2, Octave)
#define A 27.5 * pow(2, Octave)
#define B 30.86771 * pow(2, Octave)
#define high_C 32.70320 * pow(2, Octave)
#define rest 0

#define soundDetectorAnalogPin A0
#define soundDetectorPin 2
#define motorPin1 9
#define motorPin2 10
#define speakerPIN 11
#define potPin 12

//int octave = 5;
int songLength = 54;  

//int note_play[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};

int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};

int noteIndex = 0;
int song_tempo = 250;
int motorSpeed = 50;

bool updateOctave = true;

bool soundDetected = false;
int soundValue = 0;


int tempo = 50;

bool motorClockwise = true;
void setup() {
  // put your setup code here, to run once:
  //pinMode(speakerPIN, OUTPUT);
  //pinMode(motorPIN, OUTPUT);
  Serial.begin(9600);

  pinMode(soundDetectorPin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  

  if (soundDetected) {

    
    /*
    if (updateOctave) {
      adjustOctave();
      updateOctave = false;
    }
    */
    motorMove(noteIndex);
  
    
    tone(speakerPIN, notes[noteIndex], beats[noteIndex]*tempo/512);
    noteIndex++;
    if (noteIndex >= songLength) {
      noteIndex = 0;
    }
    delay(500);  
  }
  else {
    soundValue = analogRead(soundDetectorAnalogPin);
    if (soundValue > 80) {
      soundDetected = true;
      Serial.print("Sound Detected\n");
    }
  }
  
  
}

void motorMove(int noteIndex) {

  if (notes[noteIndex] != rest) {

    Serial.print(notes[noteIndex]);
    Serial.print("\n");
    if (motorClockwise == true) {
      Serial.print("Move clockwise\n");
      analogWrite(motorPin1, motorSpeed);
      analogWrite(motorPin2, 0);
      motorClockwise = false;
    }
    else {
      Serial.print("Move counterclockwise\n");
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, motorSpeed);
      motorClockwise = true;
    }
  }
  else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
  }
}

//void adjustOctave() {
//  for (int x = 0; x < 54; x++) {
//    notes[x] = note_play[x] * pow(2, octave);
//  }
//}

double goertzel_FFT(double* data, double k, int N) {
  
  double omega = 2.0 * M_PI * k / (double) N;
  double cr = cos(omega * M_PI / 180.0);
  double ci = sin(omega * M_PI / 180.0);
  double coeff = 2.0 * cr;
  double sprev = 0.0;
  double sprev2 = 0.0;

  for (int i = 0; i < N - 1; i++) {
    double s = data[i] + coeff * sprev - sprev2;
    sprev2 = sprev;
    sprev = s;
  }

  double It = cr * sprev - sprev2;
  double Qt = ci * sprev;

  double omega2 = 2.0 * M_PI * k;
  double cr2 = cos(omega2 * M_PI / 180.0);
  double ci2 = sin(omega2 * M_PI / 180.0);

  double I = It * cr2 + Qt * ci2;
  double Q = -It * ci2 + Qt * cr2;

  return sqrt(I * I + Q * Q);
}
