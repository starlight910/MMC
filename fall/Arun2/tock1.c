#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>
#include "random.h"

void adsr2(short sound[], double dur, int sr, 
	   double T[], double A[], int N, int flag) ;
void addsyn(short sData[], double dur, int sr, 
	    double F, double dB, 
	    double partialF[], double partialA[], int nPartials);
void concatenate(short output[], short input[], 
		 double st, double dur, int sr) ;

/*************************************
void envelopeFixed()

simple version to create envelope
and apply it to sound array
 *************************************/

static void envelopeFixed(short *sound, double dur, int sr) {
  double T[] = {0.0, 0.1, 0.9, 1.0};
  double A[] = {0.0, 1.0, 1.0, 0.0};
  int nPoints = 4;
  int flag = 0;

  adsr2(sound, dur, sr, T, A, nPoints, flag) ; // apply the envelope
  return;  
}


/***********************************
tock1()

what is the simplest tick sound one could make:
10 partials of sawtooth, square or triangle?
fixed fundamental 
 ***********************************/
void tock1(short *window, double dur, int sr)
{
  double tickDur = dur / 30.0 ;		// duration of the 'tick'

  double F1 = 1000.0 ; // , F2 = 500;
  int nPartials = 20;
  double *partialF, *partialA ;
  double dB = 80;
  int i;

  partialF = (double *) Malloc(nPartials * sizeof(double));
  partialA = (double *) Malloc(nPartials * sizeof(double));

  for (i=0; i<nPartials; i++) {
    partialF[i] = (double) (i+1);
    partialA[i] = 1.0 / (double)(i+1);
  }

  // create the 'tick'
  addsyn(window, tickDur, sr, F1, dB, partialF, partialA, nPartials) ;

  Free(partialF) ;
  Free(partialA) ;

  envelopeFixed(window, dur, sr) ;

  return;
}

