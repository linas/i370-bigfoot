OUTPUT_FORMAT("elf32-i370")
ENTRY(_start)
SECTIONS
{
  /* text section. Start at zero. */
   . = 0x0;
   _text = .;
   .text : { *(.text) }
   _etext = .;

  /* The initial task and kernel stack */
  init_task : { *(start_kernel) }

  /* Global data */
  . = ALIGN(4096);  /* Pad to page start */
  .rodata : { *(.rodata) }
  _data = .;
  .data : { *(.data) CONSTRUCTORS }
  _edata = .;
  _bss = .;
  .bss : { *(.bss) *(COMMON) }
  _ebss = .;

  . = ALIGN(4096);
  _end = .;
}
