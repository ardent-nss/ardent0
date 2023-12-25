@ main.S: prints "Hello World" repeatedly using the Pico SDK.
@ R0: first parameter to printf
@ R1: second parameter to printf
@ R7: index counter

.thumb_func @ necessary because SDK uses BLX
.global main @ provide program starting address to linker

main:
  MOV R7, #0 @ initialize counter to 0
  BL stdio_init_all @ initialize UART or USB
loop:
  LDR R0, =helloworld @ load address of string
  ADD R7, #1 @ increment counter
  MOV R1, R7 @ move the counter to second parameter
  BL printf @ call pico_printf
  B loop @ loop forever

.data
.align 4 @ necessary alignment
helloworld: .asciz "Hello World %d\n"