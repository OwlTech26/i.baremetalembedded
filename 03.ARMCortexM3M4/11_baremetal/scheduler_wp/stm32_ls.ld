/* Identify entry point of the code */
ENTRY(Reset_handler)

/* name(attr):ORIGIN=origin,LENGTH=len
	name(attr) - Label (not mandatory): defines name of the memory region which will be later referenced by other part of the linker script.
	ORIGIN=origin - Defines origin address of the memory region.
	LENGTH=len - Defines the length information.
	attr{ALIRWX}:
		R - Read-only sections
		W - Read and write sections
		X - Sections containing executable code
		A - Allocated sections
		I - Initialized sections
		L - same as 'I'
		! - Invert the sense of any of the following attributes
*/
MEMORY
{
	/* MCU				FLASH[kB] 	SRAM1[kB] SRAM2[kB]
	   STM32F446RE		512			112		  16
	*/
	FLASH(rx):ORIGIN =0x08000000,LENGTH =512K
	SRAM(rwx):ORIGIN =0x20000000,LENGTH =128K
	/*
	SRAM1(rwx):ORIGIN =0x20000000,LENGTH =112K
	SRAM2(rwx):ORIGIN =0x20000000+112K-4,LENGTH =16K
	*/
}

SECTIONS
{
	.text :
	{
		/* location counter: . = vma (0x08000000) */
		/* Merge all .isr_vector section of all input files */
		*(.isr_vector)
		/* Merge all .text section of all input files */
		*(.text)
		/* Merge all standard libraries .text section */
		*(.text.*)
		*(.init)
		*(.fini)
		/* Merge all .rodata section of all input files */
		*(.rodata)
		/* Merge all standard libraries .rodata section */
		*(.rodata.*)
		. = ALIGN(4); /* Align the location counter to 32 bit */
		/* location counter: . = vma (0x08000000) + size_of_the_text section */
		_etext = .; /* Store the updated location counter (address information) value in to a symbol. The location counter is incremented by the size of the section. */
	}> FLASH
	
	_la_data = LOADADDR(.data);
	.data :
	{
		_sdata = .; /* Start of the VMA (SRAM) */
		/* Merge all .data section of all input files */
		*(.data)
		/* Merge all standard libraries .data section */
		*(.data.*)
		. = ALIGN(4); /* Align the location counter to 32 bit */
		_edata = .; /* _sdata + size of .data */
	}> SRAM AT> FLASH /* >(vma)AT>(lma): Virtual/Load Memory Address */
	
	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss; /* Needed for syscalls.c*/
		/* Merge all .bss section of all input files */
		*(.bss)
		/* Merge all standard libraries .bss section */
		*(.bss.*)
		. = ALIGN(4); /* Align the location counter to 32 bit */
		_ebss = .; 
		/* Needed for syscalls.c */
		__bss_end__ = _ebss;
		. = ALIGN(4); /* Align the location counter to 32 bit */
		end = .;
		__end__ = .;
	}> SRAM
}