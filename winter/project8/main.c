#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sf.h>
#include<sfmisc.h>
#include<string.h>

int main() 
{

	


	short *drumLoop ;



	int nchan = 2 ;
	int sr = 44100 ;

	int dB = 70;

	int BPM = 100 ;

	double dur = 10 ;
	int i ;

	void conc(short output[], short input[], double st, double dur, int sr) ;
	short *sequence(int BPM, double dur, int nchan, int sr, int dB) ;


	int samples = dur * nchan * sr ;

	drumLoop = (short *)Malloc(samples * sizeof(short)) ;
	memset(drumLoop, 0, dur * nchan * sr * sizeof(short)) ;

	//drumLoop = (short *)Malloc(samples * sizeof(short)) ;

	for(i = 0; i < samples; i++) 
	{

		drumLoop = sequence(BPM, dur, nchan, sr, dB) ;



	
	}

	free(drumLoop) ;


	printf("G-UNIT!");
	sfsave("drumloop.wav", drumLoop, dur, sr, nchan) ;

	exit(EXIT_SUCCESS) ;

return 0;
}
