main:main.o i2c.o
		gcc main.o i2c.o -o test
main.o:main.c
		gcc -c main.c -o main.o
i2c.o:i2c.c
		gcc -c i2c.c -o i2c.o
.PHONY:clean
clean:
		rm -rf *.o
