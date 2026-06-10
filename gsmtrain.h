
void gsm_sms(unsigned char *c)
{

UART0_STR("AT\r\n");
delay_ms(200);

UART0_STR("AT+CMGF=1\r\n");     // Text mode
delay_ms(200);

UART0_STR("AT+CMGS=\"6381953071\"\r\n");
delay_ms(500);                // Wait for '>' prompt

UART0_STR(c);

UART0_TX(0x1A);                // Ctrl+Z
}
