#include <avr/io.h>
void set_pins(){
    // Set the switch pin as input with an internal pull-up resistor
    DDRB &= ~(1 << PB0);     // Set PB0 as input (Switch)
    PORTB |= (1 << PB0);     // Enable internal pull-up resistor on PB0

    DDRB |= (1 << PB5);      // Set PB5 as output (LED)

}    
    
