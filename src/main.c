//main.c: Hello World on Raspberry Pi Pico in C
#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/binary_info.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 921600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define FLAG_VALUE 123
const uint LED_CPU0 = 9;
const uint LED_CPU1 = 5;

void core1() {
  multicore_fifo_push_blocking(FLAG_VALUE);
  uint32_t g = multicore_fifo_pop_blocking();
  if (g != FLAG_VALUE) {
    printf("\033[1;101mERR:\033[0m Something's wrong on core 1??\n");
  } else {
    printf("\033[1;105mSETUP:\033[0m Core 1 initialized.\n");
  }

  printf("\033[1;92mCPU1:\033[0m Hey there!\n");

  uint64_t counter1 = 0;
  while(true) {
    gpio_put(LED_CPU1, 1);

    //printf("\033[1;92mCPU1:\033[0m Hello world! %lld\n", counter1);

    counter1++;
    gpio_put(LED_CPU1, 0);
    //sleep_us(1);
  }
}

int main() {
  set_sys_clock_khz(250000, true);
  stdio_init_all();

  uart_init(UART_ID, 115200);
  printf("11500 baud comm right here\n\n");
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

  printf("\n\nNew baudrate: %d\n\n", actual);
  bi_decl(bi_program_description("Ardent 0 Bootloader"));
  bi_decl(bi_1pin_with_name(LED_CPU0, "CPU0 status LED"));
  bi_decl(bi_1pin_with_name(LED_CPU1, "CPU1 status LED"));

  if (cyw43_arch_init()) {
    printf("\033[41mFATAL:\033[0m Wi-Fi init failed\n");
    return -1;
  }

  gpio_init(LED_CPU0);
  gpio_init(LED_CPU1);
  gpio_set_dir(LED_CPU0, GPIO_OUT);
  gpio_set_dir(LED_CPU1, GPIO_OUT);

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

  uint64_t counter0 = 0;
  while(true) {
    gpio_put(LED_CPU0, 1);

    printf("\033[1;91mCPU0:\033[0m Hello world! %lld\n", counter0);

    counter0++;
    gpio_put(LED_CPU0, 0);
    //sleep_us(1);
  }

  return 0;
}