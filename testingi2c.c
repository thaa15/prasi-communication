#include <stdio.h>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <wiringPiI2C.h>

#define DEVICE_ID 0x3C
#define SLAVE_R4F 0x4F

void main(){
int fd = wiringPiI2CSetup(DEVICE_ID);
wiringPiI2CWrite(fd,SLAVE_R4F);
int received_data = wiringPiI2CRead(fd);
printf("%d\n",received_data);
return;
}
