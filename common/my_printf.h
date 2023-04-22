#ifndef STDIO_H_
#define STDIO_H_

#include<stdarg.h>
#include "common_type.h"
#include "uart.h"

#if 0
typedef char *  va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )


#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_arg(ap,t)    ( *(t *)( ap=ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )
#endif
#define  __out_putchar  uart_putc


#define  MAX_NUMBER_BYTES  64

int my_printf(const char *fmt, ...);

#endif
