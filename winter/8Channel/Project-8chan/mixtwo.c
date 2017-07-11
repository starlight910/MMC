#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sf.h>
#include <sfmisc.h>

#include "env.h"

static double mixTotalDuration ;
static int mixNFrames ;
static int mixChannelCount ;
static int mixSamplingRate ;
static double **mixBuffer ;

int getMixChannelCount(void)
{
	return mixChannelCount ;
}

double getMixTotalDuration(void)
{
	return mixTotalDuration ;
}

void mixAddS(short *input, int start, int samples, int channelNumber)
{
	static int fCounter ;
	double *pMixBuf ;

	fCounter++ ;

	if ( start + samples > mixNFrames ) {
		fprintf(stderr,
			"mixAddS[%d]: start(%d) + samples(%d) >= mixNFrames(%d)\n",
				fCounter, start, samples, mixNFrames) ;
		exit(EXIT_FAILURE) ;
	}

	if ( channelNumber > mixChannelCount || channelNumber < 0 ) {
		fprintf(stderr,"mixAddS[%d]: Bad channelNumber: %d\n",
				fCounter, channelNumber) ;
		exit(EXIT_FAILURE) ;
	}

	pMixBuf = mixBuffer[channelNumber] + start ;

	while ( samples-- )
		*pMixBuf++ += *input++ ;

	return ;
}

void mixSetup(double totalDuration, int sr, int nchan) 
{
	int i ;

	mixChannelCount = nchan ;
	mixSamplingRate = sr ;
	mixTotalDuration = totalDuration ;

	mixNFrames = mixTotalDuration * mixSamplingRate ;

	mixBuffer = (double **)Malloc(mixChannelCount * sizeof(double *));
	for ( i = 0 ; i < mixChannelCount ; i++ )
		mixBuffer[i] = (double *)Malloc(mixNFrames * sizeof(double)) ;

	return ;
}

void mixAdd(short *input, double st, double dur, int channelNumber)
{
	static int fCounter ;
	int start, samples ;
	double *pMixBuf ;

	fCounter++ ;

	if ( st + dur > mixTotalDuration ) {
		fprintf(stderr,"mixAdd[%d]: st(%g) + dur(%g) >= mixTotalDur(%g)\n",
				fCounter, st, dur, mixTotalDuration) ;
		exit(EXIT_FAILURE) ;
	}

	if ( channelNumber > mixChannelCount || channelNumber < 0 ) {
		fprintf(stderr,"mixAdd[%d]: bad channelNumber: %d\n",
				fCounter, channelNumber) ;
		exit(EXIT_FAILURE) ;
	}

	start = st * mixSamplingRate ;
	samples = dur * mixSamplingRate ;

	pMixBuf = mixBuffer[channelNumber] + start ;

	while ( samples-- )
		*pMixBuf++ += *input++ ;

	return ;
}

static void mixScale(void)
{
	double xmax, xmin, scale, *pd ;
	const double ymax = 32750, ymin = -32750 ;
	int i ;

	xmax = xmin = mixBuffer[0][0] ;
	for ( i = 0 ; i < mixChannelCount ; i++ ) {
		for ( pd = mixBuffer[i] ; pd < mixBuffer[i] + mixNFrames ; pd++ )
			if ( *pd > xmax ) xmax = *pd ;
			else if ( *pd < xmin ) xmin = *pd ;
	}

	scale = ( ymax - ymin ) / ( xmax - xmin ) ;

	if ( scale >= 1.0 ) 
		return ;

	fprintf(stderr,"\tmixScale: Attenuating by %5.2f dB ... ", 20*log10(scale));
	for ( i = 0 ; i < mixChannelCount ; i++ ) {
		pd = mixBuffer[i] ;
		for ( pd = mixBuffer[i] ; pd < mixBuffer[i] + mixNFrames ; pd++ )
			*pd = scale * ( *pd - xmin ) + ymin ;
	}
	fputs("Done\n", stderr) ;

	return ;
}

short *mixConvertTo16Bits(void)
{
	int i, j ;
	short *po, *output ;

	fputs("Staring mixConvert ... ", stderr) ;

	mixScale() ;

	po = output = (short *)Malloc(mixNFrames * mixChannelCount * sizeof(short));

	for ( i = 0 ; i < mixNFrames ; i++ ) {
		for ( j = 0 ; j < mixChannelCount ; j++ )
			*po++ = mixBuffer[j][i] ;
	}

	for ( i = 0 ; i < mixChannelCount ; i++ )
		Free(mixBuffer[i]) ;
	Free(mixBuffer) ;

	fputs("Done\n", stderr) ;

	return output ;
}



