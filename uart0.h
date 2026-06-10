void  UART0_CONFIG()
{
PINSEL0=0X5;
U0LCR=0X83;
U0DLL=97;
U0DLM=0;
U0LCR=0X03;
}

void UART0_TX(unsigned char c)
{
while(((U0LSR>>5)&1)==0);
U0THR=c;
}

void UART0_STR(unsigned char *s)
{
while(*s)
{
UART0_TX(*s++);
}
}


