/*
generate samples of for a square wave
with frequency = 1, for a duration of 1

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sf.h>
#include <sfmisc.h>

void gen_sq(short *wav, double dur, int sr) ;
void gen_sin(double *wav, double f, double dur, int sr) ;
double dft_coeff(short *wav, double f, int samples, int sr) ;


int main(void)
{
	double dur  = 5;	// total duration of the sound
	int sr = 44100;
	short *sq_wav;
	double partial = 0.0;
	double probe_f = 3.0;
	//short * sound;

	//allocate array for sound
	sq_wav = (short *)malloc(dur * sr * sizeof(short));
	
	// compute the function
	gen_sq(sq_wav, dur, sr);
	
	// compute one DFT coefficient at a time
	partial = dft_coeff(sq_wav, probe_f, dur*sr, sr);

	printf("result = %f \n", partial);
	
	sfsave("square.wav", sq_wav, dur, sr, nchan) ;
	
	free(sq_wav);
	
	return 0 ;
}


// this is the same as env
void gen_sq(short *wav, double dur, int sr) {
    double T[] = {0.0, 0.5, 1.0};  //time scaled to [0, 1]
    short Y[] = {1, -1, 1};  //amplitude of waveform
    int nPoints = 3;                                    // number of line segments
    double freq = 1;  // frequency
    double period = 1.0 / freq;

    double t_inc = 1.0/sr;
    double time;
    double realT[nPoints];
    double ft = 0;

    int i;
    int samples = dur * sr;

    printf("t-inc %f, samples %d,  per %f \n", t_inc, samples, period);

    for (i=0; i<nPoints; i++) {
      realT[i] = T[i] * period;
    }

    // definition of square wave    
    for (i=0, time=0; i<samples; i++) {
      if (time < realT[1]) {
	wav[i] = 16000 * Y[0];
      }
      else {
	wav[i] = 16000 * Y[1];
      }

      time += t_inc;
      if (time >= period) {
	time -= period;
      }
    }

    // debugging
    for (i=0; i<400; i+=10) {
      printf("%8.4d ", wav[i]);
    }
    printf("\n");
}


void gen_sin(double *wav, double f, double dur, int sr) 
{	
	int i;
	double phase=0, phase_inc;
	double samples = dur*sr;
	double accum = 0;

	for (i=0; i<samples; i++) {
    accum += sin(phase) *  sin(phase);
    phase += phase_inc;

  }


}

double dft_coeff(double *wav, double f, int samples, int sr) {
  // generate sine wave

  double prod[samples];
  int i;
  double result = 0;
  double phase=0, phase_inc;

  phase_inc = 2 * M_PI * f / sr;  // check this

  for (i=0; i<samples; i++) {
    prod[i] = sin(phase) * wav[i];
    phase += phase_inc;

    result += prod[i];
  }

  return result/samples;
}


