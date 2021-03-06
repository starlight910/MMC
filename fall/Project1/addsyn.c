#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sf.h>
#include <sfmisc.h>

/*
 * addsyn(sData[], dur, sr, F, dB, partialF[], partialA[], nPartials)
 * routine for additive synthesis.  
 * adds together 'nPartials' of sine waves. 
 *
 * The frequency of each partial is given as a proportion in the
 * array 'partialF[]'
 * The amplitude of each partial is given as a proportion in the array
 * 'partialA[]'
 * 'F' = fundamental frequency in Hertz; 'dB' output amplitude in decibels.
 */
void addsyn(short sData[],	// array for the resulting sound
	double dur,				// duration of sound in seconds
	int sr,					// sampling rate
	double F,			// fundamental frequency in Hertz
	double dB,			// overall amplitude in dB
	double partialF[],	// list of partial frequencies (proportional)
	double partialA[],  // list of partial amplitudes (proportional)
//	double partialF2[], // list of partial frequencies 2
//	double partialA2[], // list of partial amplitudes 2
	int nPartials)
//	int nPartials2)		// number of partials (length of arrays)
{
	int n ;				// counter for partials
	double f ;			// variable for partial frequency
	double A ;			// variable for partial amplitude
	double nyquist ;	// set the nyquist frequency
	double *tone ;		// array to build the partials

	// declarations of functions called from addsyn()
	void createPartial(double tone[], double F, double A, double dur, int sr);
	void copyToShort(short output[], double input[], double dur, int sr);
	void scale(double sound[], double dur, int sr, double dB);

	nyquist = sr / 2 ;		// set the nyquist frequency

	// allocate memory to create additive synthesis tone
	tone = (double *)Malloc(dur * sr * sizeof(double)) ;

	for ( n = 0 ; n < nPartials ; n++ ) {	// loop to create partials

		f = F * partialF[n] ;		// calculate partial frequency
		if ( f >= nyquist )			// make sure frequency is less than nyquist
			break ;

		A = partialA[n] ;			// partial amplitude (proportional)

		createPartial(tone, f, A, dur, sr) ;		// create one partial
	}

	scale(tone, dur, sr, dB) ;		// scale values to desired dB
	copyToShort(sData, tone, dur, sr) ;	// copy doubles to shorts

	Free(tone) ;		// free the 'double' array

	return ;
}
/*
 * scale(data[], N, dB)
 * y[n] = ((ymax-ymin) / (xmax-xmin)) * ( x[n] - xmin ) + ymin 
 */
void scale(double sound[],	// array for the sound to be scaled
		double dur,			// duration of the sound in seconds
		int sr,				// sampling rate
		double dB)			// amplitude of sound in decibels
{
	double xmin, xmax ;		// current linear min/max values
	double ymax, ymin ;		// desired linear max/min values
	double sf ;				// scaling factor
	int x,					// counter
		samples ;			// duration of sound in samples


	samples = dur * sr ;	// calculate value for samples

	xmax = xmin = sound[0] ;		// set initial values for xmin/xmax
	for ( x = 0 ; x < samples ; x++ ) { // find min/max
		if ( sound[x] > xmax ) 
			xmax = sound[x] ;
		else if ( sound[x] < xmin ) 
			xmin = sound[x] ;
	}

	ymax = pow(10.0, dB/20.0) / 2 ;		// convert dB to linear
	ymin = -ymax ;

	sf = ( ymax - ymin ) / ( xmax - xmin ) ;	// scale factor

	for ( x = 0 ; x < samples ; x++ )			// scale the samples
		sound[x] = sf * ( sound[x] - xmin ) + ymin ;

	return ;
}
/*
 * createPartial(tone, F, A, dur, sr)
 * create one partial (a sine wave) at 'F' hertz and 'A' amplitude
 */
void createPartial(double tone[],	// array for the sound
		double F,					// frequency in Hertz
		double A,					// amplitude as proportion
		double dur,					// duration in seconds
		int sr)						// sampling rate
{
	int t,				// counter
		samples ;		// duration of sound in samples
	double ph,			// counter for phase
		   phInc, 		// phase increment
		   newamp ;		// variable for the new waveform's amplitude

	ph = 0 ;							// initialize phase to zero
	phInc = ( 2 * M_PI * F ) / sr ;	    // set phase increment
	samples = dur * sr ;				// duration of sound in samples

	for ( t = 0 ; t < samples ; t++ )   // create the partial
	{
		newamp = A * sin(ph) ;			// calculate new amplitude
		tone[t] = tone[t] + newamp ;	// add newamp to current wave
		ph = ph + phInc ;				// increment the phase
	}

	return ;
}
/*
 * copyToShort(output, input, dur, sr)
 * copy 'input' (which is a double) into 'output' (which is a short)
 */
void copyToShort(
		short output[],		// output array of shorts
		double input[],		// input array of doubles
		double dur,			// duration of array in seconds
		int sr)				// sampling rate
{
	int n,			// counter
		samples ;	// duration of sound in samples

	samples = dur * sr ;	// calculate the number of samples

	for ( n = 0 ; n < samples ; n++ )	// loop to copy the sound
		output[n] = input[n] ;

	return ;
}
