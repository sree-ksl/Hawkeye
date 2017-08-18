#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf.h"

#include "boards.h"
#include "hal_clocks.h"
#include "hal_nop_delay.h"
#include "hal_gpio.h"
#include "common_util.h"
#include "tinyprintf.h"
#include "uart_printf.h"
#include "ms_timer.h"
#include "nrf_util.h"
#include "hal_uart.h"
#include "simple_adc.h"
#include "CBUF.h"

#define PIN_1 2
#define PIN_2 3
#define PIN_3 26
#define PIN_4 22
#define PIN_5 27
#define PIN_6 28

// Circular buffer variables
#define myQ_SIZE    64
volatile struct
{
  uint8_t     m_getIdx;
  uint8_t     m_putIdx;
  uint8_t     m_entry[ myQ_SIZE ];
} myQ;

//Button state enum
enum state{
  PLAY,
  PAUSE
}btn_state = PLAY;

static void init_pbtn(void){
  hal_gpio_cfg_input(BUTTON_1,HAL_GPIO_PULL_DISABLED);
}
//initialize gpio for all the 6 led's and put them in non active state
static void init_gpio(void)
{
    hal_gpio_cfg_output(PIN_1, 0);
    hal_gpio_cfg_output(PIN_2, 0);
    hal_gpio_cfg_output(PIN_3, 0);
    hal_gpio_cfg_output(PIN_4, 0);
    hal_gpio_cfg_output(PIN_5, 0);
    hal_gpio_cfg_output(PIN_6, 0);
}

void letter_a(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}

void letter_b(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}

void letter_c(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_d(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_e(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_f(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_g(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_h(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_i(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_j(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_k(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_l(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_m(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_n(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_o(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_p(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_q(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_r(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_s(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_t(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_u(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_v(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_w(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_x(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_y(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_z(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_space(void){
  hal_gpio_pin_write(PIN_1, 1);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 1);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_period(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_comma(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_semicolon(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_questionmark(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 1);
}
void letter_apost(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}
void letter_exclamation(void){
  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 1);
  hal_gpio_pin_write(PIN_3, 1);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 1);
  hal_gpio_pin_write(PIN_6, 0);
}

void cell_clear(void){

  hal_gpio_pin_write(PIN_1, 0);
  hal_gpio_pin_write(PIN_2, 0);
  hal_gpio_pin_write(PIN_3, 0);
  hal_gpio_pin_write(PIN_4, 0);
  hal_gpio_pin_write(PIN_5, 0);
  hal_gpio_pin_write(PIN_6, 0);
}

//to pop all elements of buffer and clear it for the next
void read_buf(void){
//clear the cell contents
	cell_clear();
  //pop till buffer is empty and flush it
  if(CBUF_Len(myQ) != 0){
    //retrieve element from buffer and convert to braille
    uint8_t poped_letter = CBUF_Pop(myQ);
    tfp_printf("popped letter: %c\n", poped_letter);
    switch (poped_letter) {
      case 'a':
          letter_a();
          break;
      case 'b':
          letter_b();
          break;
      case 'c':
          letter_c();
          break;
      case 'd':
            letter_d();
            break;
      case 'e':
            break;
            letter_e();
      case 'f':
            letter_f();
            break;
      case 'g':
            letter_g();
            break;
      case 'h':
            letter_h();
            break;
      case 'i':
            letter_i();
            break;
      case 'j':
              letter_j();
              break;
      case 'k':
              letter_k();
              break;
      case 'l':
              letter_l();
              break;
      case 'm':
              letter_m();
              break;
      case 'n':
              letter_n();
              break;
      case 'o':
              letter_o();
              break;
      case 'p':
              letter_p();
              break;
      case 'q':
              letter_q();
              break;
      case 'r':
              letter_r();
              break;
      case 's':
              letter_s();
              break;
      case 't':
              letter_t();
              break;
      case 'u':
              letter_u();
              break;
      case 'v':
              letter_v();
              break;
      case 'w':
              letter_w();
              break;
      case 'x':
              letter_x();
              break;
      case 'y':
              letter_y();
              break;
      case 'z':
              letter_x();
              break;
      case ' ':
              letter_space();
              break;
      case '.':
              letter_period();
              break;
      case ',':
              letter_comma();
              break;
      case ';':
              letter_semicolon();
              break;
      case '\'':
              letter_apost();
              break;
      case '?':
              letter_questionmark();
              break;
      case '!':
              letter_exclamation();
              break;
    }

  }
}

void uart_handler(uint8_t *ptr){
    // Read string and push to buffer
    for (int i = 0; ptr[i] != '\0'; i++)
    {      CBUF_Push(myQ, ptr[i] );
      tfp_printf("Pushed\n");
    }

    //Displaying buffer contents
    tfp_printf("Buffer contents: %s\n", myQ.m_entry);
    //read the buffer and convert to braille

}

void repeated_handler()
{
    //pop buffer here for timer
    read_buf();
}

void pause_all(void){
    //to pause the function
      ms_timer_stop(MS_TIMER0);
      cell_clear();
}

void play_all(void){
      //play the cell
      ms_timer_start(MS_TIMER0, MS_REPEATED_CALL, RTC_TICKS_MS(2000),repeated_handler);

  }


void button_check(void)
{
    static uint32_t prev_state = !BUTTONS_ACTIVE_STATE;
    bool falling_edge;
    uint32_t curr_state = hal_gpio_pin_read(BUTTON_1);
    if((curr_state == !BUTTONS_ACTIVE_STATE) && (prev_state == BUTTONS_ACTIVE_STATE))
    {
         falling_edge = true;
    }
    else
    {
        falling_edge = false;
    }
    prev_state = curr_state;

    if(falling_edge)
    {
        if(btn_state == PLAY)
        {
            btn_state = PAUSE;
            tfp_printf("Paused!\n");
            pause_all();
        }
        else
        {
            btn_state = PLAY;
            tfp_printf("Played!\n");
            play_all();
        }
    }

}


// Main Function.
int main(void)
{
    //initialize and set all pins as output
    init_gpio();
    // Initialise buffer
    CBUF_Init(myQ);
    // Initialize uart
    hal_uart_init(HAL_UART_BAUD_9600, uart_handler);
    //init button
    init_pbtn();


    hfclk_xtal_init_blocking();
    lfclk_init(LFCLK_SRC_Xtal);

    //timer to check button state
    ms_timer_init (APP_IRQ_PRIORITY_HIGH);
    ms_timer_start(MS_TIMER1, MS_REPEATED_CALL, RTC_TICKS_MS(100),button_check);
    play_all();

    while (true)
    {
      __WFI();
    }
}

/** @} */
/** @} */
