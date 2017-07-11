#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

void comb(short *xdata, int samples, int sr, int ms, double g)
{
	short *ydata ;
	int i, D ;

	// translate delay from milliseconds to samples
	D = (ms/1000.0) * sr ;

	// allocate memory for output
	ydata = (short *)Malloc(samples * sizeof(short)) ;

	for ( i = 0 ; i < D ; i++ )	// copy the first 'D' samples
		ydata[i] = xdata[i] ;

	for ( i = D ; i < samples ; i++ )	// apply a comb filter
		ydata[i] = xdata[i] + g * ydata[i-D] ;

	for ( i = 0 ; i < samples ; i++ )	// copy output to input
		xdata[i] = ydata[i] ;

	Free(ydata) ;

	return ;
}
