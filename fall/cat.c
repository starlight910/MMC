void concatenate(short output[], short input[], double st, double dur, int sr)
{
	int start ;
	int length ;
	int n ;
	int i ;

	start = st * sr ;    // start time of tone is samples
	length = dur * sr ;  // duration of tone is samples

	// using 2 indexes (i and n), copy 'input' into 'output'
	for( n = start, i = 0 ; n < start + length ; n++, i++ )
		output[n] = input[i] ;

			return;
}
