#include <avr/io.h>
#include "uart.h"   // Include the UART communication library
#include "init.c"   // Include initialization code for AVR microcontroller
#include <string.h> // Include string.h for strncmp function

int main() {
    // Initialize UART with a baud rate of 9600
    uart_init(9600);

    // Set the switch pin as input with an internal pull-up resistor
    DDRB &= ~(1 << PB0);     // Set PB0 as input (Switch)
    PORTB |= (1 << PB0);     // Enable internal pull-up resistor on PB0

    DDRB |= (1 << PB5);      // Set PB5 as output (LED)

    char command[16];        // Array to store received command
    uint8_t index = 0;       // Index for tracking characters in the command
    char lastButtonState = 1; // Assume the button is not pressed initially

    while (1) {
        // Check the button status
        char buttonState = PINB & (1 << PB0);

        if (buttonState != lastButtonState) {
            if (buttonState) {
                uart_send_string("Button not pressed\r\n");
            } else {
                uart_send_string("Button pressed\r\n");
            }
            lastButtonState = buttonState;
        }

        // Receive and process UART commands as complete strings
        if (uart_receive_ready() != 0) {
            char received_char = uart_receive_char();

            if (received_char == '\n' || received_char == '\r') {
                command[index] = '\0';  // Null-terminate the string

                if (strncmp(command, "turn on led", strlen("turn on led")) == 0) {
                    PORTB |= (1 << PB5); // Turn on the LED
                    uart_send_string("LED on\r\n");
                } else if (strncmp(command, "turn off led", strlen("turn off led")) == 0) {
                    PORTB &= ~(1 << PB5); // Turn off the LED
                    uart_send_string("LED off\r\n");
                } else {
                    uart_send_string("Error: Invalid command\r\n");
                }

                index = 0; // Reset the index for the next command
            } else {
                command[index] = received_char; // Add the received character to the command
                index++;
                if (index >= sizeof(command) - 1) {
                    // Prevent buffer overflow
                    index = 0; // Reset the index
                }
            }
        }
    }

    return 0;
}
