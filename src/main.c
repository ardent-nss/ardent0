//main.c: Hello World on Raspberry Pi Pico in C
#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"

#define FLAG_VALUE 123
//const short int LED_STATUS = 25;
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

  //bool *console_free = &console_free;
  uint64_t counter1 = 0;
  while(true) {
    while(console_free = 0) {;;}
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    console_free = 0;
    printf("\033[1;92mCPU1:\033[0m Hello world! %lld\n", counter1);
    console_free = 1;
    sleep_us(1);
    counter1++;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
  }
}

int main() {
  set_sys_clock_khz(250000, true);
  stdio_init_all();
  printf("\n\n");
  //bi_decl(bi_program_description("Ardent 0 Bootloader"));
  //bi_decl(bi_1pin_with_name(LED_STATUS, "Status LED"));
  //gpio_init(LED_STATUS);
  if (cyw43_arch_init()) {
    printf("\033[41mFATAL:\033[0m Wi-Fi init failed\n");
    return -1;
  }

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

  //bool *console_free = &console_free;
  uint64_t counter0 = 0;
  while(true) {
    while(console_free = 0) {;;}
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    console_free = 0;
    printf("\033[1;91mCPU0:\033[0m Hello world! %lld\n", counter0);
    console_free = 1;
    sleep_us(1);
    counter0++;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
  }

  return 0;
}