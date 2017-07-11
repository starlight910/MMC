extern void mixSetup(double totalDuration, int sr, int nchan)  ;
extern void mixAdd(short *input, double st, double dur, int channelNumber) ;
extern void mixAddS(short *input, int st, int samples, int channelNumber) ;
extern short *mixConvertTo16Bits(void) ;
extern void mixPan(short *input, double st, double dur, int sr, 
		double tList[], int cList[], int N) ;
extern int getMixChannelCount(void) ;
extern double getMixTotalDuration(void) ;
