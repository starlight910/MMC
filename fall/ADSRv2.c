#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <time.h> 
#include <sf.h> 
#include <sfmisc.h>

int main()
{
	int sr = 44100 ; //sampling rate
	int nchan = 1 ;  // channel chount
	short *sound ;
	short *sound2 ;
	short *newSound ;
	double dur = 10 ;    // Time
	double F = 440;
	double dB = 96;
	int nPartials = 8;
	double partialF[] = {1.0, 10.0/8.0, 12.0/8.0, 14.5/8.0, 2.0, 18.0/8.0, 20.0/8.0, 22.5/8.0 };
	double partialA[] = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3} ;
	// 1, 1/1, 3, 1/3, 5, 1/5, 7, 1/7, etc... Square wave
	// 1/1, 1/2, 1/3, 1/4, 1/5, etc... Sawtooth wave


	int N = 6 ;
	double T[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0}; //ADSR Time
	double A[] = {0.0, 1.0, 0.6, 0.3, 1.0, 0.0}; //ADSR Amplitude
	int flag = 0 ;
	int nSequence = 2 ;

	int samples ;
	int samples2 ;
	int dataSizeInBytes ;
	int dataSizeInBytes2 ;

	void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials);
	void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag);

	samples = dur * nchan * sr ;
	dataSizeInBytes = samples * nchan * sizeof(short) ;
	
	samples2 = dur * nchan * sr ;
	dataSizeInBytes2 = samples * nchan * sizeof(short) ;
	
	sound = (short *)Malloc(dataSizeInBytes) ;

    sound2 = (short *)Malloc(dataSizeInBytes) ;
	newSound = (short *)Malloc(dataSizeInBytes2) ;

	addsyn(sound, dur, sr, F, dB, partialF, partialA, nPartials) ;

    adsr2(sound, dur, sr, T, A, N, flag);
	adsr2(sound2, dur, sr, T, A, N, flag);

	sfsave("ADSRv2.wav", sound,dur, sr, nchan) ;
	exit(EXIT_SUCCESS);
}
void addsyn(short sData[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) 
{
	int n ;
	double f;
	double A;
	double nyquist;
	double *tone;
	
	void createPartial(double tone[], double F,double A, double dur, int sr);
	void copyToShort(short output[], double input[], double dur, int sr);
	void scale(double sound[], double dur, int sr, double dB);
	
	nyquist = sr / 2;
	
	tone = (double *)Malloc(dur * sr * sizeof(double));

	for (n = 0; n < nPartials ; n++)
	{
		f = F * partialF[n] ;
		
		if ( f >= nyquist )
			break ;
	
		A = partialA[n] ;
		createPartial(tone, f, A, dur,sr) ;
	}
	
	scale(tone, dur, sr, dB) ;
	copyToShort(sData, tone, dur, sr);
	
	Free(tone) ;

	return;
}

void scale(double sound[], double dur, int sr, double dB)
{ 
	double xmin, xmax;
	double ymax, ymin;
	double sf;
	int x;
	int samples;
	
	samples = dur * sr;

	xmax = xmin = sound[0];
	for(x = 0; x < samples; x++)
	{
		if(sound[0] > xmax)
			xmax = sound[x];
		else if(sound[x] < xmin)
			xmin = sound[x];
	}

	ymax = pow(10.0, dB /20.0) /2 ;
	ymin = -ymax;

	sf = (ymax - ymin) / (xmax - xmin) ;

	for(x = 0; x < samples; x++)
		sound[x] = sf * (sound[x] - xmin) + ymin ;
	
	return;
}

void createPartial(double tone[], double F, double A, double dur, int sr)
{
	int t;
	int	samples ;
	double ph;
	double phInc;
	double newamp;
	
	ph = 0;
	phInc = (2.0 * M_PI * F)/ sr;
	samples = dur * sr ;
	
	for ( t=0; t < samples; t++)
	{
		newamp = A * sin(ph) ;
		tone[t] = tone[t] + newamp;
		ph = ph + phInc;
	}
	return;
}

void copyToShort(short output[], double input[], double dur, int sr)
{
	int n,
	samples ;
	samples = dur * sr;
	
	for ( n = 0 ; n < samples ; n++)
		output[n] = input[n];
	return;
}
