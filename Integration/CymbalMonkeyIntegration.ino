#include <stdio.h>
#include <math.h>
//#include <Speaker.h>

#define Octave 6

//Music Notes based on Octave--
#define C 16.3516*pow(2,Octave)
#define D 18.35405*pow(2,Octave)
#define E 20.60172*pow(2,Octave)
#define F 21.82676*pow(2,Octave)
#define G 24.49971*pow(2,Octave)
#define A 27.5*pow(2,Octave)
#define B 30.86771*pow(2,Octave)
#define high_C 32.70320*pow(2,Octave)
#define rest 0

#define speakerPIN 11
#define motorPin1 9
#define motorPin2 10


int songLength = 54;  
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};

int noteIndex = 0;
int song_tempo = 250;
int motorSpeed = 0;//50;

int tempo = 50;

bool motorClockwise = true;
void setup() {
  // put your setup code here, to run once:
  //pinMode(speakerPIN, OUTPUT);
  //pinMode(motorPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

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

  
  tone(speakerPIN, notes[noteIndex], beats[noteIndex]*tempo/512);
  noteIndex++;
  if (noteIndex >= songLength) {
    noteIndex = 0;
  }
  delay(1000);
}
