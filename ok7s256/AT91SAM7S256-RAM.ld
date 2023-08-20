/*---------------------------------------------------------------------------*/
/*-         ATMEL Microcontroller Software Support  -  ROUSSET  -            */
/*---------------------------------------------------------------------------*/
/* The software is delivered "AS IS" without warranty or condition of any    */
/* kind, either express, implied or statutory. This includes without	     */
/* limitation any warranty or condition with respect to merchantability or   */
/* fitness for any particular purpose, or against the infringements of	     */
/* intellectual property rights of others.				     */
/*---------------------------------------------------------------------------*/
/*- File source          : AT91SAM7S256-RAM.ld                               */
/*- Object               : Linker Script File for Flash Memory Workspace     */
/*-                                                                          */
/*- 1.0 11/Mar/05 JPP    : Creation for WinARM                               */
/*- 2.0 01/May/07 Yoon   : Modified for OK-7S256 Kit                         */
/*---------------------------------------------------------------------------*/

/***** Memory Definitions ****************************************************/

MEMORY
{
  CODE (rx)  : ORIGIN = 0x00000000, LENGTH = 0x00008000
  DATA (rw)  : ORIGIN = 0x00008000, LENGTH = 0x00008000
  STACK (rw) : ORIGIN = 0x00010000,LENGTH = 0x00000000
}

/***** Section Definitions ***************************************************/

SECTIONS
{
  . = 0x0000000;			/* first section is .text which is used for code */
  .text :
  { *Cstartup.o (.text)
  } >CODE =0

  .text :
  { *(.text)				/* remaining code */
    *(.glue_7t) *(.glue_7)
  } >CODE =0

  . = ALIGN(4);

  .rodata :				/* .rodata section which is used for read-only data (constants) */
  { *(.rodata)
  } >CODE

  . = ALIGN(4);

  _etext = . ;
  PROVIDE (etext = .);

  .data : AT (_etext)			/* .data section which is used for initialized data */
  { _data = . ;
    *(.data)
    SORT(CONSTRUCTORS)
  } >DATA

  . = ALIGN(4);

  _edata = . ;
   PROVIDE (edata = .);

  .bss :				/* .bss section which is used for uninitialized data */	
  { __bss_start = . ;
    __bss_start__ = . ;
    *(.bss)
    *(COMMON)
  } 

  . = ALIGN(4);
  __bss_end__ = . ;
  __bss_end__ = . ;
  _end = .;
  . = ALIGN(4);

  .int_data :  
  { *(.internal_ram_top) 
  } >STACK 

  PROVIDE (end = .);

  .stab            0 : { *(.stab) }		/* Stabs debugging sections.  */
  .stabstr         0 : { *(.stabstr) }
  .stab.excl       0 : { *(.stab.excl) }
  .stab.exclstr    0 : { *(.stab.exclstr) }
  .stab.index      0 : { *(.stab.index) }
  .stab.indexstr   0 : { *(.stab.indexstr) }
  .comment         0 : { *(.comment) }

  .debug           0 : { *(.debug) }		/* DWARF 1 debug section */
  .line            0 : { *(.line) }

  .debug_srcinfo   0 : { *(.debug_srcinfo) }	/* GNU DWARF 1 extensions */
  .debug_sfnames   0 : { *(.debug_sfnames) }

  .debug_aranges   0 : { *(.debug_aranges) }	/* DWARF 1.1 and DWARF 2 */
  .debug_pubnames  0 : { *(.debug_pubnames) }

  .debug_info      0 : { *(.debug_info .gnu.linkonce.wi.*) }	/* DWARF 2 */
  .debug_abbrev    0 : { *(.debug_abbrev) }
  .debug_line      0 : { *(.debug_line) }
  .debug_frame     0 : { *(.debug_frame) }
  .debug_str       0 : { *(.debug_str) }
  .debug_loc       0 : { *(.debug_loc) }
  .debug_macinfo   0 : { *(.debug_macinfo) }

  .debug_weaknames 0 : { *(.debug_weaknames) }	/* SGI/MIPS DWARF 2 extensions */
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
