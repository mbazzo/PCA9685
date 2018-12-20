#ifndef PCA9685_H
#define PCA9685_H

#define   PCA9685_MODE1       0x00
#define   PCA9685_MODE2       0x01
#define   PCA9685_LED0        0x06
#define   PCA9685_PRESC       0xFE
#define   PCA9685_I2C_ADR     0x40

void Setup(void);
void SetPwm(int on, int off, int channel);

#endif