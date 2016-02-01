#include "no_random.h"
#include <stdio.h>
#include <stdlib.h>

const static unsigned long long int MAX_SIZE = 1048576;

void print_help( const char *name )
{
	printf("%s options: \n",name);
	printf("  -h  : Prints this help.\n");
	printf("  -i  : Random integer\n");
	printf("  -u  : Random unsigned integer\n");
	printf("  -b  : Random booleen\n");
	printf("  -f  : Random float\n");
	printf("        Can be followed by an optional min and max values.\n\n");
	printf(" If none of these options are used. Then pipe mode is used.\n It's commands follow.");
	printf("  -s  : Number of outputs.\n");
	printf("  -t  : Type or size of the output. (Default=1)\n");
	printf("        K = kilobyte\n");
	printf("        M = megabyte\n");
	printf("        G = gigabyte\n");
	printf("        k = kilobit\n");
	printf("        m = megabit\n");
	printf("        g = gigabit\n");
	printf("      Or just specify the size in bytes.\n\n");
	printf(" Examples:\n");
	printf("  %s -i (Prints a random number)\n",name);
	printf("  %s -u (Prints a unsigned random number)\n",name);
	printf("  %s -b (Prints True, or False randomly)\n",name);
	printf("  %s -f (Prints a random float)\n",name);
	printf("  %s -f 10.0 15.0 (Prints a random float between 10 and 15)\n",name);
	printf("  %s -s 100 (outputs 100 bytes on std out)\n",name);
	printf("  %s -s 10 -t M (outputs 10 megabytes on std out)\n",name);
	printf("  %s -s 5 -t 1024 (outputs 5 kilobytes on std out)\n\n",name);
	return;
}

int main( int argc ,const char *argv[] )
{
	no_random rnd;
	unsigned long long int bytes = 16 ,multi = 1 ,sync = 0;
	int output = 1000;
	unsigned int unum = 0;
	float min = 0.0f ,max= 100.0f ,fcache = 0.0f;
	
	if( argc <= 1 )
	{
		print_help( argv[0] );
		return 0;
	}
	
	if( argc > 1 ) /* Yes I AM trolling you with that scope style. */
		for( int loop = 0;loop < argc;loop++ )
			if( argv[loop][0] == '-' )
			{
				if( argv[loop][1] == 'h' )
				{
					print_help( argv[0] );
					return 0;
				}
				if( argv[loop][1] == 's' )
					bytes = atoll( argv[loop+1] );
				if( argv[loop][1] == 't' )
				{
					if( argv[loop+1][0] == 'K' )
						multi = 1024;
					else if( argv[loop+1][0] == 'M' )
						multi = 1024*1024;
					else if( argv[loop+1][0] == 'G' )
						multi = (1024*1024)*1024;
					else if( argv[loop+1][0] == 'k' )
						multi = 128;
					else if( argv[loop+1][0] == 'm' )
						multi = 128*1024;
					else if( argv[loop+1][0] == 'g' )
						multi = (128*1024)*1024;
					else
						multi = atoll( argv[loop+1] );
				}
				if( argv[loop][1] == 'i' )
					output = 0;
				if( argv[loop][1] == 'u' )
					output = 1;
				if( argv[loop][1] == 'b' )
					output = 2;
				if( argv[loop][1] == 'f' )
				{
					output = 3;
					if( loop+1 < argc )
						min = atof(argv[loop+1]);
					if( loop+2 < argc )
						max = atof(argv[loop+2]);
					if( max < min )
					{
						fcache = min;
						min = max;
						max = fcache;
					}
				}
			}
	
	no_init_random(&rnd);
	switch(output)
	{
		case 0: // int
			output = no_random_int(&rnd);
			printf("%i\n",output);
			return 0;
			break;
		case 1: // uint
			unum = no_random_uint(&rnd);
			printf("%u\n",unum);
			return 0;
			break;
		case 2: // bool
			if( no_random_bool(&rnd) ) {
				printf("True\n");
			} else {
				printf("False\n");
			}
			return 0;
			break;
		case 3: // float
			min = no_random_f(min,max,&rnd);
			printf("%f\n",min);
			return 0;
			break;
	};
	
	for(unsigned long long int loop=0;loop < bytes;)
	{
		if( (bytes-loop) < NO_ONE_RANDOM_BUFFER ) {
			fwrite(&rnd.cache[0],(bytes-loop),1,stdout);
			loop = bytes;
		} else {
			if( fwrite(&rnd.cache[0],NO_ONE_RANDOM_BUFFER,1,stdout) != 1 )
			{
				loop = bytes;
				fprintf(stderr,"Broken pipe\n");
			}
			loop += NO_ONE_RANDOM_BUFFER;
			no_fill(NO_ONE_RANDOM_BUFFER,&rnd);
		}
	}
	return 0;
}
