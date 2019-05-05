arm-none-eabi-as -mcpu=cortex-a9 -g startup.s -o startup.o -w
arm-none-eabi-gcc -cpp -mcpu=cortex-a9 test.cpp -o test.o -w
arm-none-eabi-gcc -cpp -mcpu=cortex-a9 master.cpp -o master.o -w
arm-none-eabi-gcc -cpp -mcpu=cortex-a9 slave.cpp -o slave.o -w
arm-none-eabi-ld -T test.ld master.o slave.o test.o startup.o -o test.elf
arm-none-eabi-objcopy -O binary test.elf test.bin
qemu-system-arm -M realview-pbx-a9 -cpu cortex-a9 -m 128M -nographic -kernel test.bin
