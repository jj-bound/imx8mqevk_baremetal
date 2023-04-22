#ifndef _COMMON_TYPE_H_
#define _COMMON_TYPE_H_

typedef unsigned char UINT8;
typedef char INT8;
typedef unsigned short int UINT16;
typedef short int INT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef long long INT64;
typedef unsigned long long UINT64;

#ifndef NULL
#define NULL 0
#endif

typedef enum{
	UART1 = 0,
	UART2,
	UART3,
	UART4,
} E_IMX8M_UART;

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

static inline void reg32_write(unsigned int uiAddr, unsigned int uiRegVal)
{
	volatile unsigned int *puiRegAddr = (volatile unsigned int *)uiAddr;
	*puiRegAddr = uiRegVal;
}

static inline int reg32_read(unsigned int uiAddr)
{
	unsigned int *puiRegAddr = (unsigned int *)uiAddr;
	return (*puiRegAddr);
}

static inline unsigned short reg16_read(unsigned int uiAddr)
{
	unsigned short *pusRegAddr = (unsigned short *)uiAddr;
	return (*pusRegAddr);
}

#endif
