# DCLK中断问题

当LCDC模块内FIFO为空时，DCLK会输出高电平，部分屏幕会出现抖动现象。

当LCDC持续抢占不到SDRAM时，FIFO就会变空，CPU,DMA,DMA2D,JPEG模块都会抢占SDRAM。