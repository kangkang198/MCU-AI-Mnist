######################################
# target
######################################
TARGET = ACM32H5_AI


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = Build
OUTPUT_DIR = Output

######################################
# source
######################################
# C sources path
C_SOURCES_PATH = \
Source/App/src \
Source/Drivers/Device \
Source/Drivers/HAL_Driver/Src \
Source/NNOM/src/backends \
Source/NNOM/src/core \
Source/NNOM/src/layers \

# C sources
C_SOURCES = $(foreach dir,$(C_SOURCES_PATH),$(wildcard $(dir)/*.c))

# ASM sources
ASM_SOURCES =  \
Source/App/src/startup_acm32h5xx.S \


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m33

# fpu
FPU = -mfpu=fpv5-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ISource/App/inc \
-ISource/Drivers/CMSIS \
-ISource/Drivers/Device \
-ISource/Drivers/HAL_Driver/Inc \
-ISource/NNOM/inc \
-ISource/NNOM/inc/layers \
-ISource/NNOM/port \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -w -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -w -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = Source/App/src/ACM32H5xx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys -lg -lgcc
LIBDIR =
LDFLAGS = $(MCU) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(OUTPUT_DIR)/$(TARGET).map,--cref -Wl,--gc-sections,--print-memory-usage

# change terminal compile output 
# V = 0: terminal simplify compile output 
# V = 1: terminal normal compile output 
V = 0
ifneq ($(V),1)
Q = @
MSG_CC = @echo	CC	$(<:.c=.o)
MSG_AS = @echo	AS	$(<:.S=.o)
MSG_LD = @echo	LD	$@
COMPILE_C = $(Q)$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
COMPILE_AS = $(Q)$(AS) -c $(CFLAGS) $< -o $@
LD_OBJS = $(Q)$(CC) $(OBJECTS) $(LDFLAGS) -o $@
else
Q = 
MSG_CC = 
MSG_AS =
MSG_LD =
COMPILE_C = $(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
COMPILE_AS = $(AS) -c $(CFLAGS) $< -o $@
LD_OBJS = $(CC) $(OBJECTS) $(LDFLAGS) -o $@
endif


# default action: build all
all: $(OUTPUT_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).hex $(OUTPUT_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(MSG_CC)
	$(COMPILE_C) 

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(MSG_AS) 
	$(COMPILE_AS)

$(OUTPUT_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(MSG_LD)
	$(LD_OBJS)
	$(SZ) $@

$(OUTPUT_DIR)/%.hex: $(OUTPUT_DIR)/%.elf | $(OUTPUT_DIR)
	$(HEX) $< $@
	
$(OUTPUT_DIR)/%.bin: $(OUTPUT_DIR)/%.elf | $(OUTPUT_DIR)
	$(BIN) $< $@	

$(BUILD_DIR):
	mkdir $@	

$(OUTPUT_DIR):
	mkdir $@	

#######################################
# clean up   del /q $(BUILD_DIR)
#######################################
clean:
	del *.lst /s
	del *.o /s
	del *.d /s
	del *.map /s
	del *.elf /s
	del *.hex /s
	del *.bin /s
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

#######################################
# compile 
#######################################
compile:
	make -j8

#######################################
# download 
#######################################
download:
	.\PyOCD\pyocd.bat flash --target=ACM32H5XX --erase=sector --frequency=1000000 \
	..\$(OUTPUT_DIR)/$(TARGET).hex

# *** EOF ***