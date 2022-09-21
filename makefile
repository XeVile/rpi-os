##
#  RTOS - Raspberry Pi 3 B+
#
# @file
# @version 0.1

# Cross-Compiler prefix set to ARM64 GCC
ARMGNU ?= aarch64-linux-gnu

# C-Options and Assembler-Options
# * C
# 	- Show all warnings
# 	- Do not use standard lib (Bare Metal)
# 	- Do not set initial stack pointer, static data and jump to entry point
# 	- Do not assume startup at usual places like "main"
# 	- Look for headers at include folder
# 	- Only use general purpose registers, no NEON registers
#
# * Assembler
# 	- Look for headers at include folder
#
COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMOPS = -Iinclude

BUILD_DIR = build
SRC_DIR = src

all: kernel8.img

clean: rm -rf $(BUILD_DIR) *.img

# Compile files in SRC directory and output into BUILD directory
# $< is placeholder for input files
# $@ is placeholder for output files
#
# Output File is named with snake case prefix for "_c" & "_s"
#
# -MMD: Creates dependency files as required
#
# Added creation of fallback build directory in case it is non-existent
#
$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

# Build an array of Object files
#
C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

# Use defined linker script for compilation and look of the executable image
# Extract ELF to IMG file
# Use ARMv# -> kernel#.img
# * -> version 8 of the ARM architecture
#
kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf  $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

# end
