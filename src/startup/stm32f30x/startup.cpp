extern "C" {
// Signature to main function
extern int main();

// Linker script .data variables
extern unsigned int _sdata;
extern unsigned int _edata;
extern unsigned int _sidata;

// Linker script .bss variables
extern unsigned int _sbss;
extern unsigned int _ebss;

// Consturctor and destructor memory
typedef void (*ptr_func_t)(void);
extern ptr_func_t __preinit_array_start[];
extern ptr_func_t __preinit_array_end[];
extern ptr_func_t __init_array_start[];
extern ptr_func_t __init_array_end[];
extern ptr_func_t __fini_array_start[];
extern ptr_func_t __fini_array_end[];

// Load .data section from FLASH
void copy_data() {
  unsigned int *src = &_sidata;
  unsigned int *dst = &_sdata;
  while (dst < &_edata) {
    *dst++ = *src++;
  }
}

// Clear .bss section
void zero_bss() {
  unsigned int *dst = &_sbss;
  while (dst < &_ebss) {
    *dst++ = 0;
  }
}

// Call constructors for static objects
void call_init_array() {
  auto array = __preinit_array_start;
  while (array < __preinit_array_end) {
    (*array)();
    array++;
  }

  array = __init_array_start;
  while (array < __init_array_end) {
    (*array)();
    array++;
  }
}

// Call destructors for static objects
void call_fini_array() {
  auto array = __fini_array_start;
  while (array < __fini_array_end) {
    (*array)();
    array++;
  }
}

// Entry point defined in linker file
void RESET_handler(void) {
  while (true)
    ;

  copy_data();
  zero_bss();
  call_init_array();

  // Application loop
  main();

  call_fini_array();

  // ...and its dead.
  while (true)
    ;
}
}
