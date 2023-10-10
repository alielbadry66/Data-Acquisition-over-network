#include <avr/io.h>
#include "uart.h"
void uart_init(unsigned int baudrate) {
    // Set baud rate
    unsigned int ubrr = F_CPU / 16 / baudrate - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable receiver and transmitter
    UCSR0B = UCSR0B | (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_char(char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Put data into buffer, sends the data
    UDR0 = data;
}

char uart_receive_char(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));
    
    // Get and return received data from buffer
    return UDR0;
}

void uart_send_string(const char* str) {
    while (*str) {
        uart_send_char(*str);
        str++;
    }
}

char uart_receive_ready(){
  return UCSR0A & (1 << RXC0);
}
