#!/usr/bin/make -f

# Ensure consistent environment
SHELL := /bin/bash
PATH := /opt/york/cs/net/gcc-arm-9.2.0/bin:$(PATH)


# Path to the GCC toolbox
PKG=/opt/york/cs/net

# Specify the commands needed from the tool chain, CC is the C-compiler,
# OBJCOPY converts the resulting program binary into a format we can load
# into the MBED board
ARCH=arm-none-eabi
CC=$(ARCH)-gcc
OBJCOPY=$(ARCH)-objcopy

# Due to a change in 2012 Linux, we now need to set a user name variable in the
# Makefile so the output path the make install users is right, this is done as
# follows
# USER:=$(shell whoami)

SOURCERY=$(PKG)/sourcery-g++-lite-arm-eabi-2010.09.51-i686-1
GNU_VERSION=4.5.0
THUMB2GNULIB=$(SOURCERY)/$(ARCH)/lib/$(GNU_VERSION)/thumb2
THUMB2GNULIB2=$(SOURCERY)/$(ARCH)/lib/thumb2

# "Cortex Microcontroller Software Interface Standard" Startup files, also the
# flags passed to the C compiler, and linker
CMSIS=$(PKG)/lpc1700-cmsis-lite-2011.01.26-i686-1
CMSISINCLUDES=-I$(CMSIS)/include
CMSISFL=$(CMSIS)/lib/core_cm3.o \
		$(CMSIS)/lib/system_LPC17xx.o \
		$(CMSIS)/lib/startup_LPC17xx.o
LDSCRIPT = $(CMSIS)/lib/ldscript_rom_gnu.ld

WARN= -Wall

CFLAGS= -O0 -std=gnu18 $(WARN) \
		-mcpu=cortex-m3 -mthumb -mapcs-frame -D__thumb2__=1 -msoft-float -gdwarf-2\
		-mno-sched-prolog -fno-hosted -mtune=cortex-m3 -march=armv7-m \
		-mfix-cortex-m3-ldrd -ffunction-sections -fdata-sections \
		-D__RAM_MODE__=0 $(CMSISINCLUDES) -I../libs -I.

LDFLAGS=$(CMSISFL) -static -mcpu=cortex-m3 -mthumb -mthumb-interwork \
		-Wl,--start-group -L$(THUMB2GNULIB) -L$(THUMB2GNULIB2) \
		-lc -lg -lstdc++ -lsupc++ -lgcc -lm -Wl,--end-group \
		-Xlinker -Map -Xlinker bin/lpc1700.map -Xlinker -T $(LDSCRIPT)

LDFLAGS+=-L$(CMSIS)/lib -lDriversLPC17xxgnu

# Name of the binary being built
EXECNAME	= bin/exec

# Source files provided by the user to build the project
LIBSC		= libs/*.c
LIBS		= $(shell echo $(LIBSC) | sed s/\\.c/\\.o/g)
OBJ1		= $(LIBS) mini1.o
OBJ2		= $(LIBS) mini2.o
OBJCALC		= $(LIBS) calculator.o
OBJ3		= $(LIBS) mini3.o
OBJINT		= $(LIBS) int.o

#all:	main
#	@echo "Build finished"

libs: $(LIBS)

mini1: $(OBJ1)
	mkdir -p bin
	/opt/york/cs/net/bin/arm-none-eabi-gcc -o $(EXECNAME) $(OBJ1) $(LDFLAGS)
	$(OBJCOPY) -I elf32-little -O binary $(EXECNAME) $(EXECNAME).bin

mini2: $(OBJ2)
	mkdir -p bin
	/opt/york/cs/net/bin/arm-none-eabi-gcc -o $(EXECNAME) $(OBJ2) $(LDFLAGS)
	$(OBJCOPY) -I elf32-little -O binary $(EXECNAME) $(EXECNAME).bin

calc: $(OBJCALC)
	mkdir -p bin
	/opt/york/cs/net/bin/arm-none-eabi-gcc -o $(EXECNAME) $(OBJCALC) $(LDFLAGS)
	$(OBJCOPY) -I elf32-little -O binary $(EXECNAME) $(EXECNAME).bin

mini3: $(OBJ3)
	mkdir -p bin
	/opt/york/cs/net/bin/arm-none-eabi-gcc -o $(EXECNAME) $(OBJ3) $(LDFLAGS)
	$(OBJCOPY) -I elf32-little -O binary $(EXECNAME) $(EXECNAME).bin

int: $(OBJINT)
	mkdir -p bin
	/opt/york/cs/net/bin/arm-none-eabi-gcc -o $(EXECNAME) $(OBJINT) $(LDFLAGS)
	$(OBJCOPY) -I elf32-little -O binary $(EXECNAME) $(EXECNAME).bin

# make clean - Clean out the source tree ready to re-build the project
clean:
	rm -f `find . | grep \~`
	rm -f *.swp *.o */*.o */*/*.o *.log
	rm -f *.d */*.d *.srec */*.a bin/*.map
	rm -f *.elf *.wrn bin/*.bin log *.hex
	rm -f $(EXECNAME)

# make install - Installs the resulting binary file to the MBED board, remember
# to sync the file systems, so the copy finishes
# need to know user to install into correct directory
USER:=$(shell whoami)

install:
	@echo "Copying " $(EXECNAME) "to the MBED file system"
	cp $(EXECNAME).bin /media/$(USER)/MBED &
	sync
	@echo "Now press the reset button on all MBED file systems"

version:
	$(CC) --version
