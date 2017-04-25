#include "types.h"


extern void memcpy(unsigned char *dec, unsigned char *src, int size);
extern void memset(unsigned char *src, unsigned char val, int size);

extern int sprintf(char *buf, const char *fmt, ...);
extern int printf(const char *fmt, ...);

extern int strnlen(const char *s, int count);
extern int strlen(const char *s);

extern int strncmp (const char *str1,const char *str2, int n);
extern int strcmp (const char *str1, const char *str2);


