#include "uart.h"

void uart_gpio_init()
{
	volatile UINT32 *puiUart1Rx = (volatile UINT32 *)0x30330234;
	volatile UINT32 *puiUart1Tx = (volatile UINT32 *)0x30330238;
	volatile UINT32 *puiUart1RxCtrl = (volatile UINT32 *)0x3033049c;
	volatile UINT32 *puiUartTxCtrl = (volatile UINT32 *)0x303304A0;
	volatile UINT32 *puiUartSelInput = (volatile UINT32 *)0x303304F4;
	
	/* uart引脚复用 */
	*puiUart1Rx = 0;//(1<<4);
	*puiUart1Tx = 0;//(1<<4);

	*puiUart1RxCtrl = (1<<3)|(6<<0); //(0<<8)|(1<<6)|(0<<3)|(1<<0);
	*puiUartTxCtrl = (1<<3)|(6<<0); //(0<<8)|(1<<6)|(0<<3)|(1<<0);

	*puiUartSelInput = 0;
}

void uart_init(void)
{
	volatile T_UART_REG *ptUart1Reg = (volatile T_UART_REG *)0x30860000;
	uart_gpio_init();

	ptUart1Reg->uiCr2 = 0;
	ptUart1Reg->uiCr1 = 0;

	while((ptUart1Reg->uiCr2)&(1<<0)==0);

	ptUart1Reg->uiCr3 = 0x784;
	ptUart1Reg->uiCr4 = 0x8000;
	ptUart1Reg->uiEsc = 0x2b;
	ptUart1Reg->uiTim = 0;
	ptUart1Reg->uiUts = 1<<4;
	ptUart1Reg->uiFcr = (2<<10)|(4<<7)|(1<<0);
	ptUart1Reg->uiMcr = 0;

	ptUart1Reg->uiBir = 0xf;//0x0FA2;
	ptUart1Reg->uiBmr = 80000000/(2*115200);//0xD415;

	/* 使能uart */
	ptUart1Reg->uiCr2 = (1<<14)|(0<<8)|(0<<6)|(1<<5)|(1<<2)|(1<<1)|(1<<0);
	ptUart1Reg->uiCr1 |= (1<<0);
}

void uart_putc(UINT8 ucVal)
{
#if 1
	volatile T_UART_REG *ptUart1Reg = (volatile T_UART_REG *)0x30860000;


	//while((ptUart1Reg->uiSr1)&(1<<13)==0);
	//while(((ptUart1Reg->uiUts)&(1<<6))==0);
	ptUart1Reg->uiUartTxD = ucVal;
	while(((ptUart1Reg->uiUts)&(1<<6))==0);
	//while((ptUart1Reg->uiSr2)&(1<<3)==0);
#else
	volatile UINT32 *puiUartTxd = (volatile UINT32 *)0x30860040;
	//while((ptUart1Reg->uiSr1)&(1<<13)==0);
	*puiUartTxd = ucVal;
#endif
	//while(((ptUart1Reg->uiUts)&(1<<6))==0);
}
