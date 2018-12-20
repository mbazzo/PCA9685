#include <fcntl.h>   
#include <stdio.h>   
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdint.h> 
#include "PCA9685.h"

static void set_prescaler(int pwm_freq);
static void i2c_write_reg(uint8_t reg, uint8_t data);
static void i2c_init(void);

int fp;

static void i2c_write_reg(uint8_t reg, uint8_t data)
{
    uint8_t buf[2];
	
    buf[0] = reg;
    buf[1] = data;
    write(fp, buf, 2);
}

static void i2c_init(void)
{
   char *filename = (char*)"/dev/i2c-1"; 
  
   if((fp = open(filename, O_RDWR)) < 0){ }
   
   int addr = PCA9685_I2C_ADR;
   if(ioctl(fp, I2C_SLAVE, addr) < 0){   }   
}

void SetPwm(int on, int off, int channel)
{
   i2c_write_reg((PCA9685_LED0 + 4*channel),     (on & 0xFF));
   i2c_write_reg((PCA9685_LED0 + 1 + 4*channel), (on >> 8));
   i2c_write_reg((PCA9685_LED0 + 2 + 4*channel), (off & 0xFF));
   i2c_write_reg((PCA9685_LED0 + 3 + 4*channel), (off >> 8));
}

void Setup(void)
{
   i2c_init();                          //platform specific
   
   i2c_write_reg(PCA9685_MODE1, 17);    //goto sleep
   set_prescaler(50);                   //50Hz
   i2c_write_reg(PCA9685_MODE1, 1);     //run mode
}

static void set_prescaler(int pwm_freq)
{
   uint8_t presc = (25000000 / (4096 * pwm_freq)) - 1;   //presc value
   i2c_write_reg(PCA9685_PRESC, presc);
}
