#include "common.h"

typedef struct
{
  volatile unsigned int CR;
  volatile unsigned int CFGR;
  volatile unsigned int CIR;
  volatile unsigned int APB2RSTR;
  volatile unsigned int APB1RSTR;
  volatile unsigned int AHBENR;
  volatile unsigned int APB2ENR;
  volatile unsigned int APB1ENR;
  volatile unsigned int BDCR;
  volatile unsigned int CSR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)0x40021000)

