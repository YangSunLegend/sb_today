#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int open_i2c_bus(const unsigned char *busName);
int open_i2c_device(int fd, int devAddr);
int close_i2c_bus(int fd);
int read_register(int fd, unsigned int regAddr, unsigned char *value, unsigned int len);
int write_register(int fd, unsigned int regAddr, unsigned char *value, unsigned int len);