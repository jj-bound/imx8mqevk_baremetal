#ifndef IMX8M_UART_H_
#define IMX8M_UART_H_

#include "common_type.h"

typedef struct{
	UINT32 uiUartRxD; //0
	UINT32 uiRecv1[15];
	UINT32 uiUartTxD; //40
	UINT32 uiRecv2[15];
	UINT32 uiCr1;//80
	UINT32 uiCr2;//84
	UINT32 uiCr3;//88
	UINT32 uiCr4;//8c
	UINT32 uiFcr; //0x90
	UINT32 uiSr1;//94
	UINT32 uiSr2;//98
	UINT32 uiEsc;//9c
	UINT32 uiTim;//a0
	UINT32 uiBir;//a4
	UINT32 uiBmr;//a8
	UINT32 uiBrc;//ac
	UINT32 uiOnems;//b0
	UINT32 uiUts;//b4
	UINT32 uiMcr;//b8
} T_UART_REG;

void uart_init(void);
void uart_putc(UINT8 ucVal);

#endif
