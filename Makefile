CROSS_COMPILE := aarch64-none-elf-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCIPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
OBJNAME := relocate

INC := -I./include/timer -I./include/asm -I./include/driver/uart -I./clock -I./common \
       -I./include/exception -I./include/gic -I./include/driver/ddr -I./include \
	   -I./include/code_relocate

OBJ := main.o ./arch/eln.o ./arch/start.o \
      ./timer/arm_generic_timer/generic_timer.o \
	  ./driver/uart/uart.o ./clock/clock.o ./common/my_printf.o \
	  ./arch/gic.o ./arch/gic/gic.o ./arch/vector.o ./arch/exception.o \
	  ./driver/ddr/ddr.o ./driver/src/src.o \
	  ./code_relocate/code_relocate.o \
	  ./code_relocate/fix_rel_dyn.o \

all:$(OBJ)
	$(LD) -T $(OBJNAME).lds -pie  $^ -o $(OBJNAME).elf
	$(OBJCIPY) -O binary -S $(OBJNAME).elf $(OBJNAME).bin
	$(OBJDUMP) -D $(OBJNAME).elf  > $(OBJNAME).dis

clean:
	rm -rf *.bin $(OBJ) *.elf *.dis

%.o:%.S
	$(CC) $(INC) -fpie  -O0 -c -o $@ $<

%.o:%.c
	$(CC) $(INC) -fpie -O0 -c -o $@ $<
