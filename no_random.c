#include "no_random.h"
#include <math.h>
#include <limits.h>
#include <string.h>

#if defined(NO_ONE_HASH_CRC32)
static const no_hash32 no_one_crc32tble[256] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};
#endif

no_float threshhold_no_fl( no_float inFlt )
{
	#ifndef NO_ONE_NO_LONG_DOUBLE
	if( inFlt >= 0.999999999999999 ) return 1.0;
	if( inFlt <= 0.0000000000000001 ) return 0.0;
	#else
	if( inFlt >= 0.99999999999999999L ) return 1.0L;
	if( inFlt <= 0.000000000000000001L ) return 0.0L;
	#endif
	return inFlt;
}

float no_threshhold_float_zo( float inFlt )
{
	if( inFlt >= 0.999999f ) return 1.0f;
	if( inFlt <= 0.0000001f ) return 0.0f;
	return inFlt;
}

double no_threshhold_double_zo( double inFlt )
{
	if( inFlt >= 0.999999999999999 ) return 1.0;
	if( inFlt <= 0.0000000000000001 ) return 0.0;
	return inFlt;
}

#ifndef NO_ONE_NO_LONG_DOUBLE
long double no_threshhold_ldouble_zo( long double inFlt )
{
	if( inFlt >= 0.99999999999999999L ) return 1.0L;
	if( inFlt <= 0.000000000000000001L ) return 0.0L;
	return inFlt;
}
#endif

float no_threshhold_float_noo( float inFlt )
{
	if( inFlt >=  0.999999f ) return 1.0f;
	if( inFlt <= -0.999999f ) return -1.0f;
	if( inFlt <= 0.0000001f && inFlt >= -0.0000001f ) return 0.0f;
	return inFlt;
}

double no_threshhold_double_noo( double inFlt )
{
	if( inFlt >=  0.999999999999999 ) return 1.0;
	if( inFlt <= -0.999999999999999 ) return -1.0;
	if( inFlt <= 0.0000000000000001 && inFlt >= -0.0000000000000001 ) return 0.0;
	return inFlt;
}

#ifndef NO_ONE_NO_LONG_DOUBLE
long double no_threshhold_ldouble_noo( long double inFlt )
{
	if( inFlt >=  0.99999999999999999L ) return 1.0L;
	if( inFlt <= -0.99999999999999999L ) return -1.0L;
	if( inFlt <= 0.000000000000000001L && inFlt >= -0.000000000000000001L ) return 0.0L;
	return inFlt;
}
#endif

/* Windows */
#if defined(_WIN32)
int time_eo()
{
	FILETIME tm1 ,tm2;
	ULONGLONG num1 = 0 ,num2 = 0;
	#if defined(NTDDI_WIN8) && NTDDI_VERSION >= NTDDI_WIN8
	/* Windows 8, Windows Server 2012 and later. */
	GetSystemTimePreciseAsFileTime( &tm1 );
	GetSystemTimePreciseAsFileTime( &tm2 );
	#else
	/* Windows 2000 and later. */
	GetSystemTimeAsFileTime( &tm1 );
	GetSystemTimeAsFileTime( &tm2 );
	#endif
	num1 = ((ULONGLONG)tm1.dwHighDateTime << 32) | (ULONGLONG)tm1.dwLowDateTime;
	num2 = ((ULONGLONG)tm2.dwHighDateTime << 32) | (ULONGLONG)tm2.dwLowDateTime;
	return (num1 ^ num2) & 1;
}

/*  HP-UX and Solaris */
#elif (defined(__hpux) || defined(hpux)) || ((defined(__sun__) || defined(__sun) || defined(sun)) && (defined(__SVR4) || defined(__svr4__)))
int time_eo()
{
	hrtime_t num1 = gethrtime();
	hrtime_t num2 = gethrtime();
	return (int)((num1 ^ num2) & 1);
}

/* Apple */
#elif defined(__MACH__) && defined(__APPLE__)
int time_eo()
{
	uint64_t num1 = mach_absolute_time();
	uint64_t num2 = mach_absolute_time();
	return (int)((num1 ^ num2) & 1);
}

/* General posix */
#elif defined(_POSIX_VERSION)
int time_eo()
{
	long int num1 = -1, num2 = -1;
	#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0) && !defined(NO_ONE_SKIP_POSIX)
	{
		struct timespec ts1 ,ts2;
		#if defined(CLOCK_MONOTONIC)
		const clockid_t id = CLOCK_MONOTONIC;
		#elif defined(CLOCK_REALTIME)
		const clockid_t id = CLOCK_REALTIME;
		#elif defined(CLOCK_MONOTONIC_PRECISE)
		const clockid_t id = CLOCK_MONOTONIC_PRECISE;
		#elif defined(CLOCK_MONOTONIC_RAW)
		const clockid_t id = CLOCK_MONOTONIC_RAW;
		#elif defined(CLOCK_HIGHRES)
		const clockid_t id = CLOCK_HIGHRES;
		#else
		# error "Failed to find a suitable clock id. Define NO_ONE_SKIP_POSIX, and recompile."
		#endif

		num1 = clock_gettime( id, &ts1 );
		num2 = clock_gettime( id, &ts2 );
		
		if( num1 != -1 )
		{
			num1 = ts1.tv_nsec;
		}
		if( num2 != -1 )
		{
			num2 = ts2.tv_nsec;
		}
		
		if( (num1 != -1) && (num2 != -1)  ) 
		{
			return (int)((num1 ^ num2) & 1);
		}
	}
	#endif /* _POSIX_TIMERS */
	/* No alternative, use gettimeofday(). Might not work correctly. */
	struct timeval tm1 ,tm2;
	gettimeofday( &tm1, 0 );
	gettimeofday( &tm2, 0 );
	num1 = (long int)tm1.tv_usec;
	num2 = (long int)tm2.tv_usec;
	return (int)((num1 ^ num2) & 1);
}
#else
# error "Could not implement time_eo() function."
#endif

#if defined(NO_ONE_HASH_ONLY_PROTO)
void no_hash_scramble(char *);
#endif

#if defined(NO_ONE_HASH_CRC32)
void no_hash_scramble(char *data_in)
{
	no_hash32 oHash = (no_hash32)~0 ,*poi = (no_hash32 *)data_in;
	int off = 0;
	for( int loop = 0;loop < NO_ONE_RANDOM_BUFFER; )
	{
		oHash = ( oHash >> 8 ) ^ no_one_crc32tble[(oHash ^ data_in[loop++]) & 0xFF];
		oHash = ( oHash >> 8 ) ^ no_one_crc32tble[(oHash ^ data_in[loop++]) & 0xFF];
		oHash = ( oHash >> 8 ) ^ no_one_crc32tble[(oHash ^ data_in[loop++]) & 0xFF];
		oHash = ( oHash >> 8 ) ^ no_one_crc32tble[(oHash ^ data_in[loop++]) & 0xFF];
		poi[off++] ^= ~oHash;
	}
	
	return;
}
#endif

#if defined(NO_ONE_HASH_FNV1A32)
const no_hash32 no_prime = 0x01000193;
const no_hash32 no_seed  = 0x811C9DC5;
/// hash a single byte
void no_hash_scramble(char *data_in)
{
	no_hash32 oHash = *((no_hash32 *)data_in);
	int off = 0;
	for( int loop = 0;loop < NO_ONE_RANDOM_BUFFER; )
	{
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
	}
	return;
}
#endif

#if defined(NO_ONE_HASH_FNV1A64)
const no_hash64 no_prime = 0x00000100000001B3;
const no_hash64 no_seed  = 0xCBF29CE484222325;
/// hash a single byte
void no_hash_scramble(char *data_in)
{
	no_hash64 oHash = *((no_hash64 *)data_in);
	int off = 0;
	for( int loop = 0;loop < NO_ONE_RANDOM_BUFFER; )
	{
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
		oHash = (data_in[loop++] ^ oHash) * no_prime;
	}
	return;
}
#endif

#if defined(NO_ONE_HASH_MURMUR3_32)

#define NO_ROLL_LEFT(x,r) ((x << r) | (x >> (32 - r)))

#define NO_FMIX( x ) \
x ^= x >> 16; \
x *= 0x85EBCA6B; \
x ^= x >> 13; \
x *= 0xC2B2AE35; \
x ^= x >> 16;

void no_hash_scramble(char *data_in)
{
	const no_uint8 *data = (const no_uint8*)data_in;
	const int nblocks = NO_ONE_RANDOM_BUFFER / 4;
	
	no_hash32 h1 = *((no_hash32 *)data_in) ,cache = 0;
	const no_hash32 c1 = 0xCC9E2D51;
	const no_hash32 c2 = 0x1B873593;
	
	no_hash32 *blocks = (no_hash32 *)(data + nblocks*4);
	no_uint8 *tail = 0;
	no_hash32 k1 = 0;
	
	for(int i = -nblocks; i; i++)
	{
		no_hash32 k1 = blocks[i];
		
		k1 *= c1;
		k1 = NO_ROLL_LEFT(k1,15);
		k1 *= c2;
		
		h1 ^= k1;
		h1 = NO_ROLL_LEFT(h1,13); 
		h1 = h1*5+0xE6546B64;
		
		/* Tail for each block out */
		cache = h1;
		tail = (no_uint8*)(data + i*4);
		k1 = 0;
		switch(NO_ONE_RANDOM_BUFFER & 3)
		{
			case 3: k1 ^= tail[2] << 16;
			case 2: k1 ^= tail[1] << 8;
			case 1: k1 ^= tail[0];
			k1 *= c1; k1 = NO_ROLL_LEFT(k1,15); k1 *= c2; h1 ^= k1;
		};
		/* Skip xor of size, that would introduce a pattern. */
		
		NO_FMIX(h1);
		blocks[i] = h1;
		h1 = cache;
	}
	
	return;
}
#endif

#if defined(NO_ONE_HASH_MURMUR3_128)

#define NO_ROLL_LEFT(x,r) ((x << r) | (x >> (64 - r)))

#define NO_FMIX( x ) \
x ^= x >> 33; \
x *= 0xFF51AFD7ED558CCDULL; \
x ^= x >> 33; \
x *= 0xC4CEB9FE1A85EC53ULL; \
x ^= x >> 33; \

void no_hash_scramble(char *data_in)
{
	const no_uint8 *data = (const no_uint8*)data_in;
	const int nblocks = NO_ONE_RANDOM_BUFFER / 16;
	
	no_hash64 h1 = *((no_hash32 *)data_in);
	no_hash64 h2 = *((no_hash32 *)data_in + (NO_ONE_RANDOM_BUFFER/2) );
	no_hash64 cache1 = 0;
	no_hash64 cache2 = 0;
	
	const no_hash64 c1 = 0x87C37B91114253D5ULL;
	const no_hash64 c2 = 0x4CF5AD432745937FULL;
	
	no_uint8  *tail   = (no_uint8*)(data + nblocks*16);
	no_hash64 *blocks = (no_hash64 *)(data);
	no_hash64 k1 = 0;
	no_hash64 k2 = 0;
	
	for(int i = 0; i < nblocks; i++)
	{
		k1 = blocks[i*2  ];
		k2 = blocks[i*2+1];
		
		k1 *= c1; k1  = NO_ROLL_LEFT(k1,31); k1 *= c2; h1 ^= k1;
		
		h1 = NO_ROLL_LEFT(h1,27); h1 += h2; h1 = h1*5+0x52DCE729;
		
		k2 *= c2; k2  = NO_ROLL_LEFT(k2,33); k2 *= c1; h2 ^= k2;
		
		h2 = NO_ROLL_LEFT(h2,31); h2 += h1; h2 = h2*5+0x38495AB5;
		
		cache1 = h1;
		cache2 = h2;
		
		/* Tail for each block out */
		tail = (no_uint8*)(data + i*16);
		
		k1 = 0;
		k2 = 0;
		switch(NO_ONE_RANDOM_BUFFER & 15)
		{
			case 15: k2 ^= ((no_hash64)tail[14]) << 48;
			case 14: k2 ^= ((no_hash64)tail[13]) << 40;
			case 13: k2 ^= ((no_hash64)tail[12]) << 32;
			case 12: k2 ^= ((no_hash64)tail[11]) << 24;
			case 11: k2 ^= ((no_hash64)tail[10]) << 16;
			case 10: k2 ^= ((no_hash64)tail[ 9]) << 8;
			case  9: k2 ^= ((no_hash64)tail[ 8]) << 0;
			k2 *= c2; k2  = NO_ROLL_LEFT(k2,33); k2 *= c1; h2 ^= k2;
			
			case  8: k1 ^= ((no_hash64)tail[ 7]) << 56;
			case  7: k1 ^= ((no_hash64)tail[ 6]) << 48;
			case  6: k1 ^= ((no_hash64)tail[ 5]) << 40;
			case  5: k1 ^= ((no_hash64)tail[ 4]) << 32;
			case  4: k1 ^= ((no_hash64)tail[ 3]) << 24;
			case  3: k1 ^= ((no_hash64)tail[ 2]) << 16;
			case  2: k1 ^= ((no_hash64)tail[ 1]) << 8;
			case  1: k1 ^= ((no_hash64)tail[ 0]);
			k1 *= c1; k1  = NO_ROLL_LEFT(k1,31); k1 *= c2; h1 ^= k1;
		};
		
		/* Skip xor of size, that would introduce a pattern. */
		
		h1 += h2;
		h2 += h1;
		
		NO_FMIX(h1);
		NO_FMIX(h2);
		
		h1 += h2;
		h2 += h1;
		blocks[i*2  ] = h1;
		blocks[i*2+1] = h2;
		h1 = cache1;
		h2 = cache2;
	}
	
	return;
}
#endif

/* End locals  */

void no_fill( int bCnt ,no_random *outRD )
{
	for( int sync=0;sync < bCnt;sync++ )
	{
		outRD->cache[sync] = outRD->cache[sync] ^  (char)no_whitened_bit();
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<1;
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<2;
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<3;
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<4;
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<5;
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<6;
		outRD->cache[sync] = outRD->cache[sync] ^ ((char)no_whitened_bit())<<7;
	}
	/* Remove bias.
	 * This also "bleeds" your entropy into the pool when you are doing a short fill.
	 */
	no_hash_scramble( outRD->cache );
	return;
}

int no_whitened_bit()
{
	char flags = ((char)time_eo()) | (((char)time_eo())<<1) ;
	while(1)
	{
		switch( flags )
		{
			case 0:
				break;
			case 1:
				return 0;
				break;
			case 2:
				return 1;
				break;
		};
		flags = ((char)time_eo()) | (((char)time_eo())<<1) ;
	}
	return 1;
}

void no_init_random( no_random *outRD )
{
	if( no_whitened_bit() ) /* Doesn't do much, but why not */
	{
		memset( outRD->cache ,0xAA,NO_ONE_RANDOM_BUFFER );
	} else {
		memset( outRD->cache ,0x55,NO_ONE_RANDOM_BUFFER );
	}
	#if defined(NO_ONE_HASH_FNV1A)
	/* FNV1a requires a preset seed value. */
	memcpy( outRD->cache ,&no_seed ,sizeof(no_seed) );
	#endif
	no_fill(NO_ONE_RANDOM_BUFFER,outRD);
	#if defined(NO_ONE_HASH_FNV1A)
	/* Reset FNV1a seed. (Don't use no_init_random() as a fill) */
	memcpy( outRD->cache ,&no_seed ,sizeof(no_seed) );
	#endif
	return;
}

int no_random_bool( no_random *inRD )
{
	int num = 0;
	no_fill(1,inRD);
	memcpy((void *)&num,inRD->cache,1);
	return num & 1;
}

int no_random_int( no_random *inRD )
{
	int num = 0;
	no_fill(sizeof(int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(int));
	return num;
}

unsigned int no_random_uint( no_random *inRD )
{
	unsigned int num = 0;
	no_fill(sizeof(unsigned int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(unsigned int));
	return num;
}

short int no_random_short( no_random *inRD )
{
	short int num = 0;
	no_fill(sizeof(short int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(short int));
	return num;
}

unsigned short int no_random_ushort( no_random *inRD )
{
	unsigned short int num = 0;
	no_fill(sizeof(unsigned short int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(unsigned short int));
	return num;
}

long int no_random_long( no_random *inRD )
{
	long int num = 0;
	no_fill(sizeof(long int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(long int));
	return num;
}

unsigned long int no_random_ulong( no_random *inRD )
{
	unsigned long int num = 0;
	no_fill(sizeof(unsigned long int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(unsigned long int));
	return num;
}

#ifndef NO_ONE_NO_LONG_LONG

long long int no_random_ll( no_random *inRD )
{
	long long int num = 0;
	no_fill(sizeof(long long int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(long long int));
	return num;
}

unsigned long long int no_random_ull( no_random *inRD )
{
	unsigned long long int num = 0;
	no_fill(sizeof(unsigned long long int),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(unsigned long long int));
	return num;
}

#endif

char no_random_char( no_random *inRD )
{
	char num = 0;
	no_fill(sizeof(char),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(char));
	return num;
}

unsigned char no_random_uchar( no_random *inRD )
{
	unsigned char num = 0;
	no_fill(sizeof(unsigned char),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(unsigned char));
	return num;
}

signed char no_random_schar( no_random *inRD ) /* char may, or may not be signed */
{
	signed char num = 0;
	no_fill(sizeof(signed char),inRD);
	memcpy((void *)&num,inRD->cache,sizeof(signed char));
	return num;
}

float no_random_f( float inMin , float inMax ,no_random *inRD )
{
	if( inMax == inMin ) return inMin;
	if( inMax < inMin ) {
		float temp = inMax;
		inMax = inMin;
		inMin = temp;
	}
	float range = 0.0f ,shift = 0.0f;
	switch( ((int)(inMin < 0)) | (((int)(inMax < 0))<<1) )
	{
		case 0:
			range = inMax - inMin;
			shift = inMax - range;
			break;
		case 1:
			range = fabsf(inMin) + inMax;
			shift = inMin;
			break;
		case 2:
			/* I should never happen. */
			return 0.0f;
			break;
		case 3:
			range = inMax - inMin;
			shift = inMax + -range;
			break;
	}
	no_float out = ((no_float)no_random_ulong(inRD))/((no_float)ULONG_MAX );
	out = threshhold_no_fl(out) * (no_float)range;
	out += shift;
	return (float)out;
}

double no_random_d( double inMin , double inMax ,no_random *inRD )
{
	if( inMax == inMin ) return inMin;
	if( inMax < inMin ) {
		double temp = inMax;
		inMax = inMin;
		inMin = temp;
	}
	double range = 0.0 ,shift = 0.0;
	switch( ((int)(inMin < 0)) | (((int)(inMax < 0))<<1) )
	{
		case 0:
			range = inMax - inMin;
			shift = inMax - range;
			break;
		case 1:
			range = fabs(inMin) + inMax;
			shift = inMin;
			break;
		case 2:
			/* I should never happen. */
			return 0.0;
			break;
		case 3:
			range = inMax - inMin;
			shift = inMax + -range;
			break;
	}
	no_float out = ((no_float)no_random_ulong(inRD))/((no_float)ULONG_MAX );
	out = threshhold_no_fl(out) * (no_float)range;
	out += shift;
	return (double)out;
}

#ifndef NO_ONE_NO_LONG_DOUBLE
long double no_random_ld( long double inMin , long double inMax ,no_random *inRD )
{
	if( inMax == inMin ) return inMin;
	if( inMax < inMin ) {
		long double temp = inMax;
		inMax = inMin;
		inMin = temp;
	}
	long double range = 0.0L ,shift = 0.0L;
	switch( ((int)(inMin < 0)) | (((int)(inMax < 0))<<1) )
	{
		case 0:
			range = inMax - inMin;
			shift = inMax - range;
			break;
		case 1:
			range = fabsl(inMin) + inMax;
			shift = inMin;
			break;
		case 2:
			/* I should never happen. */
			return 0.0L;
			break;
		case 3:
			range = inMax - inMin;
			shift = inMax + -range;
			break;
	}
	no_float out = ((no_float)no_random_ulong(inRD))/((no_float)ULONG_MAX );
	out = threshhold_no_fl(out) * (no_float)range;
	out += shift;
	return (long double)out;
}
#endif

float no_zero_onef(no_random *inRD)
{
	return no_threshhold_float_zo(
		((float)no_random_ulong(inRD) ) / ((float)ULONG_MAX)
	);
}

double no_zero_oned(no_random *inRD)
{
	return no_threshhold_double_zo(
		#ifndef NO_ONE_NO_LONG_LONG
		((double)no_random_ull(inRD) ) / ((double)ULLONG_MAX)
		#else
		((double)no_random_ulong(inRD) ) / ((double)ULONG_MAX)
		#endif
	);
}
#ifndef NO_ONE_NO_LONG_DOUBLE
long double no_zero_oneld(no_random *inRD)
{
	return no_threshhold_ldouble_zo(
		#ifndef NO_ONE_NO_LONG_LONG
		((long double)no_random_ull(inRD) ) / ((long double)ULLONG_MAX)
		#else
		((long double)no_random_ulong(inRD) ) / ((long double)ULONG_MAX)
		#endif
	);
}
#endif

float no_neg_one_onef(no_random *inRD)
{
	float out = ((float)no_random_ulong(inRD) ) / ((float)ULONG_MAX);
	if( no_random_bool(inRD) ) out = out * -1.0f;
	return no_threshhold_float_noo(out);
}

double no_neg_one_oned(no_random *inRD)
{
	#ifndef NO_ONE_NO_LONG_LONG
	double out = ((double)no_random_ull(inRD) ) / ((double)ULLONG_MAX);
	#else
	double out = ((double)no_random_ulong(inRD) ) / ((double)ULONG_MAX);
	#endif
	if( no_random_bool(inRD) ) out = out * -1.0;
	return no_threshhold_double_noo(out);
}

#ifndef NO_ONE_NO_LONG_DOUBLE
long double no_neg_one_oneld(no_random *inRD)
{
	#ifndef NO_ONE_NO_LONG_LONG
	long double out = ((long double)no_random_ull(inRD) ) / ((long double)ULLONG_MAX);
	#else
	long double out = ((long double)no_random_ulong(inRD) ) / ((long double)ULONG_MAX);
	#endif
	if( no_random_bool(inRD) ) out = out * -1.0L;
	return no_threshhold_ldouble_noo(out);
}
#endif

void no_random_buff( void *inBuff ,unsigned long int sz ,no_random *inRD )
{
	char *buff = (char *)inBuff;
	for( unsigned long int loop=0;loop < sz;loop += NO_ONE_RANDOM_BUFFER )
	{
		no_fill(NO_ONE_RANDOM_BUFFER,inRD);
		if( loop + NO_ONE_RANDOM_BUFFER > sz )
		{
			memcpy( (buff + loop) ,inRD->cache ,(loop+NO_ONE_RANDOM_BUFFER) - sz );
		} else {
			memcpy( (buff + loop) ,inRD->cache ,NO_ONE_RANDOM_BUFFER);
		}
	}
	return;
}
