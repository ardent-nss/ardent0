//main.c: Hello World on Raspberry Pi Pico in C
#include <stdio.h>
#include "pico/stdlib.h"
//#include "pico/multicore.h"

// #define FLAG_VALUE 123

// void core1() {
//   printf("veryugly");
// }

int main() {
  stdio_init_all();
  printf("Initializing...\n");

  uint64_t counter = 0;
  while(true) {
    printf("Hello world! %d\n", counter);
    counter++;
  }

  return 0;
}