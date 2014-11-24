################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/SW/ti/ccsv5/tools/compiler/c5500_4.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./usbstk5515_led.obj" \
"./usbstk5515_i2c.obj" \
"./usbstk5515_gpio.obj" \
"./usbstk5515.obj" \
"./tunable_filter.obj" \
"./sar.obj" \
"./noise_gate.obj" \
"./XVGA.obj" \
"./LED.obj" \
"./LCD_FCN.obj" \
"./IntegratedDemo.obj" \
"./FFT.obj" \
"./AdaptiveNotch.obj" \
"./AIC_func.obj" \
-l"H:/github/EECS452GitHub/CCS/452Lib/452_Support/lib/usbstk5515bsl.lib" \
-l"H:/github/EECS452GitHub/CCS/452Lib/452_Support/lib/452_Labs_Essentials.lib" \
-l"H:/github/EECS452GitHub/CCS/452Lib/dsplib_2.40.00/55xdspx_LARGE.lib" \
-lrts55x.lib \
"H:/github/EECS452GitHub/CCS/452Lib/452_Support/lib/452_Labs_Essentials.lib" \
"H:/github/EECS452GitHub/CCS/452Lib/452_Support/lib/55xdspx_LARGE.lib" \
"../lnkx.cmd" \
"../rts55x.lib" \
"H:/github/EECS452GitHub/CCS/452Lib/452_Support/lib/usbstk5515bsl.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: IntegratedDemo.out

# Tool invocations
IntegratedDemo.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"C:/SW/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -vCPU:3.3 --memory_model=large -O3 -g --display_error_number --diag_warning=225 --ptrdiff_size=16 -z -m"IntegratedDemo.map" -i"C:/SW/ti/ccsv5/tools/compiler/c5500_4.4.1/lib" -i"H:/github/EECS452GitHub/CCS/452Lib/452_Support/src" -i"H:/github/EECS452GitHub/CCS/CustomLib/src" --reread_libs --warn_sections --rom_model -o "IntegratedDemo.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QUOTED) "IntegratedDemo.out"
	-$(RM) "AIC_func.pp" "AdaptiveNotch.pp" "FFT.pp" "IntegratedDemo.pp" "LCD_FCN.pp" "LED.pp" "XVGA.pp" "noise_gate.pp" "sar.pp" "tunable_filter.pp" "usbstk5515.pp" "usbstk5515_gpio.pp" "usbstk5515_i2c.pp" "usbstk5515_led.pp" 
	-$(RM) "AIC_func.obj" "AdaptiveNotch.obj" "FFT.obj" "IntegratedDemo.obj" "LCD_FCN.obj" "LED.obj" "XVGA.obj" "noise_gate.obj" "sar.obj" "tunable_filter.obj" "usbstk5515.obj" "usbstk5515_gpio.obj" "usbstk5515_i2c.obj" "usbstk5515_led.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
