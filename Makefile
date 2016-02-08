# STM32 Makefile for GNU toolchain and openocd
#
# This Makefile fetches the Cube firmware package from ST's' website.
# This includes: CMSIS, STM32 HAL, BSPs, USB drivers and examples.
#
# Usage:
#	make cube		Download and unzip Cube firmware
#	make program		Flash the board with OpenOCD
#	make openocd		Start OpenOCD
#	make debug		Start GDB and attach to OpenOCD
#	make dirs		Create subdirs like obj, dep, ..
#	make template		Prepare a simple example project in this dir
#
# Copyright	2015 Steffen Vogel
# License	http://www.gnu.org/licenses/gpl.txt GNU Public License
# Author	Steffen Vogel <post@steffenvogel.de>
# Link		http://www.steffenvogel.de
#
# edited for the STM32F4-Discovery

# A name common to all output files (elf, map, hex, bin, lst)
TARGET     = midi_synth

# Take a look into $(CUBE_DIR)/Drivers/BSP for available BSPs
BOARD      = STM32746G-Discovery
BOARD_UPCASE = STM32746G_DISCOVERY
BSP_BASE   = stm32746g_discovery

OCDFLAGS   = -f stm32f7discovery.cfg
GDBFLAGS   =

#EXAMPLE   = Templates
EXAMPLE    = Examples/FMC/FMC_SDRAM

# MCU family and type in various capitalizations o_O
MCU_FAMILY = stm32f7xx
MCU_LC     = stm32f746xx
MCU_MC     = STM32F746xx
MCU_UC     = STM32F746NGHx

# Your C files from the /src directory
SRCS       = main.c
SRCS      += system_$(MCU_FAMILY).c
SRCS      += stm32f7xx_it.c

# Basic HAL libraries
SRCS      += stm32f7xx_hal_rcc.c stm32f7xx_hal_rcc_ex.c stm32f7xx_hal.c stm32f7xx_hal_cortex.c stm32f7xx_hal_gpio.c \
			 stm32f7xx_hal_pwr_ex.c stm32f7xx_ll_fmc.c stm32f7xx_hal_sdram.c stm32f7xx_hal_pcd.c stm32f7xx_hal_pcd_ex.c \
			 stm32f7xx_hal_hcd.c stm32f7xx_hal_i2s.c stm32f7xx_hal_sai.c stm32f7xx_hal_sai_ex.c stm32f7xx_hal_i2c.c \
			 stm32f7xx_ll_usb.c stm32f7xx_hal_sd.c stm32f7xx_ll_sdmmc.c stm32f7xx_hal_dma.c \
			 $(BSP_BASE).c stm32746g_discovery_audio.c wm8994.c stm32746g_discovery_sd.c \
			 ff.c diskio.c ff_gen_drv.c sd_diskio.c ff_wrapper.c \
			 usbd_core.c usbd_ctlreq.c usbd_ioreq.c \
			 usbd_midi.c usbd_midi_if.c \
			 usbd_conf.c usbd_desc.c \
			 fluid_chan.c fluid_defsfont.c fluid_gen.c fluid_list.c fluid_mod.c fluid_synth.c fluid_voice.c \
			 fluid_chorus.c fluid_hash.c fluid_midi.c fluid_rev.c fluid_sys.c \
			 fluid_conv.c fluid_event.c fluid_io.c fluid_midi_router.c fluid_settings.c fluid_tuning.c \
			 arm_common_tables.c arm_sin_cos_f32.c arm_sin_f32.c arm_cos_f32.c arm_mult_f32.c arm_add_f32.c


# Directories
OCD_DIR    = openocd-stm32f7/tcl

CUBE_DIR   = cube

BSP_DIR    = src/bsp
HAL_DIR    = $(CUBE_DIR)/Drivers/STM32F7xx_HAL_Driver
CMSIS_DIR  = $(CUBE_DIR)/Drivers/CMSIS
AUDIO_DIR  = src/audio
USB_DIR	   = src/usb
FATFS_DIR	   = src/fatfs
FATFS_DRV_DIR = src/fatfs/drivers
LFLUIDSYNTH_DIR = src/lfluidsynth/src

DEV_DIR    = $(CMSIS_DIR)/Device/ST/STM32F7xx

CUBE_URL   = http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stm32cubef7.zip

# that's it, no need to change anything below this line!

###############################################################################
# Toolchain

PREFIX     = arm-none-eabi
CC         = $(PREFIX)-gcc
AR         = $(PREFIX)-ar
OBJCOPY    = $(PREFIX)-objcopy
OBJDUMP    = $(PREFIX)-objdump
SIZE       = $(PREFIX)-size
GDB        = $(PREFIX)-gdb

OCD        = openocd-stm32f7/src/openocd

###############################################################################
# Options

# Defines
DEFS       = -D$(MCU_MC) -DUSE_HAL_DRIVER -DUSE_USB_FS -D__FPU_PRESENT -DUSE_STM32746G_DISCOVERY

DEFS      += -DSTM32 -DSTM32F7 -DSTM32F746xx -DSTM32F746NGHx -DSTM32F746G_DISCO
# lfluidsynth
DEFS      += -DFLUID_SAMPLE_FORMAT_FLOAT -DFLUID_SAMPLE_READ_DISK -DFLUID_SAMPLE_GC -DFLUID_ARM_OPT -DFLUID_SAMPLE_READ_CHUNK -DFLUID_NEW_GEN_API

DEFS      += -DAUDIO_FORMAT_32BITS

DEFS      += -DARM_MATH_CM7

# Debug specific definitions for semihosting
DEFS       += -DUSE_DBPRINTF

# Include search paths (-I)
INCS       = -Isrc
INCS      += -I$(BSP_DIR)
INCS      += -I$(CMSIS_DIR)/Include
INCS      += -I$(DEV_DIR)/Include
INCS      += -I$(HAL_DIR)/Inc
INCS      += -I$(AUDIO_DIR)
INCS      += -I$(USB_DIR)
INCS      += -I$(FATFS_DIR)
INCS      += -I$(FATFS_DRV_DIR)
INCS      += -I$(LFLUIDSYNTH_DIR)

# Library search paths
LIBS       = -L$(CMSIS_DIR)/Lib

# Compiler flags
#CFLAGS     = -Wall -g -std=c99 -Os
CFLAGS     = -Wall -std=c99 -Os -g
#CFLAGS	   = -Wall -std=c99 -O3

CFLAGS += -mcpu=cortex-m7 -mlittle-endian
CFLAGS += -mfloat-abi=hard -mfpu=fpv5-sp-d16
CFLAGS += -mthumb 
CFLAGS += -ftree-vectorize -ffast-math -fsingle-precision-constant
#CFLAGS += -mno-sched-prolog

#CFLAGS    += -mlittle-endian -mcpu=cortex-m4 -mthumb -mthumb-interwork
#CFLAGS    += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS    += -ffunction-sections -fdata-sections
CFLAGS    += $(INCS) $(DEFS)

# Linker flags
LDFLAGS    = -Wl,--gc-sections -Wl,-Map=$(TARGET).map $(LIBS) -T$(MCU_LC).ld

# Enable Semihosting
LDFLAGS   += --specs=rdimon.specs -lc -lrdimon 
#-ldsplib_lm7f

# Source search paths
VPATH      = ./src
VPATH     += $(BSP_DIR)
VPATH     += $(HAL_DIR)/Src
VPATH     += $(DEV_DIR)/Source/
VPATH     += $(AUDIO_DIR)
VPATH     += $(USB_DIR)
VPATH     += $(FATFS_DIR)
VPATH     += $(FATFS_DRV_DIR)
VPATH     += $(LFLUIDSYNTH_DIR)
VPATH	  += cube/Drivers/CMSIS/DSP_Lib/Source/CommonTables
VPATH     += cube/Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions
VPATH	  += cube/Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions
VPATH	  += cube/Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions
OBJS       = $(addprefix obj/,$(SRCS:.c=.o))
DEPS       = $(addprefix dep/,$(SRCS:.c=.d))

# Prettify output
V = 0
ifeq ($V, 0)
	Q = @
	P = > /dev/null
endif

###################################################

.PHONY: all dirs program debug template clean

all: $(TARGET).elf

-include $(DEPS)

dirs: dep obj cube
dep obj src:
	@echo "[MKDIR]   $@"
	$Qmkdir -p $@

obj/%.o : %.c | dirs
	$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF dep/$(*F).d

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) src/startup_$(MCU_LC).s $^ -o $@
	$(OBJCOPY) $(TARGET).elf -O ihex $(TARGET).hex 
	$(OBJDUMP) -sSt $(TARGET).elf >$(TARGET).lst
	@echo "[SIZE]    $(TARGET).elf"
	$(SIZE) $(TARGET).elf

build_openocd:
	tools/install_openocd.sh

openocd:
	$(OCD) -s $(OCD_DIR) $(OCDFLAGS)

program: all
	$(OCD) -s $(OCD_DIR) $(OCDFLAGS) -c "program $(TARGET).elf verify reset exit"

debug:
	@if ! nc -z localhost 3333; then \
		echo "\n\t[Error] OpenOCD is not running! Start it with: 'make openocd'\n"; exit 1; \
	else \
		$(GDB)  -ex "target extended localhost:3333" \
			-ex "monitor arm semihosting enable" \
			-ex "monitor reset halt" \
			-ex "load" \
			-ex "monitor reset init" \
			$(GDBFLAGS) $(TARGET).elf; \
	fi

cube:
	rm -fr $(CUBE_DIR)
	wget -O /tmp/cube.zip $(CUBE_URL)
	unzip /tmp/cube.zip
	mv STM32Cube* $(CUBE_DIR)
	chmod -R u+w $(CUBE_DIR)
	rm -f /tmp/cube.zip

template: cube src
	cp -ri $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/Src/* src
	cp -ri $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/Inc/* src
	cp -i $(DEV_DIR)/Source/Templates/gcc/startup_$(MCU_LC).s src
	cp -i $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/SW4STM32/$(BOARD_UPCASE)/$(MCU_UC)_FLASH.ld $(MCU_LC).ld

clean:
	@echo "[RM]      $(TARGET).elf"; rm -f $(TARGET).elf
	@echo "[RM]      $(TARGET).hex"; rm -f $(TARGET).hex
	@echo "[RM]      $(TARGET).map"; rm -f $(TARGET).map
	@echo "[RM]      $(TARGET).lst"; rm -f $(TARGET).lst
	@echo "[RMDIR]   dep"          ; rm -fr dep
	@echo "[RMDIR]   obj"          ; rm -fr obj

