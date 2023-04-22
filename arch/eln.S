#include "linkage.h"
#include "macro.h"

ENTRY(switch_el3_to_el2)
adr x4, el2_entry
armv8_switch_to_el2_m x4,x5
ENDPROC(switch_el3_to_el2)

ENTRY(el2_entry)
4:
	switch_el x1, 3f, 2f, 1f
3:
	ldr w0, =0x30220000
	ldr w2, [x0]
	orr w2,w2,#(3<<11)
	and w2,w2,#(~(1<<12))
	//orr w2,w2,#(3<<11)
	str w2, [x0] 
	b 4b
2:
1:
	ldr w0, =0x30220000
	ldr w2, [x0]
	orr w2,w2,#(3<<11)
	str w2, [x0] 
	b 1b	
ENDPROC(el2_entry)
