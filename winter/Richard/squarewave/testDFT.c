#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

void generate_signal(double *sound, double dur, int sr) ;
double dft_coeff(double *sound, double f, int samples, int sr) ;


int main(void)
{
	double duration  = 1;	// total duration of the sound
	int sr = 400;
	double *sound;
	double partial_amp = 0.0;

	//allocate array for sound
	sound = (double *)malloc(duration * sr * sizeof(double));

	// compute the function
	generate_signal(sound, duration, sr);

	// compute one DFT coefficient at a time
	partial_amp = dft_coeff(sound, 10, duration * sr, sr);

	printf("result = %f \n", partial_amp);
	free(sound);
	
	return 0 ;
}


// this is the same as env
void generate_signal(double *sound, double dur, int sr) {
    double T[] = {0.0, 0.1, 0.4, 0.6, 0.9, 1.0};  //time scaled to [0, 1]
    double Y[] = {0.0, 1.0, 1.0, -1.0, -1.0, 0.0};  //amplitude of waveform
    int segs = 6;                                    // number of line segments
    double freq = 10;  // frequency
    double period = 1.0 / freq;

    double t_inc = 1.0/sr;
    double time;
    double realT[segs];
    double ft = 0;

    int i;
    int samples = dur * sr;

    printf("t-inc %f, samples %d,  per %f \n", t_inc, samples, period);

    for (i=0; i<segs; i++) {
      realT[i] = T[i] * period;
    }

    
    for (i=0, time=0; i<samples; i++) {
      sound[i] = ft;

      time += t_inc;
      if (time >= period) {
	time -= period;
      }

      if (realT[0] <= time && time < realT[1]) {
	ft += t_inc * (Y[1] - Y[0])/((T[1] - T[0])*period);   //time * slope
      } 
      else if (realT[1] <= time && time < realT[2]) {
	ft = 1.0;
      } 
      else if (realT[2] <= time && time < realT[3]) {
	ft += t_inc * (Y[3] - Y[2])/((T[3] - T[2])*period);   
      }
      else if (realT[3] <= time && time < realT[4]) {
	ft = -1.0;
      }
      else {
	ft += t_inc * (Y[5] - Y[4])/((T[5] - T[4])*period);   
      }

    }

    for (i=0; i<40; i++) {
      printf("%8.4f ", sound[i]);
    }
}


double dft_coeff(double *sound, double f, int samples, int sr) {
  // generate sine wave

  double blah[samples];
  int i;
  double result = 0;
  double phase=0, phase_inc;

  phase_inc = 2 * M_PI * f / sr;  // check this

  for (i=0; i<samples; i++) {
    blah[i] = sin(phase) * sound[i];
    phase += phase_inc;

    result += blah[i];
  }

  return result;
}


