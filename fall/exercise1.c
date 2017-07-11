#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int i;
	double nSide = 8;
	double en = 1/nSide;
	double t ;

	for(i = 0; i<nSide; i++)
	{
		t += (en * log(en)) * -1;

		printf("%f\n", t);
	}
	return t;
}

//void ex2(int i, double nSide, double en, double t)
//{
//	int i;
//	int de = 5;
//	double x;
//
//	for(i = 0, x = 1.0; i<de; i++, x*=0.1)
//	{
//		printf("%d,%f\n", i, x);
//	}
//	return 1
//}

