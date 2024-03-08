/*
 * std_types.h
 *
 *  Created on: 28 Sep 2023
 *      Author: maria
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*
 * Boolean Data type
 */
typedef unsigned char boolean;

/* values of boolean data type */
#ifndef TRUE
#define TRUE (1u)
#endif
#ifndef False
#define FALSE (0u)
#endif

#define LOGIC_HIGH (1u)
#define LOGIC_LOW (0u)

#define NULL ((void*)0)

typedef unsigned char         uint8;          /*           0 .. 255              */
typedef signed char           sint8;          /*        -128 .. +127             */
typedef unsigned short        uint16;         /*           0 .. 65535            */
typedef signed short          sint16;         /*      -32768 .. +32767           */
typedef unsigned long         uint32;         /*           0 .. 4294967295       */
typedef signed long           sint32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;


#endif /* STD_TYPES_H_ */
