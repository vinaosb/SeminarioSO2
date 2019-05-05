#include "master.h"
#include "slave.h"
volatile unsigned int *const UART0DR = (unsigned int *)0x10009000;

void print_uart0(const char *s)
{
    while (*s != '\0')
    {
        *UART0DR = (unsigned int)(*s);
        s++;
    }
}

void c_entry()
{
    Master M;
    M.AddSlave(0x5F);
    M.AddSlave(0x4F);
    M.AddSlave(0x3F);
    M.AddData(bitset<32>(0xeeee), bitset<7>(0x5f));
    M.transferData();

    print_uart0("Hello World!\n");
}