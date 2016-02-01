/*
 * Copyright: (C) 2016 Douglas Ballard III
 * Version: 1.0 (Hot Mess)
 * License: Creative Commons Attribution 4.0 International Public License
 *          http://creativecommons.org/licenses/by/4.0/
 *          http://creativecommons.org/licenses/by/4.0/legalcode
 * 
 * A lot of the portable timer code was adapted from David Robert Nadeau's blog.
 * http://nadeausoftware.com/articles/2012/04/c_c_tip_how_measure_elapsed_real_time_benchmarking
 * His code is under a "Creative Commons Attribution 3.0 Unported License" license.
 * See http://creativecommons.org/licenses/by/3.0/deed.en_US http://creativecommons.org/licenses/by/3.0/legalcode
 * 
 * The MurMur3 scramble functions are adpated from Austin Appleby's versions.
 * https://code.google.com/p/smhasher/
 * Austin Appleby claims no copyright, and his code is in the public domain.
 * 
 * Note:
 *   Do not compile -O1 or -O2. The resulting binary runs significantly SLOWER.
 *   My tests have shown -Ofast -O3 -O0 and -Os (Ofast fastest Os slowest) are 
 *   generally 2x to 4x as fast. Mind you, this may vary depending on system and 
 *   compiler.
 */


/**
 * @file no_random.h
 * @author Douglas Ballard III
 * @date February 1, 2016
 * @version 1.0
 * @section LICENSE
 * Creative Commons Attribution 4.0 International Public License
 * @see http://creativecommons.org/licenses/by/4.0/
 * @see http://creativecommons.org/licenses/by/4.0/legalcode
 * 
 * @brief Header for a simple clock based entropy gathering library.
 * 
 * There are a number of defines you can use to define how the library operates.
 * 
 * Define NO_ONE_HASH_CRC32 to use crc32 to scramble the data.
 * 
 * Define NO_ONE_HASH_FNV1A32 to use fnv1A 32 bit hash to scramble the data.
 * 
 * Define NO_ONE_HASH_FNV1A64 to use fnv1A 64 bit hash to scramble the data.
 * 
 * Define NO_ONE_HASH_MURMUR3_32 to use Murmur3 32 bit hash to scramble the data.
 * 
 * Define NO_ONE_HASH_MURMUR3_128 to use Murmur3 128 bit hash to scramble the data.
 * 
 * Define NO_ONE_HASH_SELECTED if you have written your own no_hash_scramble function.
 * 
 * The defualt functions are 'Murmur3 32 bit' on 32 bit systems. And 'Murmur3 128 bit' 
 * on 64 bit systems.
 * 
 * Define NO_ONE_NO_LONG_LONG if your compiler does not support "long long"
 * 
 * Define NO_ONE_NO_LONG_DOUBLE if your compiler does not support "long double"
 */

#ifndef NO_ONE_RANDOM_H
/** @cond */
#define NO_ONE_RANDOM_H 1
#if defined(_LP64) || defined(_____LP64_____) || defined(__64BIT__) || _WIN64
# define NO_ONE_IS64 1
# define NO_ONE_NATIVE_INT 8
#else
# define NO_ONE_IS32 1
# define NO_ONE_NATIVE_INT 4
#endif

#if defined(_WIN32)
# include <Windows.h>
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# if defined(__MACH__) && defined(__APPLE__)
#  include <mach/mach.h>
#  include <mach/mach_time.h>
# endif
#else
# error "Failed to find timer functions."
#endif

#if defined(NO_ONE_HASH_SELECTED)
#define NO_ONE_HASH_ONLY_PROTO 1
#endif

/* For 32bit */
#ifndef NO_ONE_HASH_SELECTED
# if defined(NO_ONE_HASH_CRC32)
#  define NO_ONE_HASH_SELECTED NO_ONE_HASH_CRC32
# endif
#endif

/* For 32bit */
#ifndef NO_ONE_HASH_SELECTED
# if defined(NO_ONE_HASH_FNV1A32)
#  define NO_ONE_HASH_SELECTED NO_ONE_HASH_FNV1A32
#  define NO_ONE_HASH_FNV1A 1
# endif
#endif

/* For 64bit */
#ifndef NO_ONE_HASH_SELECTED
# if defined(NO_ONE_HASH_FNV1A64)
#  define NO_ONE_HASH_SELECTED NO_ONE_HASH_FNV1A64
#  define NO_ONE_HASH_FNV1A 1
# endif
#endif

/* For 32bit */
#ifndef NO_ONE_HASH_SELECTED
# if defined(NO_ONE_HASH_MURMUR3_32)
#  define NO_ONE_HASH_SELECTED NO_ONE_HASH_MURMUR3_32
#  define NO_ONE_HASH_MURMUR3 1
# endif
#endif

/* For 64bit */
#ifndef NO_ONE_HASH_SELECTED
# if defined(NO_ONE_HASH_MURMUR3_128)
#  define NO_ONE_HASH_SELECTED NO_ONE_HASH_MURMUR3_128
#  define NO_ONE_HASH_MURMUR3 1
# endif
#endif

#ifndef NO_ONE_HASH_SELECTED
//Default hash alg goes here.
# if defined(NO_ONE_IS64)
#  define NO_ONE_HASH_MURMUR3_128 1
# else
#  define NO_ONE_HASH_MURMUR3_32 1
# endif
#endif


#ifndef NO_ONE_INTERNAL_FLOAT
# ifndef NO_ONE_NO_LONG_DOUBLE
# define NO_ONE_INTERNAL_FLOAT long double
# else
# define NO_ONE_INTERNAL_FLOAT double
# endif
#endif
/** @endcond */ 

/** @typedef
 * largest float for interal use. Exists due to lack of long double prior to c99.
 */
typedef NO_ONE_INTERNAL_FLOAT no_float;

/** @cond */
#ifndef NO_ONE_INT8_TYPE
# define NO_ONE_INT8_TYPE signed char
#endif
/** @endcond */ 

/** @typedef 
 * Overridable typedef of a signed 8 bit int.
 * Define NO_ONE_INT8_TYPE to overide the type.
 */
typedef NO_ONE_INT8_TYPE no_int8;

/** @cond */
#ifndef NO_ONE_UINT8_TYPE
# define NO_ONE_UINT8_TYPE unsigned char
#endif
/** @endcond */ 

/** @typedef 
 * Overridable typedef of an unsigned 8 bit int.
 * Define NO_ONE_UINT8_TYPE to overide the type.
 */
typedef NO_ONE_UINT8_TYPE no_uint8;

/** @cond */
#ifndef NO_ONE_HASH32_TYPE
/* int is generally safe for 32 bits. But you can override it if needed. */
# define NO_ONE_HASH32_TYPE unsigned int
#endif
/** @endcond */ 

/** @typedef 
 * Overridable typedef of a 32 bit int used for the hash/scramble functions.
 * Define NO_ONE_HASH32_TYPE to overide the type.
 */
typedef NO_ONE_HASH32_TYPE no_hash32;

/** @cond */
#ifndef NO_ONE_HASH64_TYPE
# ifndef NO_ONE_NO_LONG_LONG
#  define NO_ONE_HASH64_TYPE unsigned long long int
# else 
/* Crossed fingers */
#  define NO_ONE_HASH64_TYPE unsigned long int
# endif
#endif
/** @endcond */ 

/** @typedef 
 * Overridable typedef of a 64 bit int used for the hash/scramble functions.
 * Define NO_ONE_HASH64_TYPE to overide the type.
 */
typedef NO_ONE_HASH64_TYPE no_hash64;

/** @def
 * Overridable define of no_random object #no_random buffer size.
 * Generally the buffer should divide into 16 evenly.
 * This is not always required, and is dependant on what scrambling
 * function is used.
 * Define NO_ONE_RANDOM_BUFFER to overide the value.
 */
#ifndef NO_ONE_RANDOM_BUFFER
/* Allows enough room for up to 128 bits. Check your hash functions for alignment */
# define NO_ONE_RANDOM_BUFFER 16
#endif

/**
 * @brief This is the core object that holds random data.
 */
typedef struct no_random_t
{
	char cache[NO_ONE_RANDOM_BUFFER];
} no_random;

/**
 * \brief Fills the #no_random object with entropy.
 * @param [in] int The amount of entropy to gather in bytes.
 * @param [in] no_random * The #no_random object to fill.
 * @note Do not fill with a value larger than NO_ONE_RANDOM_BUFFER.
 * @return void
 */
void no_fill( int ,no_random * );

/**
 * \brief Retrieves 1 bit of whitened entropy.
 * @warn The output of this function is not scrambled. It contains a lot of bias. Use #no_random_bool if you want 1 bit of random data.
 * @return void
 */
int no_whitened_bit();

/**
 * \brief Initializes the #no_random object.
 * @param [in] no_random * The #no_random object to initialize.
 * @note Technically unneeded, but it's a very good idea to use it anyway.
 * @return void
 * 
 * Initializes the #no_random object with entropy. And depending on the hash/scramble
 * function used. Said functions starting values.
 */
void no_init_random( no_random * );

/**
 * \brief Returns either 1 or 0
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return int of the value 1 or 0
 */
int no_random_bool( no_random * );

/**
 * \brief Returns a random int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return int with a random value.
 */
int no_random_int( no_random * );

/**
 * \brief Returns a random unsigned int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return unsigned int with a random value.
 */
unsigned int no_random_uint( no_random * );

/**
 * \brief Returns a random short int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return short int with a random value.
 */
short int no_random_short( no_random * );

/**
 * \brief Returns a random unsigned short int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return unsigned short int with a random value.
 */
unsigned short int no_random_ushort( no_random * );

/**
 * \brief Returns a random long int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return long int with a random value.
 */
long int no_random_long( no_random * );

/**
 * \brief Returns a random unsigned long int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return unsigned long int with a random value.
 */
unsigned long int no_random_ulong( no_random * );
#ifndef NO_ONE_NO_LONG_LONG

/**
 * \brief Returns a random long long int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return long long int with a random value.
 */
long long int no_random_ll( no_random * );

/**
 * \brief Returns a random unsigned long long int
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return unsigned long  long int with a random value.
 */
unsigned long long int no_random_ull( no_random * );
#endif

/**
 * \brief Returns a random char
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return char with a random value.
 */
char no_random_char( no_random * );

/**
 * \brief Returns a random unsigned char
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return unsigned char with a random value.
 */
unsigned char no_random_uchar( no_random * );

/**
 * \brief Returns a random signed char
 * @param [in] no_random * The #no_random object to read.
 * @note This was added because the signedness of char is unspecified. Fills, and scrambles the buffer.
 * @return signed char with a random value.
 */
signed char no_random_schar( no_random * );

/**
 * \brief Returns a random float within a range.
 * @param [in] float Minimum value for random number.
 * @param [in] float Maximum value for random number.
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return float with a random value.
 */
float no_random_f( float , float ,no_random * );

/**
 * \brief Returns a random double within a range.
 * @param [in] double Minimum value for random number.
 * @param [in] double Maximum value for random number.
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return double with a random value.
 */
double no_random_d( double , double ,no_random * );
#ifndef NO_ONE_NO_LONG_DOUBLE

/**
 * \brief Returns a random long double within a range.
 * @param [in] long double Minimum value for random number.
 * @param [in] long double Maximum value for random number.
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return long double with a random value.
 */
long double no_random_ld( long double , long double ,no_random * );
#endif

/**
 * \brief Returns a random float between the values 0 and 1
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return float with a random value.
 */
float no_zero_onef(no_random *);

/**
 * \brief Returns a random double between the values 0 and 1
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return double with a random value.
 */
double no_zero_oned(no_random *);
#ifndef NO_ONE_NO_LONG_DOUBLE

/**
 * \brief Returns a random long double between the values 0 and 1
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return long double with a random value.
 */
long double no_zero_oneld(no_random *);
#endif

/**
 * \brief Returns a random float between the values -1 and 1
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return float with a random value.
 */
float no_neg_one_onef(no_random *);

/**
 * \brief Returns a random double between the values -1 and 1
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return double with a random value.
 */
double no_neg_one_oned(no_random *);
#ifndef NO_ONE_NO_LONG_DOUBLE

/**
 * \brief Returns a random long double between the values -1 and 1
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return long double with a random value.
 */
long double no_neg_one_oneld(no_random *);
#endif

/**
 * \brief Fills a buffer with random data.
 * @param [out] void * Address to write random data.
 * @param [in] unsigned long int Number of bytes to write.
 * @param [in] no_random * The #no_random object to read.
 * @note fills, and scrambles the buffer.
 * @return void
 */
void no_random_buff( void *,unsigned long int,no_random * );

#endif /* NO_ONE_RANDOM_H */
