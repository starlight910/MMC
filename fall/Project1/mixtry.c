#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

short *mix(short *part1sound, double dur1, short *part2sound, double dur2, int sr)
{
	short part1sound;
	short part2sound;
	short output;
	double dur1;
	double dur2;
	double maxdur;
	double mindur;
	int sr;

	{
		if(dur1 > dur2)
		{
			maxdur = dur1; mindur = dur2;
		else
			maxdur = dur2; mindur = dur1;
		}

		output
