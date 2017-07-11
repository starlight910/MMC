#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>


int main (int argc, char *argv[])
{
	int dataSizeInBytes,
		samplingRate = 44100,
		channelCount = 1;
	double f,                // frequency
		   d,                // duration
		   A,                // amplitude
		   phase,
		   decay,
		   phaseInc;
	int samples;
	short *buffer;
	int t,counter,q,direction;
	decay = 1;
	if ( argc != 4 ) {
		printf("usage: %s frequency duration amplitude\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f = atof(argv[1]);
	d = atof(argv[2]);
	A = atof(argv[3]);

	fprintf(stderr,"\tfrequency = %f\n", f);
	fprintf(stderr,"\t duration = %f\n", d);
	fprintf(stderr,"\tamplitude = %f\n", A);

	samples = d * samplingRate ;
	dataSizeInBytes = samples * channelCount * sizeof(short);

	buffer = (short *)Malloc(dataSizeInBytes) ; 

	phaseInc = 2.0 * M_PI * f / samplingRate ;
	phase = 0 ;
	counter = 0;
	q = 0;
	direction = 1;
	void delayy(short buffer[], int t,double A, double phase, double decay );
	for ( t = 0 ; t < samples ; t++) {
		counter++;
		if(q == 0){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 5;
		}
		if(q == 1){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 5;
		}
		if(q == 2){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 4;
		}
		if(q == 3){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 5;
		}
		if(q == 4){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 5;
		}
		if(q == 5){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 1;
		}
		if(q == 6){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 1;
		}
		if(q == 7){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 2;
		}
		if(q == 8){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 1;
		}
		if(q == 9){
			delayy(buffer,t,A,phase,decay);
			phase += phaseInc * 1;
		}
		if(counter > samplingRate/8){
			counter = 0;
			decay = 1;
			if(q == 0)
				direction = 1;
			if(q == 9)
				direction = 0;
			if(direction == 1)
				q++;
			if(direction == 0)
				q--;
		}
		if(counter > samplingRate/16)
			decay = 1/8;
	}


	sfsave("arpsinetest.wav", buffer, d, samplingRate, channelCount);

	exit(EXIT_SUCCESS) ;
}

void delayy(short buffer[], int t,double A, double phase, double decay ){

	buffer[t] = (short)(A * decay * sin( phase ));

}










