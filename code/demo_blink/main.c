#include "SWM341.h"

int main(void)
{
    uint32_t i;
    SystemInit();
    GPIO_Init(GPIOD, PIN2, 1, 0, 0, 0); //GPIOD.2配置为输出引脚，推挽输出
    while(1==1)
    {
        GPIO_InvBit(GPIOD, PIN2);
        for(i = 0; i < SystemCoreClock/8; i++) __NOP();
    }
}
