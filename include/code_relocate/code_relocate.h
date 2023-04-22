#ifndef CODE_RELOCATE_H_
#define CODE_RELOCATE_H_

#define RELOCATE_CODE_START 0x40A00000

extern char __rel_dyn_start[0];
extern char __rel_dyn_end[0];
extern char __rodata_start[0];
extern char __rodata_end[0];

extern void code_relocate(void);
extern void clean_bsse();
extern void fix_rel_addr();
extern void copy2ddr(void);

#endif /* CODE_RELOCATE_H_ */
