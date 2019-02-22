// Project 3 Jose&Nima

#ifndef __music__
#define __music__

#include "avr.h"
#include "stdio.h"
#include "lcd.h"

//     note delay(freq)
#define A 114
#define Asharp 108
#define B 101
#define C 96
#define Csharp 90
#define D 85
#define Dsharp 81 
#define E 76
#define F 72
#define Fsharp 68
#define G 64
#define Gsharp 60
#define Rest 0 // rest is not working yet

//      duration
#define W 1
#define H 0.5
#define Q 0.25
#define EI 0.125


char bufmsg[17];

unsigned int tempo;
unsigned int vol;

typedef struct{
	unsigned int frequency;
	float length;
} note;

typedef struct {
	char title[17];
	note *sequence;
	unsigned int length;
}songs;


void play(songs song);
void clrLine(unsigned int r);
void playsingle(unsigned int freq, float duration);


#endif