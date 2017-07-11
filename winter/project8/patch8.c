#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sf.h>
#include<sfmisc.h>

// declarate external functions

void addsyn(short sound, double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials);
void conc(short output[], short input[], double st, double dur, int sr);


short patch8(int dB, int sr)
{

	int i ;

	double F = 0 ;
	

	short *sound ;
	double dur = 1 ;
	

	int nPartials = 3 ;
	double partialF[] = {1.0, 2.0, 4.0} ;
	double partialA[] = {1.0, 1.0/2.0, 1.0/4.0} ;

	int nPoints = 3 ;
	double T[] = {0.0, 0.5, 1.0} ;
	double A[] = {0.0, 1.0, 0.0};
	int flag = 0 ;

	sound = (short *)Malloc(dur * sizeof(short)) ;

int	samples = dur * sr ;

	for(i=0; i < samples; i++)
	{
		addsyn(sound, dur, sr, F, dB, partialF, partialA,
				nPartials) ;
		adsr2(sound, dur, sr, T, A, nPoints, flag) ;

	}

	return sound ;

	Free(sound) ;

}	

