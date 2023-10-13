void uart_init(unsigned int baudrate);
void uart_send_char(char data);
char uart_receive_char(void);
void uart_send_string(const char* str);
char uart_receive_ready();
