/* Entry point */
ENTRY(RESET_handler)

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

/* Memories definition */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  .isr_vector (READONLY) :
  {
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  .text (READONLY) :
  {
    . = ALIGN(4);
    *(.text)     /* .text sections (code) */
    *(.text*)    /* .text* sections (code) */
    *(.eh_frame) /* C++ exceptions support */
    . = ALIGN(4);
    _etext = .;  /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata (READONLY) :
  {
    . = ALIGN(4);
    *(.rodata)  /* .rodata sections (constants, strings, etc.) */
    *(.rodata*) /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  /* Index table for exception handling */
  .ARM.extab (READONLY) : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH

  /* Index table for stack unwinding */
  .ARM.exidx (READONLY) : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array (READONLY) :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array (READONLY) :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array (READONLY) :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM" Ram type memory */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;  /* create a global symbol at data start */
    *(.data)     /* .data sections */
    *(.data*)    /* .data* sections */
    . = ALIGN(4);
    _edata = .;  /* define a global symbol at data end */
  } >SRAM AT> FLASH

  /* Uninitialized data section into "RAM" Ram type memory */
  .bss ALIGN(4) (NOLOAD) :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .; /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
    _ebss = .; /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >SRAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
