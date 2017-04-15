#include "lib.h"


void memcpy(unsigned char *dec, unsigned char *src, int size)
{
	unsigned char *dec_p, *src_p;
	dec_p = dec ;
	src_p = src ;

	while(size--) {
		*dec_p++ = *src_p++;
	}
}


void memset(unsigned char *src, unsigned char val, int size)
{
	unsigned char *src_p;
	src_p = src;

	while(size--) {
		*src_p++ = val;
	}
}


