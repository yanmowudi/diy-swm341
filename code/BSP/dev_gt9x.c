/**
 * @file dev_gt9x.c
 * @author lik
 * @brief gt9x相关配置函数
 * @version 0.1
 * @date 2022-01-14
 *
 * @copyright Copyright (c) 2022
 *
 */

/** 如果需要更新触摸配置请定义宏 UPDATE_CFG */
//#define UPDATE_CFG
/** 如果需要打印触摸调试信息请定义宏 GT9X_DEBUG */
//#define GT9X_DEBUG

#ifdef GT9X_DEBUG
#define gt9x_debug(...) printf(__VA_ARGS__)
#else
#define gt9x_debug(...) ;
#endif // GT9X_DEBUG

#include "main.h"

#ifdef UPDATE_CFG
/**  配置文件的版本号(新下发的配置版本号大于原版本，或等于原版本号但配置内容有变化时保存，
     版本号版本正常范围：'A'~'Z',发送 0x00 则将版本号初始化为'A') */
static uint8_t gt9x_cfg_tab[] = {
    0x00,       /*!< config_version */
    0xE0, 0x01, /*!< x output max */
    0x10, 0x01, /*!< y output max */
    0x05,       /*!< touch number */
    0x3D, 0x00, /*!< module switch */
    0x02, 0x08, 0x1E, 0x08, 0x50, 0x3C, 0x0F, 0x05,
    0x00, 0x00, 0xFF, 0x67, 0x50, 0x00, 0x00, 0x18,
    0x1A, 0x1E, 0x14, 0x89, 0x28, 0x0A, 0x30, 0x2E,
    0xBB, 0x0A, 0x03, 0x00, 0x00, 0x02, 0x33, 0x1D,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32,
    0x00, 0x00, 0x2A, 0x1C, 0x5A, 0x94, 0xC5, 0x02,
    0x07, 0x00, 0x00, 0x00, 0xB5, 0x1F, 0x00, 0x90,
    0x28, 0x00, 0x77, 0x32, 0x00, 0x62, 0x3F, 0x00,
    0x52, 0x50, 0x00, 0x52, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x0F, 0x03, 0x06, 0x10,
    0x42, 0xF8, 0x0F, 0x14, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x18, 0x16, 0x14, 0x12, 0x10, 0x0E, 0x0C,
    0x0A, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x28,
    0x24, 0x22, 0x20, 0x1F, 0x1E, 0x1D, 0x0E, 0x0C,
    0x0A, 0x08, 0x06, 0x05, 0x04, 0x02, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#endif

#define GT9x_ADDR 0x5D /*!< gt9x设备地址 */

#define GT9x_CTRL 0x8040  /*!< gt9x控制寄存器 */
#define GT9x_CFGS 0x8047  /*!< gt9x配置寄存器 */
#define GT9x_CHECK 0x80FF /*!< gt9x校验和寄存器 */
#define GT9x_PID 0x8140   /*!< gt9x产品ID寄存器 */

#define GT9x_GSTID 0x814E /*!< 当前检测到的触摸情况 */
#define GT9x_TP1 0x8150   /*!< 第一个触摸点数据地址 */
#define GT9x_TP2 0x8158   /*!< 第二个触摸点数据地址 */
#define GT9x_TP3 0x8160   /*!< 第三个触摸点数据地址 */
#define GT9x_TP4 0x8168   /*!< 第四个触摸点数据地址 */
#define GT9x_TP5 0x8170   /*!< 第五个触摸点数据地址 */

/**
 * @brief gt9x写寄存器
 *
 * @param reg 要写入的寄存器
 * @param buf 要写入的数组
 * @param len 要写入的数组的长度
 * @return true
 * @return false
 */
static bool gt9x_write_regs(uint16_t reg, uint8_t *buf, uint32_t len)
{
    uint32_t i;
    uint8_t ack;

    ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 0, 1);
    if (ack == 0)
        goto wr_fail;
    ack = I2C_Write(I2C0, reg >> 8, 1);
    if (ack == 0)
        goto wr_fail;
    ack = I2C_Write(I2C0, reg & 0XFF, 1);
    if (ack == 0)
        goto wr_fail;
    for (i = 0; i < len; i++)
    {
        ack = I2C_Write(I2C0, buf[i], 1);
        if (ack == 0)
            goto wr_fail;
    }

    I2C_Stop(I2C0, 1);
    for (i = 0; i < CyclesPerUs; i++)
        __NOP();
    return true;

wr_fail:
    I2C_Stop(I2C0, 1);
    for (i = 0; i < CyclesPerUs; i++)
        __NOP();
    return false;
}

/**
 * @brief gt9x读寄存器
 *
 * @param reg 要读取的寄存器
 * @param buf 要读取的数组
 * @param len 要读取的数组的长度
 * @return true
 * @return false
 */
static bool gt9x_read_regs(uint16_t reg, uint8_t *buf, uint32_t len)
{
    uint32_t i;
    uint8_t ack;

    ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 0, 1);
    if (ack == 0)
        goto rd_fail;
    ack = I2C_Write(I2C0, reg >> 8, 1);
    if (ack == 0)
        goto rd_fail;
    ack = I2C_Write(I2C0, reg & 0XFF, 1);
    if (ack == 0)
        goto rd_fail;
    for (i = 0; i < CyclesPerUs; i++)
        __NOP();
    ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 1, 1); // ReStart
    if (ack == 0)
        goto rd_fail;
    for (i = 0; i < len - 1; i++)
    {
        buf[i] = I2C_Read(I2C0, 1, 1);
    }
    buf[i] = I2C_Read(I2C0, 0, 1);
    I2C_Stop(I2C0, 1);
    for (i = 0; i < CyclesPerUs; i++)
        __NOP();
    return true;
rd_fail:
    I2C_Stop(I2C0, 1);
    for (i = 0; i < CyclesPerUs; i++)
        __NOP();
    return false;
}

/** 触摸信息结构体 */
tp_dev_t tp_dev;

/**
 * @brief gt9x读取触摸点
 *
 */
static void gt9x_read_points(void)
{
    uint8_t touch_status = 0, touch_num = 0, temp = 0, buf[5];

    gt9x_read_regs(GT9x_GSTID, &touch_status, 1);
    touch_num = touch_status & 0x0F;
    if ((touch_status & 0x80) && (touch_num < 6))
    {
        temp = 0;
        gt9x_write_regs(GT9x_GSTID, &temp, 1); // 清除READY标志
    }
    if (touch_num && (touch_num < 6))
    {
        tp_dev.status = TP_STATE_PRESSED;

        gt9x_read_regs(GT9x_TP1, buf, 4); //读取XY坐标值
        tp_dev.x = (((uint16_t)buf[1] << 8) + buf[0]);
        tp_dev.y = (((uint16_t)buf[3] << 8) + buf[2]);

        gt9x_debug("%d %d\n", tp_dev.x, tp_dev.y);
    }
    if ((touch_status & 0x8F) == 0x80) //无触摸点按下
    {
        tp_dev.x = 0xFFFF;
        tp_dev.y = 0xFFFF;
        tp_dev.status = TP_STATE_RELEASED;
    }
}

#ifdef UPDATE_CFG
/**
 * @brief 更新触摸配置固件
 *
 * @return true
 * @return false
 */
static bool gt9x_update_cfg(void)
{
    uint8_t buf[2];
    uint8_t i = 0;

    /* set x range */
    gt9x_cfg_tab[2] = (uint8_t)(HOR_RES >> 8);
    gt9x_cfg_tab[1] = (uint8_t)(HOR_RES & 0xff);

    /* set y range */
    gt9x_cfg_tab[4] = (uint8_t)(VER_RES >> 8);
    gt9x_cfg_tab[3] = (uint8_t)(VER_RES & 0xff);

    /* change x y */
    // gt9x_cfg_tab[6] ^= (1 << 3);

    /* change int trig type */
    /* FLAG_INT_FALL_RX */
    gt9x_cfg_tab[6] &= 0xFC;
    gt9x_cfg_tab[6] |= 0x01;
    /* FLAG_RDONLY */
    // gt9x_cfg_tab[6] &= 0xFC;
    // gt9x_cfg_tab[6] |= 0x03;

    if (gt9x_write_regs(GT9x_CFGS, gt9x_cfg_tab, sizeof(gt9x_cfg_tab)) != 0) /* send config */
    {
        gt9x_debug("send config failed\n");
        return false;
    }

    buf[0] = 0;
    for (i = 0; i < sizeof(gt9x_cfg_tab); i++)
        buf[0] += gt9x_cfg_tab[i];
    buf[0] = (~buf[0]) + 1;
    buf[1] = 1;
    gt9x_write_regs(GT9x_CHECK, buf, 2);
    swm_delay_ms(10);

    return true;
}
#endif

/**
 * @brief tp初始化
 *
 */
void tp_init(void)
{
    uint8_t temp[5] = {0};
    I2C_InitStructure I2C_initStruct;

    PORT_Init(PORTA, PIN1, PORTA_PIN1_I2C0_SCL, 1); // GPIOA.1配置为I2C0 SCL引脚
    PORTA->OPEND |= (1 << PIN1);
    PORTA->PULLU |= (1 << PIN1);                    //必须使能上拉，用于模拟开漏
    PORT_Init(PORTA, PIN0, PORTA_PIN0_I2C0_SDA, 1); // GPIOA.0配置为I2C0 SDA引脚
    PORTA->OPEND |= (1 << PIN0);
    PORTA->PULLU |= (1 << PIN0); //必须使能上拉，用于模拟开漏

    I2C_initStruct.Master = 1;
    I2C_initStruct.MstClk = 400000;
    I2C_initStruct.Addr10b = 0;
    I2C_initStruct.TXEmptyIEn = 0;
    I2C_initStruct.RXNotEmptyIEn = 0;
    I2C_Init(I2C0, &I2C_initStruct);
    I2C_Open(I2C0);

    GPIO_Init(GPIOD, PIN0, 0, 0, 1, 0); // 输入，开启下拉。复位时INT为低，选择0xBA作为地址

    GPIO_Init(GPIOA, PIN5, 1, 1, 0, 0); // gt9x复位
    GPIO_ClrBit(GPIOA, PIN5);
    swm_delay_ms(10);
    GPIO_SetBit(GPIOA, PIN5);
    swm_delay_ms(10);

    temp[0] = 0x02;
    gt9x_write_regs(GT9x_CTRL, temp, 1); // 软复位
    swm_delay_ms(100);

    gt9x_read_regs(GT9x_PID, temp, 4);
    gt9x_debug("touch product id:%s\n", temp);
#ifdef UPDATE_CFG
    /* 更新触摸芯片配置 */
    gt9x_update_cfg();
#endif

    EXTI_Init(GPIOD, PIN0, EXTI_FALL_EDGE); //下降沿触发
    NVIC_EnableIRQ(GPIOD_IRQn);
    EXTI_Open(GPIOD, PIN0);
}

void GPIOD_Handler(void)
{
    if (EXTI_State(GPIOD, PIN0))
    {
        EXTI_Clear(GPIOD, PIN0);
        gt9x_read_points();
    }
}