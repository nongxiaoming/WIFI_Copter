#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>
#include "mpu6500.h"

#define CONFIG_REG_NUM 7
rt_uint8_t MPU_Init_Data[CONFIG_REG_NUM][2] =
{
    {MPU6500_PWR_MGMT_1, 0x80},    // Reset Device
    {MPU6500_PWR_MGMT_1, 0x01},    // Clock Source
    {MPU6500_PWR_MGMT_2, 0x00},    // Enable Acc & Gyro
    {MPU6500_GYRO_CONFIG, 0x18},   // +-2000dps
    {MPU6500_ACCEL_CONFIG, 0x08},  // +-4G
    {MPU6500_ACCEL_CONFIG_2, 0x09}, // Set Acc Data Rates, Enable Acc LPF , Bandwidth 184Hz
    {MPU6500_INT_PIN_CFG, 0x30},   //
};

static rt_size_t mpu6500_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_i2c_msg msgs[2];
    mpu6500_dev_t *mpu6500;
    rt_uint8_t read_reg = pos;

    if (dev->user_data == RT_NULL)
        return (0);

    mpu6500 = (mpu6500_dev_t *)dev->user_data;

    msgs[0].addr  = mpu6500->addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &read_reg;
    msgs[0].len   = 1;

    msgs[1].addr  = mpu6500->addr;
    msgs[1].flags = RT_I2C_RD; /* Read from slave */
    msgs[1].buf   = (rt_uint8_t *)buffer;
    msgs[1].len   = size;

    if (rt_i2c_transfer(mpu6500->i2c_bus, msgs, 2) == 2)
        return (size);
    else
        return (0);
}

static rt_size_t mpu6500_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct rt_i2c_msg msgs[2];
    mpu6500_dev_t *mpu6500;
    rt_uint8_t write_reg = pos;

    if (dev->user_data == RT_NULL)
        return (0);
    mpu6500 = (mpu6500_dev_t *)dev->user_data;

    msgs[0].addr  = mpu6500->addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &write_reg;
    msgs[0].len   = 1;

    msgs[1].addr  = mpu6500->addr;
    msgs[1].flags = RT_I2C_WR | RT_I2C_NO_START;
    msgs[1].buf   = (rt_uint8_t *)buffer;
    msgs[1].len   = size;

    if (rt_i2c_transfer(mpu6500->i2c_bus, msgs, 2) == 2)
        return (size);
    else
        return (0);

}

/**
 * The following is rt-thread device operating interface
 */
static rt_err_t mpu6500_init(rt_device_t dev)
{
    rt_uint8_t i = 0;
    for (i = 0; i < CONFIG_REG_NUM; i++)
    {
        mpu6500_write(dev, MPU_Init_Data[i][0], &MPU_Init_Data[i][1], 1);
    }
    return RT_EOK;
}

static rt_err_t mpu6500_open(rt_device_t dev, rt_uint16_t oflag)
{

    if (dev->user_data == RT_NULL)
    {
        return RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

static rt_err_t mpu6500_close(rt_device_t dev)
{
    return RT_EOK;
}
static rt_err_t mpu6500_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    return RT_EOK;
}
void rt_hw_mpu6500_init(const char *i2c_bus_name, rt_uint16_t addr)
{
    rt_device_t device;
    mpu6500_dev_t *mpu6500;
    RT_ASSERT(i2c_bus_name != RT_NULL);
    mpu6500 = (mpu6500_dev_t *)rt_malloc(sizeof(mpu6500_dev_t));

    mpu6500->i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(i2c_bus_name);
    RT_ASSERT(mpu6500->i2c_bus != RT_NULL);
    mpu6500->addr = addr;


    device = (rt_device_t)rt_malloc(sizeof(struct rt_device));

    /* Register RTC device */
    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = mpu6500_init;
    device->open        = mpu6500_open;
    device->close       = mpu6500_close;
    device->read        = mpu6500_read;
    device->write       = mpu6500_write;
    device->control     = mpu6500_control;
    device->user_data   = mpu6500;

    rt_device_register(device, "mpu6500", RT_DEVICE_FLAG_RDWR);
}

rt_uint8_t mpu6500_test(void)
{
    rt_device_t mpu6500 = RT_NULL;
    rt_uint8_t mpu6500_id = 0;
    rt_uint8_t mpu_data[14];
    rt_uint16_t acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
    mpu6500 = rt_device_find("mpu6500");
    while (mpu6500 == RT_NULL)
    {
        rt_kprintf("can not find mpu6500!\n");
        rt_hw_mpu6500_init("i2c1", MPU6500_DEFAULT_ADDRESS);
        rt_thread_delay(5);
        mpu6500 = rt_device_find("mpu6500");
    }
    rt_device_open(mpu6500, RT_DEVICE_FLAG_RDONLY);
    mpu6500->read(mpu6500, MPU6500_WHOAMI, &mpu6500_id, 1);
    rt_kprintf("mpu6500 id = %x\n", mpu6500_id);
    if (mpu6500_id != 0x70)
        return 0;
    while (1)
    {
        mpu6500->read(mpu6500, MPU6500_ACCEL_XOUT_H, mpu_data, 14);
        acc_x = ((mpu_data[0] << 8) | mpu_data[1]);
        acc_y = ((mpu_data[2] << 8) | mpu_data[3]);
        acc_z = ((mpu_data[4] << 8) | mpu_data[5]);
        gyro_x = ((mpu_data[8] << 8) | mpu_data[9]);
        gyro_y = ((mpu_data[10] << 8) | mpu_data[11]);
        gyro_z = ((mpu_data[12] << 8) | mpu_data[13]);
        rt_kprintf("acc_xyz:%d,%d,%d\n", acc_x, acc_y, acc_z);
        rt_kprintf("gyro_xyz:%d,%d,%d\n", gyro_x, gyro_y, gyro_z);
        rt_thread_delay(100);
    }
    //return 0 ;
}
FINSH_FUNCTION_EXPORT(mpu6500_test, mpu6500 test);
