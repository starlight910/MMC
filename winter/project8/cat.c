#include <stdio.h>

void conc(short output[], short input[], double st, double dur, int sr)
{
	int start, length, n, i ;

	fprintf(stderr, "st = %f  dur = %f\n", st, dur) ;

	start = st * sr ; // start time of tone in samples
	length = dur * sr ; //duration of tone in samples
//using 2 indexes (i and n), copy 'intput' into 'output'
	for(n = start, i = 0; n < start + length; n++, i++)
		output[n] = input[i] ;
	return;
}
