#include "code_relocate.h"
#include "common_type.h"
#include "generic_timer.h"

char __rel_dyn_start[0] __attribute__((section(".__rel_dyn_start")));
char __rel_dyn_end[0] __attribute__((section(".__rel_dyn_end")));
char __rodata_start[0] __attribute__((section(".__rodata_start")));
char __rodata_end[0] __attribute__((section(".__rodata_start")));

extern unsigned int __bss_start;
extern unsigned int __bss_end;

void copy2ddr(void)
{
    extern UINT32 __text_start;
    extern UINT32 __bss_start;

    volatile UINT32 *puiDest = (volatile UINT32 *)RELOCATE_CODE_START;
    volatile UINT32 *puiSrc = (volatile UINT32 *)&__text_start;
    volatile UINT32 uiSrc = &__text_start;
    volatile UINT32 uiSrcEnd = &__bss_start;

    UINT32 uiCodeSize = (uiSrcEnd - uiSrc)/sizeof(UINT32);//0x1E7A;
    UINT32 uiCurCopySize = 0;

    volatile UINT32 *puiDdrAddr = (volatile UINT32 *)0x40a01f90;
	*puiDdrAddr = 0;

    my_printf("src:0x%x,src end:0x%x, code size:0x%x\r\n", uiSrc, uiSrcEnd, uiSrcEnd - uiSrc);
    my_printf("text start:0x%x, bss end:0x%x, code size:0x%x\r\n", &__text_start, &__bss_start, (&__bss_start) - (&__text_start));
    
    while(uiCurCopySize < uiCodeSize)
    {
        *puiDest = *puiSrc;
        puiDest++;
        puiSrc++;
        uiCurCopySize++;
    }

#if 1
    uiCurCopySize = 0;

    puiDest = (volatile UINT32 *)RELOCATE_CODE_START;
    puiSrc = (volatile UINT32 *)&__text_start;
    while(uiCurCopySize < uiCodeSize)
    {
        if (*puiDest != *puiSrc)
        {
            my_printf("diff src addr:0x%x,val:0x%x, dest addr:0x%x,val:0x%x\r\n", puiSrc, *puiSrc, puiDest, *puiDest);
        }
        puiDest++;
        puiSrc++;
        uiCurCopySize++;
    }
#else
     //uiCurCopySize = 0;
     //while(uiCurCopySize < uiCodeSize)
    //{
      //  *puiDdrAddr = (*puiDdrAddr)+1;
	  puiDdrAddr = (volatile UINT32 *)(0x7e4f80 - 0x7e1000 + 0x40A00000);
        my_printf("ddr val:%x\r\n", *puiDdrAddr);
      puiDdrAddr = (volatile UINT32 *)0x7e4f80;
      my_printf("rodata val:0x%x\r\n", *puiDdrAddr);
        //uiCurCopySize++;
    //}
#endif
}

extern void code_relocate(void)
{
    my_printf("ddr copy code\r\n");
    /* 复制代码到ddr中 */
    copy2ddr();
     my_printf("ddr copy code finish\r\n");
    /* 修改需要修改的地址 */
    fix_rel_addr();
}

extern void clean_bss(void)
{    
    volatile UINT32 *puiBssStart = (volatile UINT32 *) ((& __bss_start) + 0x4021F000);
    volatile UINT32 *puiBssEnd = (volatile UINT32 *) ((&__bss_end) + 0x4021F000);
 
    while(puiBssStart < puiBssEnd)
    {
        *puiBssStart++ = 0;
    } 
}
