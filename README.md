# Data-Acquisition-over-network
First assessment in embedded systems course.


This code is designed for an AVR microcontroller, likely as part of an embedded systems project. It primarily focuses on handling UART communication and controlling an LED based on UART commands.

The program begins by initializing the UART (Universal Asynchronous Receiver-Transmitter) communication module with a baud rate of 9600, enabling serial communication with an external device such as a computer. It also configures the microcontroller's I/O pins. Specifically, it sets PB0 as an input for a switch and activates its internal pull-up resistor, ensuring stable input readings. Additionally, it configures PB5 as an output to control an LED.

Inside the main loop, the code continuously monitors the status of the switch connected to PB0. If the switch is pressed, it sends a corresponding message through UART indicating that the button is pressed; otherwise, it indicates that the button is not pressed.

The code also checks for incoming UART commands. If characters are available for reception, it checks if the received string is 'turn on led'. If it is, the code sends a message via UART indicating that the LED is turned on and sets PB5 high, illuminating the LED. If the received string is 'turn off led', it sends a message indicating that the LED is turned off and clears PB5, turning off the LED.

Overall, this code demonstrates the integration of UART communication with hardware control on an AVR microcontroller, making it suitable for various applications where remote control or monitoring via UART is required, with real-time feedback on the status of a button and LED control.
