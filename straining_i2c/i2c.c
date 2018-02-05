#include "i2c.h"

int open_i2c_bus(const unsigned char *busName)
{
	int fd;

	fd = open(busName, O_RDWR);
	if(fd < 0) {
		perror("open failed the i2c bus!%d\n");
		return -1;	
	}
	return fd;
}

int open_i2c_device(int fd, int devAddr)
{
	int returnValue = 0;

	returnValue = ioctl(fd, I2C_SLAVE, devAddr);
	if(returnValue < 0) {
		printf("access the device i2c failed!\n");
		return -1;
	}
	return 0;
}

int read_register(int fd, unsigned int regAddr, unsigned char *value, unsigned int len)
{
	int bytesRead = 0;
	int returnValue;
	unsigned char regBuf[1];

	regBuf[0] = regAddr;

	returnValue = write(fd, regBuf, 1);
	if(returnValue <= 0) {
		perror("write failed!\n");
		return -1;
	}

	bytesRead = read(fd, value, len);
	if(bytesRead < 0) {
		perror("read failed!\n");
		return -1;
	}

	return bytesRead;
}

int write_register(int fd, unsigned int regAddr, unsigned char  *value, unsigned int len)
{
	int item,bytesWrite = 0;
	unsigned char data[100];

	data[0] = regAddr;

	for(item = 1; item <= len; item ++)
	{
		data[item] = value[item - 1];
	}

	bytesWrite = write(fd, data, len+1);
	if(bytesWrite < 0) {
		perror("write failed!\n");
		return -1;
	}
	return bytesWrite-1;
}

int close_i2c_bus(int fd)
{
	int returnValue = 0;

	returnValue = close(fd);
	if(returnValue < 0) {
		perror("close_i2c_bus failed!\n");
		return -1;
	}
	return returnValue;
}










