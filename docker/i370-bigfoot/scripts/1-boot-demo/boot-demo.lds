/*
 * Linker spec.
 *
 * Tells the gnu linker how to arrange the various sections into
 * various loadable segments. This spec is used to place the text
 * section at address zero, forcing it to the start of a loadable
 * elf segment.
 *
 * You can review the resulting binary with
 * i370-ibm-linux-readelf -a kernel-demo
 */

OUTPUT_FORMAT("elf32-i370")
ENTRY(_start)
SECTIONS
{
  /* text section. Start at zero. */
   . = 0x0;
   _text = .;
   .text : { *(.text) }
   _etext = .;

  /* Global data */
  . = ALIGN(4096);  /* Pad to page start */
  _data = .;
  .data : { *(.data) CONSTRUCTORS }
  _edata = .;
  _bss = .;
  .bss : { *(.bss) *(COMMON) }
  _ebss = .;

  . = ALIGN(4096);
  _end = .;
}
