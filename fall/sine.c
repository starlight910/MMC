//include statements

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// The main program

int main(int argc, char *argv[])
{
	int dataSizeInBytes,
		samplingRate = 44100,
		channelCount = 1;

// The variables for our particular sound

	double f,
		   d,
		   A,
		   phase,
		   phaseInc ;
	int samples;
	short *buffer ;
	int t ;

// The beginning of the program commands

	if ( argc != 4 ) {
		printf("Usage: %s frequency duration amplitude\n", argv[0]);
	exit(EXIT_FAILURE);
	}

	f = atof(argv[1]);
	d = atof(argv[2]);
	A = atof(argv[3]);

	fprintf(stderr,"\tfrequency = %f\n", f) ;
	fprintf(stderr,"\t duration = %f\n", d) ;
	fprintf(stderr,"\tamplitude = %f\n", A) ;

	samples = d * samplingRate ;
	dataSizeInBytes = samples * channelCount * sizeof(short) ;

	buffer = (short *)Malloc(dataSizeInBytes) ;

	phaseInc = 2.0 * M_PI * f / samplingRate ;

	phase = 0 ;
	for ( t = 0 ; t < samples ; t++ ) {
		buffer[t] = (short)(A * sin( phase ) ) ;
		phase += phaseInc ;
	}
	
// write the sound out to the file

	sfsave("sine.wav", buffer, d, samplingRate, channelCount);

	exit(EXIT_SUCCESS) ;
}



