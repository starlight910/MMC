#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

//     /opt/compmusic/2012/winter/filter/*

#include "comb.h"

short *readSound(char *soundfile, 
		int *samples, int *samplingRate, int *nchan)
{
	sfheader sf ;
	short *data ;

	fprintf(stderr,"\tReading '%s' ... ", soundfile) ;

	sfopen(soundfile, &sf, "r", 0) ;
	*samplingRate = sf.samplingRate ;
	*samples = sf.dataSize / sizeof(short) / sf.channelCount ;
	*nchan = sf.channelCount ;
	data = (short *)Malloc(sf.dataSize) ;
	sfread(&sf, data, sf.dataSize) ;
	sfclose(&sf) ;

	fprintf(stderr,"Done\n") ;

	return data ;
}


void movingAverageFilter(short *data, int samples)
{
	int i ;

	for ( i = 1 ; i < samples ; i++ )	// moving average filter
		data[i] = 0.5 * data[i] + 0.5 * data[i-1] ;

	return ;
}

int main(void)
{
	char *soundfile = "/opt/compmusic/voice.wav" ;
	short *data ;
	int samples, sr, nchan ;
	double duration ;
	double gain = 0.7 ;
	int delayInMS = 10 ;

	data = readSound(soundfile, &samples, &sr, &nchan) ;

	duration = samples / (double)sr ;

	/*
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	movingAverageFilter(data, samples) ;
	*/

	comb(data, samples, sr, delayInMS, gain) ;

	sfsave("filtered.wav", data, duration, sr, nchan) ;

	return 0 ;
}
