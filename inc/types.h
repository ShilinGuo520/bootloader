#ifndef _TYPES_H_
#define _TYPES_H_

typedef int bool;

typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef unsigned long size_t;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#endif
