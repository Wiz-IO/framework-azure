/* Copyright (c) Microsoft Corporation. All rights reserved.
   Licensed under the MIT License. 
   
   Edit: Georgi Angelov 2019
*/

MEMORY
{
    TCM (rwx) : ORIGIN = 0x00100000, LENGTH = 192K
    SYSRAM (rwx) : ORIGIN = 0x22000000, LENGTH = 64K
    FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 1M
}

/* The data and BSS regions can be placed in TCM or SYSRAM. The code and read-only regions can
   be placed in TCM, SYSRAM, or FLASH. See
   https://docs.microsoft.com/en-us/azure-sphere/app-development/memory-latency for information
   about which types of memory which are available to real-time capable applications on the
   MT3620, and when they should be used. */
REGION_ALIAS("CODE_REGION", TCM);
REGION_ALIAS("RODATA_REGION", TCM);
REGION_ALIAS("DATA_REGION", TCM);
REGION_ALIAS("BSS_REGION", TCM);

ENTRY(ExceptionVectorTable)

SECTIONS
{
    /* The exception vector's virtual address must be aligned to a power of two,
       which is determined by its size and set via CODE_REGION.  See definition of
       ExceptionVectorTable in main.c.

       When the code is run from XIP flash, it must be loaded to virtual address
       0x10000000 and be aligned to a 32-byte offset within the ELF file. */
    .text : ALIGN(32) {
        KEEP(*(.vector_table))
        *( .text .text.* i.* )
        *( .glue_7t )
        *( .glue_7 )
        *( .ctors )
        *( .dtors )
        *( .gnu.linkonce.t.* )
        *( .gnu.linkonce.r.* )
        *( .gcc_except_table )

        . = ALIGN(4);
        KEEP( *(SORT(.preinit_array.*)) )
        KEEP( *(.preinit_init_array*) )
        PROVIDE_HIDDEN (__preinit_array_end = .);
	
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP( *(SORT(.init_array.*)) )
        KEEP( *(.init_array*) )
        PROVIDE_HIDDEN (__init_array_end = .);
        
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP( *(SORT(.fini_array.*)) )
        KEEP( *(.fini_array*) )
        PROVIDE_HIDDEN (__fini_array_end = .);   
        
    } >CODE_REGION

    .ARM.extab : {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } >CODE_REGION
	.ARM.exidx : ALIGN(4) { 
	    __exidx_start = .;
	    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
	    __exidx_end = .;
	} >CODE_REGION	

    .rodata : {
        . = ALIGN(4);
        *( .rodata .rodata* .constdata* .conststring*  ) 
    } >RODATA_REGION

    .data : {
        . = ALIGN(4);
        *(.data)
    } >DATA_REGION

    .bss : {
        . = ALIGN(4);
        *(.bss)
    } >BSS_REGION

    StackTop = ORIGIN(TCM) + LENGTH(TCM);
}