SECTIONS {
	. = 0x7e1000;
	
	__text_start = . ;

	.text : {
		arch/start.o(.text)
		*(.text)
	} 

	.rodata ALIGN(4) : 
	{
		__rodata_start = .;
		*(.rodata)
		__rodata_end = .;
	} 

	.data ALIGN(4) : {*(.data)} 

	.rel_dyn_start :
    	{
        	*(.__rel_dyn_start)
    	}

    	.rela.dyn :
        {
        	*(.rela*)
    	}

    	.rel_dyn_end :
    	{
        	*(.__rel_dyn_end)
    	}


        . = ALIGN(8);

       __bss_start = .;

		.bss : {
            *(.bss*)
            . = ALIGN(8);
        }

		__bss_end = .;


	. = __text_start + 0xc800 ;
	__ddr_firmware_start = . ;

	.ddr_firmware : {
		*(.ddr_firmware)
	} 

	__ddr_firmware_end = __ddr_firmware_start + 0x18000;


    /DISCARD/ : { *(.dynsym) }
    /DISCARD/ : { *(.dynstr*) }
    /DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.plt*) }
    /DISCARD/ : { *(.interp*) }
    /DISCARD/ : { *(.gnu*) }
}
