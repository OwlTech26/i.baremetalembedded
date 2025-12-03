CC=arm-none-eabi-gcc
MACH=cortex-m4
# Cortex M4 with Thumb instruction with GNU11 standard, no optimization
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
# Linker arguments
#LDFLAGS= -nostdlib -T stm32_ls.ld -Wl,-Map=final.map
#LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_ls.ld -Wl,-Map=final.map

# Make All
all: main.o led.o stm32_startup.o final.elf

# Make SemiHosting
semi: main.o led.o stm32_startup.o final_sh.elf

# Target Dependency
# Recipe: $^ -> denotes dependency, $@ -> denotes target
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^
	
led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^
	
stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^
	
syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^
	
final.elf:main.o led.o stm32_startup.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf:main.o led.o stm32_startup.o
	$(CC) $(LDFLAGS_SH) -o $@ $^
	
clean:
	rm -f *.o *.elf
	
load:
	openocd -f board/st_nucleo_f4.cfg