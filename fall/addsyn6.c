#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sf.h>
#include <sfmisc.h>

int main(void)
{
	short *sound;      // array to create the data
	double dur = 5;    // duration of the sound in seconds
	int sr = 44100;    // sampling rate (number of samples per second)
	int nchan = 1;     // number of channels of sound
	double F = 440;    // fundamental frequency
	double dB = 93;    // amplitude of resulting sound
	int nPartials = 6; // total number of partials
	double partialF[] = {1.0, 1.26, 1.59, 1.75, 2.0, 2.25}; // partial frequency
	double partialA[] = {1.0, 1.0, 1.0, 0.0, 0.0, 0.0};    // partial amplitude

	int samples;         // number of samples of the sound
	int dataSizeInBytes; // total number of partials

	void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials);

	samples = dur * nchan * sr;                        // duration of sound in samples
	dataSizeInBytes = samples * nchan * sizeof(short); // duration in bytes

	sound = (short *)Malloc(dataSizeInBytes); // allocate memory

	// call the additive synthesis function
	addsyn(sound, dur, sr, F, dB, partialF, partialA, nPartials);

	sfsave("addsyn.wav", sound, dur, sr, nchan);

	//playbuffer(sound, dur, sr, 1, 1);   // play the sound

	exit(EXIT_SUCCESS);
}

/*
 * addsyn(sData[], dur, sr, F, dB, partialF[], partialA[], nPartials)
 * routine for additive synthesis.
 * adds together 'nPartials' of sine waves.
 *
 * The frequency of each partial is given as a proportion in the array 'partialF[]'
 * The amplitude of each partial is given as a proportion in the array 'partialA[]'
 * 'F' = fundamental frequency in Hertz; 'dB' output amplitude in decibels.
 */
void addsyn(short sData[],double dur,int sr,double F,double dB,double partialF[],double partialA[],int nPartials)
	// sData[]    -> array for the resulting sound
	// dur        -> duration of sound in seconds
	// sr         -> sampling rate
	// dB         -> fundamental frequency in Hertz
	// partialF[] -> list of partial frequencies (proportional)
	// partialA[] -> list of partial amplitudes (proportional)
	// nPartials  -> number of partials (length of arrays)
{
	int n;           // counter for partials
	double f;        // variable for partial frequency
	double A;        // variable for partial amplitude
	double nyquist;  // set the nyquist frequency
	double *tone;    // array to build the partials

	// declarations of functions called from addsyn()
	void createPartial(double tone[], double F, double A, double dur, int sr);
	void copyToShort(short oupput[], double input[], double dur, int sr);
	void scale(double sound[], double dur, int sr, double dB);

	nyquist = sr / 2;  // set the nyquist frequency

	// allocate memory to create additive synthesis tone
	tone = (double *)Malloc(dur * sr * sizeof(double));

	for ( n = 0; n < nPartials ; n++)  // loop to create partials
	{
		f = F * partialF[n];   // calculate partial frequency
		if ( f >= nyquist)     // make sure frequency is less than nyquist
			break;

		A = partialA[n];  // partial amplitude (proportional)

		createPartial(tone, f, A, dur, sr);  // create one partial
	}

	scale(tone, dur, sr, dB);   // scale values to desired dB
	copyToShort(sData, tone, dur, sr);  // copy doubles to shorts

	Free(tone);  // free the 'double' array

	return;
}
/*
 * scale(data[], N, dB)
 * y[n] = ((ymax-ymin) / (xmax-xmin)) * (x[n] - xmin) + ymin
 */
void scale(double sound[], double dur, int sr, double dB)
	// sound[] -> array for the sound to be scaled
	// dur     -> duration of the sound in seconds
	// sr      -> sampling rate
	// dB      -> amplitude of sound in decibels
{
	double xmin, xmax; // current linear min/max values
	double ymax, ymin; // desired linear max/min values
	double sf;         // scaling factor
	int x,             // counter
		samples;       // duration of sound in samples

	samples = dur * sr; // calculate value for samples

	xmax = xmin = sound[0];  // set initial values fir xmin/xmax
	for (x = 0; x < samples; x++ )  // find min/max
	{
		if ( sound[x] > xmax)
			xmax = sound[x];
		else if (sound[x] < xmin)
			xmin = sound[x];
	}

	ymax = pow(10.0, dB/20.0) / 2;  // convert dB to linear
	ymin = -ymax;

	sf = ( ymax - ymin ) / ( xmax - xmin );  // scale factor

	for (x = 0; x < samples; x++ )   //scale the samples
		sound[x] = sf * (sound[x] - xmin) + ymin;

	return;
}
/*
 * createPartial(tone, F, A, dur, sr)
 * create one partial (a sine wave) at 'F' hertz and 'A' amplitude
 */
void createPartial(double tone[], double F, double A, double dur, int sr)
	// tone[] -> array for the sound
	// F      -> frequency in Hertz
	// A      -> amplitude as proportion
	// dur    -> duration in seconds
	// sr     -> sampling rate
{
	int t,          // counter
		samples;    // duration of sound in samples
	double ph,      // counter for phase
		   phInc,   // phase increment
		   newamp;  // variable for the new waveform's amplitude

	ph = 0;                          // initialize phase to zero
	phInc = (2.0 * M_PI * F ) / sr;  // set phase increment
	samples = dur * sr;              // duration of sound in samples

	for (t = 0; t < samples; t++ )   // create the partial
	{
		newamp = A * sin(ph);        // calculate new amplitude
		tone[t] = tone[t] + newamp;  // add newamp to current wave
		ph = ph + phInc;             // increment the phase
	}

	return;
}
/*
 * copyToShort(output, input, dur, sr)
 * copy 'input' (which is a double) into 'output' (which is a short)
 */
void copyToShort(short output[], double input[], double dur, int sr)
	// output array of shorts
	// input array of doubles
	// duration of array in seconds
	// sampling rate
{
	int n,        // counter
		samples;  // duration of sound in samples

	samples = dur * sr;   // calculate the number of samples

	for (n = 0; n < samples; n++ )   //loop to copy the sound
		output[n] = input[n];

	return;
}



