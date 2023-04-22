#include "linkage.h"
//#include "code_relocate.h"

.globl TEXT_BASE
TEXT_BASE :
.quad 0x7e1000//_start

.globl RELOCATE_CODE_START
RELOCATE_CODE_START :
.quad 0x40A00000

.globl RELOCATE_OFS
RELOCATE_OFS :
.quad 0x4021F000

.globl __REL_DYB_OFS
__REL_DYB_OFS :
    .quad   __rel_dyn_start - 0x7e1000 //TEXT_BASE

ENTRY(fix_rel_addr)
ldr x9, =0x4021F000 //RELOCATE_OFS
//add lr, lr,x9

adr x2, __rel_dyn_start
adr x3, __rel_dyn_end

fixloop:
ldp	x4, x5, [x2], #16
//ldr x4, [x2]
//add x2, x2, #8
//ldr x5, [x2]
//add x2, x2, #8
//ldr x6, [x2]
//add x2, x2,#8
ldr	x6, [x2], #8

and x5, x5, #0xFFFFFFFF
cmp x5, #1027
bne fixnext

add x4, x4, x9
add x6, x6, x9
str x6, [x4]

fixnext:
cmp x2,x3
b.lo fixloop

ret
ENDPROC(fix_rel_addr)

