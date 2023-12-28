//main.c: Hello World on Raspberry Pi Pico in C
#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#define FLAG_VALUE 123
short int console_free = 1;

void core1() {
  multicore_fifo_push_blocking(FLAG_VALUE);
  uint32_t g = multicore_fifo_pop_blocking();
  if (g != FLAG_VALUE) {
    printf("\033[1;101mERR:\033[0m Something's wrong on core 1??\n");
  } else {
    printf("\033[1;105mSETUP:\033[0m Core 1 initialized.\n");
  }

  printf("\033[1;92mCPU1:\033[0m Hey there!\n");

  // uint64_t counter1 = 0;
  // while(true) {
  //   while(console_free != 1) {;;}
  //   console_free = 0;
  //   printf("\033[1;92mCPU1:\033[0m Hello world! %lld\n", counter1);
  //   console_free = 1;
  //   counter1++;
  // }
}

int main() {
  stdio_init_all();
  printf("\n\nTHIS IS A SCAAAAM\n\n");

  printf("\033[1;105mSETUP:\033[0m Initializing core 1...\n");
  multicore_launch_core1(core1);
  uint32_t g = multicore_fifo_pop_blocking();
  printf("\033[1;105mSETUP:\033[0m Initializing core 0...\n");
  if (g != FLAG_VALUE) {
    printf("\033[1;101mERR:\033[0m Something's wrong on core 0??\n");
  } else {
    multicore_fifo_push_blocking(FLAG_VALUE);
    printf("\033[1;105mSETUP:\033[0m Core 0 initialized.\n");
  }

  printf("\033[1;91mCPU0:\033[0m Hiya!\n");

  // uint64_t counter0 = 0;
  // while(true) {
  //   while(console_free != 1) {;;}
  //   console_free = 0;
  //   printf("\033[1;91mCPU0:\033[0m Hello world! %lld\n", counter0);
  //   console_free = 1;
  //   counter0++;
  // }

  return 0;
}