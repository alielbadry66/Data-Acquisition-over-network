#include <avr/io.h>
#include "uart.h"
#include "init.c"

int main() {
    // Initialize UART with a baud rate of 9600
    uart_init(9600);

    // Set the switch pin as input with internal pull-up resistor
    DDRB &= ~(1 << PB0);     // Switch (PB0) as input
    PORTB |= (1 << PB0);     // Enable internal pull-up resistor on PB0

    DDRB |= (1 << PB5);  // LED (PB5) as output

    while (1) {
        // Read the switch status
        if (PINB & (1 << PB0)) {
            uart_send_string("Button not pressed\r\n");
        } else {
            uart_send_string("Button pressed\r\n");
        }

        // Receive and process UART commands

        if(uart_receive_ready() != 0){

          char received_char = uart_receive_char();
          if (received_char == 'l' || received_char == 'L') {
              uart_send_string("LED on\r\n");
              PORTB |= (1 << PB5); // Turn on the LED
          }
          else if (received_char == 'o' || received_char == 'O') {
              uart_send_string("LED off\r\n");
              PORTB &= ~(1 << PB5); // Turn off the LED
          }
        }
        
    }

    return 0;
}

