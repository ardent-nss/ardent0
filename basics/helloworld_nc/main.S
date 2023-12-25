@ main.S: converts 1234 into bin and hex, and prints them.
@ R0: first parameter to printf
@ R1: stores the number 1234

.thumb_func @ necessary because SDK uses BLX
.global main @ provide program starting address to linker

main:
  MOV R1, #1234 @ store the number 1234
  BL stdio_init_all @ initialize UART or USB

  LDR R0, =num_dec @ load address of decimal line
  BL printf @ print decimal of 1234

  LDR R0, =num_hex @ load address of hexadecimal line
  BL printf @ print hexadecimal of 1234

  LDR R0, =num_bin @ load address of binary line
  BL printf @ print binary of 1234

.data
.align 4 @ necessary alignment
num_dec: .asciz "Dec: %d\n" @ %d: decimal
num_hex: .asciz "Hex: %x\n" @ %x: hexadecimal
num_bin: .asciz "Bin: %c\n" @ %c: direct chars, in this case binary