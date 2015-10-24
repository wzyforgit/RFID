#ifndef DATATYPE_H
#define DATATYPE_H

typedef unsigned      char 	uint8;  /*  8 bits */
typedef unsigned 	  int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef signed		  char	int8;   /*  8 bits */
typedef signed  	  int	int16;  /* 16 bits */
typedef signed	long  int	int32;  /* 32 bits */

typedef float float32; /* 32 bits */

typedef bit BOOL;	/*BOOL type*/

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#endif