#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sf.h>
#include<sfmisc.h>
#include<time.h>

short sequence(int BPM, double dur, int nchan, int sr, int dB) 
{
	
	short *sound;
	int samples ;

	int nBeats ;

	double BPS ;
	double step ;



	short *final ;

	double st = 0 ;

	BPS = BPM / 60.0 ;
	samples = dur * nchan * sr ;
	nBeats = BPS * dur ;
	step = BPS * sr ;


	void conc(short output[], short input[], double st, double dur, int sr) ;
	
	short *patch1(int dB, int sr);
	short *patch2(int dB, int sr);
	short *patch3(int dB, int sr);
	short *patch4(int dB, int sr);
	short *patch5(int dB, int sr);
	short *patch6(int dB, int sr);
	short *patch7(int dB, int sr);
	short *patch8(int dB, int sr);
	short *patch9(int dB, int sr);

	int plinko1(int random);
	int plinko2(int random);
	int plinko3(int random);
	int plinko4(int random);
	int plinko5(int random);
	int plinko6(int random);
	int plinko7(int random);
	int plinko8(int random);
	int plinko9(int random);
	
	st = 0.0 ;
	int i = 0 ;

	srand(time(NULL)) ;

	for(i = 0; i < nBeats; i++) {

		int random = rand() % 8 ;

		switch (random) {
			case 1:
				sound = patch1(dB, sr) ;
				break ;
			case 2:
				sound = patch2(dB, sr) ;
				break ;
			case 3:
				sound = patch3(dB, sr) ;
				break ;
			case 4:
				sound = patch4(dB, sr) ;
				break ;
			case 5:
				sound = patch5(dB, sr) ;
				break ;
			case 6:
				sound = patch6(dB, sr) ;
				break ;
			case 7:
				sound = patch7(dB, sr) ;
				break ;
			case 8:
				sound = patch8(dB, sr) ;
				break ;
			case 9:
				sound = patch9(dB, sr) ;
				break ;

			}

		conc(final, sound, st, dur, sr) ;

		switch (random) {
			case 1:
				random = plinko1(random) ;
				break ;
			case 2:
				random = plinko2(random) ;
				break ;
			case 3:
				random = plinko3(random) ;
				break ;
			case 4:
				random = plinko4(random) ;
				break ;
			case 5:
				random = plinko5(random) ;
				break ;
			case 6:
				random = plinko6(random) ;
				break ;
			case 7:
				random = plinko7(random) ;
				break ;
			case 8:
				random = plinko8(random) ;
				break ;
			case 9:
				random = plinko9(random) ;
				break ;



			}

		st += step ;
	}
return 1;
}
