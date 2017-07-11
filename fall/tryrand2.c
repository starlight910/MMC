#include <stdio.h>
#include <stdlib.h>

int lcg(int seed, int a, int c, int m)
{	
	int a = 1103515245 ;	// values of a,c,m from glib (GCC)
	int c = 12345 ;
	int m = 2147483648 ;	// 2^31 
	
	printf("%d  %d  %d  %d  \n", seed, a, c, m);
	seed = ( a * seed + c ) % m ;

    return seed ;
}

int main(int argc, char *argv[])
{
   int i, j, seed, a, c, m, N ;

   N = 20 ; // this could also be set to m
   printf("%d argc \n", argc);

   if (argc == 5)
   {
   a = atoi(argv[2]);
   c = atoi(argv[3]);
   m = atoi(argv[4]);
   seed = atoi(argv[1]);
   }
   else if (argc == 2);
   {
   seed = atoi(argv[1]);
   a = 5 ; c = 1 ; m = 19 ;
   }
   
   printf("%d  %d  %d  %d  \n", seed, a, c, m);
   printf("\n");
   // try every seed

   for (j=0; j<m; j++) 
   {
   seed = j;
   for ( i = 0 ; i < N ; i++ )
      {
		  printf(" %d ", seed) ;
		  seed = lcg(seed, a, c, m) ;
	  }
   printf("\n");
   
   }
   printf("\n") ;

   return 0 ;
 }                         
