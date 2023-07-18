################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
KnightRiderLights.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
KnightRiderLights.list \

OBJCOPY_BIN += \
KnightRiderLights.bin \


# All Target
all: KnightRiderLights.elf secondary-outputs

# Tool invocations
KnightRiderLights.elf: $(OBJS) $(USER_OBJS) C:\Users\yanga\STM32CubeIDE\workspace_1.1.0\KnightRiderLights\STM32F446RETX_FLASH.ld
	arm-none-eabi-gcc -o "KnightRiderLights.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\yanga\STM32CubeIDE\workspace_1.1.0\KnightRiderLights\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="KnightRiderLights.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

KnightRiderLights.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "KnightRiderLights.list"
	@echo 'Finished building: $@'
	@echo ' '

KnightRiderLights.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "KnightRiderLights.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
