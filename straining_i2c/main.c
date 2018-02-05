#include "i2c.h"

#define DEV_ADDRESS	0x5d
#define WHO_AM_I	0x0f
#define CTRL_REG1	0x10
#define PRESS_OUT_XL	0X28
#define TEMP_OUT_L	0x2b

int main()
{
	int i = 0;
	int fd[2];
	int returnValue;
	unsigned char iden[1];
	unsigned char data[1];
	unsigned char temp[2];
	unsigned char press[3];
	float pressHpa, tempc;
	unsigned int value;

	if((fd[0]  = open_i2c_bus("/dev/i2c-3")) < 0) {
		exit(-1);
	}
	if((fd[1] = open_i2c_bus("/dev/i2c-4")) < 0) {
		exit(-1);
	}

	for(i = 0; i < 2; i++) {
		if((returnValue = open_i2c_device(fd[i], DEV_ADDRESS)) < 0) {
			exit(-1);
		}
	}
	iden[0] = 0;

	for(i = 0; i < 2; i++) {
		returnValue = read_register(fd[i], WHO_AM_I, iden, 1);
		if(returnValue <= 0) {
			printf("read failed:WHO_AM_I\n");
			exit(-1);
		}else{
			printf("i2c-%d:WHO_AM_I:%x\n", i+4,iden[0]);
		}
	}
	data[0] = 0x50;

	for(i = 0; i < 2; i++) {
		returnValue = write_register(fd[i], CTRL_REG1, data, 1);
		if (returnValue != 1) {
			printf("CTRL_REG1:WRITE failed!\n");
			exit(-1);
		}else{
			data[0] = 0;
			read_register(fd[i], CTRL_REG1, data, 1);
			printf("i2c-%d:CTRL_REG1:%x\n", i+4, data[0]);
		}
	}
	for(i = 0; i < 2; i++)
		temp[i] = 0;
	for(i = 0; i < 3; i++)
		press[i] = 0;
	pressHpa = 0.0;
	tempc = 0.0;

	while(1) {

		sleep(1);

		for(i = 0; i < 2; i++) {
			returnValue = read_register(fd[i], PRESS_OUT_XL, press, 3);
			if(returnValue != 3) {
				printf("PRESS_OUT_XL: read failed!\n");
			}
			for (i = 0; i < 3; i++) {
				value |= (press[i] << (8*i));
			}
			pressHpa = ((float)value) / 4096;

			printf("i2c-%d:read value:%x\n", i + 4, value);
			printf("i2c-%d:The press is %.2f hpa\n", i+4, pressHpa );
			
			returnValue = read_register(fd[i], TEMP_OUT_L, temp, 2);
			if(returnValue != 2) {
				printf("TEMP_OUT_L: READ failed!\n");
				exit(-1);
			}
			value = (temp[1] << 8 | temp[0]);
			tempc = ((float)value) / 100;

			printf("i2c-%d:The temperature is %.2f C\n", i + 4, tempc);
		}
	}


	return 0;
}