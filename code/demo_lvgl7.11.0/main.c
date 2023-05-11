#include "main.h"
#include "lvgl/examples/porting/lv_port_disp.h"
#include "lvgl/examples/porting/lv_port_indev.h"
//#include "lvgl/examples/porting/lv_port_fs.h"

#include "lvgl/lvgl.h"
#include "lv_examples/lv_examples.h"
int main(void)
{
    uart_init();
    printf("Hi, World!\n");
    systick_init();

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    // lv_port_fs_init();

    lv_demo_widgets();

    while (1 == 1)
    {
        lv_task_handler();
    }
}

void SysTick_Handler_cb(void)
{
    lv_tick_inc(1);
}

void SysTick_Handler(void)
{
    swm_inctick();
    SysTick_Handler_cb();
}
