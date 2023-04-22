#include "my_printf.h"

static int outc(int c) 
{
	__out_putchar(c);
	return 0;
}

static int outs (const char *s)
{
	while (*s != '\0')	
		__out_putchar(*s++);
	return 0;
}

static int out_num(long n, int base,char lead,int maxwidth) 
{
	unsigned long m=0;
	char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
	int count=0,i=0;
	UINT8 hex_tab[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

	*--s = '\0';
	
	if (n < 0){
		m = -n;
	}
	else{
		m = n;
	}
	
	do{
		*--s = hex_tab[m%base];
		count++;
	//	__out_putchar(*s);
	}while ((m /= base) != 0);
//	__out_putchar('\n');
	if( maxwidth && count < maxwidth){
		for (i=maxwidth - count; i; i--)	
			*--s = lead;
	}

	if (n < 0)
		*--s = '-';
	
	return outs(s);
}

/*reference :   int vprintf(const char *format, va_list ap); */
static int my_vprintf(const char *fmt, va_list ap) 
{
	char lead=' ';
	int  maxwidth=0;	
	 for(; *fmt != '\0'; fmt++)
	 {
			if (*fmt != '%') {
				outc(*fmt);
				continue;
			}
			
		//format : %08d, %8d,%d,%u,%x,%f,%c,%s 
		    fmt++;
		if(*fmt == '0'){
			lead = '0';
			fmt++;	
		}

		lead=' ';
		maxwidth=0;
		
		while(*fmt >= '0' && *fmt <= '9'){
			maxwidth *=10;
			maxwidth += (*fmt - '0');
			fmt++;
		}
		
			switch (*fmt) {
		case 'd': out_num(va_arg(ap, int),          10,lead,maxwidth); break;
		case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;				
		case 'u': out_num(va_arg(ap, unsigned int), 10,lead,maxwidth); break;
		case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
			case 'c': outc(va_arg(ap, int)); break;		
			case 's': outs(va_arg(ap, char *)); break;		  		
				
			default:  
				outc(*fmt);
				break;
			}
	}
	return 0;
}

#if 1
int my_printf(const char *fmt, ...) 
{
	va_list ap;
	va_start(ap, fmt);
	my_vprintf(fmt, ap);	
	va_end(ap);
	return 0;
}
#else
int my_printf(const char *fmt, ...) 
{
	outc(*fmt);
}
#endif
