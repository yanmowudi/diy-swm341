# 使用FatFs进行读写速度测试

参考[战舰STM32F103开发板 SDIO写入速度测试（使用FATFS）](http://www.openedv.com/forum.php?mod=viewthread&tid=94284)

## 测试条件

- 使用8GB 速度等级为Class4的SD卡
- SWM341的主频为150Hz,SDIO接口速度为系统主频4分频37.5MHz
- 上电先对SD卡进行格式化，先写入固定大小8MB的文件，然后读取该文件
- 测试FatFs不同的单次读写块大小对文件读取写入速度的影响

## 测试代码

关键宏定义
```c linenums="1" hl_lines="1 2 3"
#define FILE_SIZE (8 * 1024 * 1024)                 //文件大小8MB
#define FILE_OP_SIZE (32 * 1024)                    //单次读写块大小
#define FILE_OP_CYCLE (FILE_SIZE / FILE_OP_SIZE)    //需要读写的次数
```

写入测试
```c linenums="1" hl_lines="1 3"
    for (uint32_t i = 0; i < FILE_OP_CYCLE; i++)
    {
        res = f_write(&fil, op_buf, FILE_OP_SIZE, &len);
        if (res != FR_OK)
        {
            printf("write file fail!\r\n");
            goto loop_forever;
        }
        if(len != FILE_OP_SIZE)
        {
            printf("write len error!\r\n");
        }
    }
```
读取测试
```c linenums="1" hl_lines="1 3"
    for (uint32_t i = 0; i < FILE_OP_CYCLE; i++)
    {
        res = f_read(&fil, op_buf, FILE_OP_SIZE, &len);
        if (res != FR_OK)
        {
            printf("read file fail!\r\n");
            goto loop_forever;
        }
        if(len != FILE_OP_SIZE)
        {
            printf("read len error!\r\n");
        }
    }
```

## 测试结果

测试FatFs不同的单次读写块大小{==FILE_OP_SIZE==}对文件读取写入速度的影响

| FILE_OP_SIZE(byte) | 写入时间(ms) | 读取时间(ms) | 写入速度(KB/s) | 读取速度(KB/s) |
| :----------------: | :---------: | :---------: | :-----------: | :----------: |
| 1024               | 28173       | 6550        | 290           | 1251         |
| 2*1024             | 14648       | 3859        | 559           | 2123         |
| 4*1024             | 7833        | 1990        | 1046          | 4117         |
| 8*1024             | 4502        | 1047        | 1820          | 7824         |
| 16*1024            | 2654        | 885         | 3087          | 9256         |
| 32*1024            | 2326        | 684         | 3522          | 11977        |
