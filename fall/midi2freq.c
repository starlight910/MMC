/* listing 1.2. Calculate frequency of a MIDI Note number */
#include <stdio.h>
#include <math.h>

int main()
{
	double semitone_ratio;
	double c0; /*for frequency of MIDI Note 0 */
	double c5; /*for frequency of Middle C */
	double frequency; /* . . . which we want to find, */
	int midinote; /* . . . given this note */

	/* Calculate required numbers */

	semitone_ratio = pow(2, 1/12.0); /* approx. 1.0594631 */
	/*find Middle C, three semitones above low A = 220 */
	c5 = 220.0 * pow(semitone_ratio, 3);
	/* MIDI Note 0 is C, 5 octaves below Middle C */
	c0 = c5 * pow(0.5, 5);

	/*calculate a frequency for a given MIDI Note Number */
	midinote = 73; /* C# above A = 440 */
	frequency = c0 * pow(semitone_ratio, midinote);

	printf("MIDI Note %d has frequencu %f\n", midinote, frequency);

	return 0;
}

