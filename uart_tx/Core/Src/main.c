#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"

int main()
{
    uart2_init();
    while(1)
    {
        char name[] = "Transmited\n\r";
        for(int i = 0; name[i] != '\0'; i++)
            uart2_write(name[i]);
        delayMs(50);
    }
    return 0;
}
