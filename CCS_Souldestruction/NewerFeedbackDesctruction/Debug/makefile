################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c5500_4.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./AdaptiveNotch.obj" \
"./C5515_eZdsp.obj" \
"./FFT.obj" \
"./LED.obj" \
"./Spi.obj" \
"./XVGA.obj" \
"./graphics_main.obj" \
"./noise_gate.obj" \
"./tunable_filter.obj" \
"./visuals.obj" \
"../lnkx.cmd" \
-l"rts55x.lib" \
-l"C:/Users/Pomakov/Documents/GitHub/EECS452GitHub/CCS_Souldestruction/C5515_Support_Files/452_Support/usbstk5515bsl.lib" \
-l"C:/Users/Pomakov/Documents/GitHub/EECS452GitHub/CCS_Souldestruction/C5515_Support_Files/452_Support/452_Labs_Essentials.lib" \
-l"C:/Users/Pomakov/Documents/GitHub/EECS452GitHub/CCS_Souldestruction/C5515_Support_Files/452_Support/55xdspx_LARGE.lib" \

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
EXE_OUTPUTS += \
NewerFeedbackDesctruction.out \

EXE_OUTPUTS__QUOTED += \
"NewerFeedbackDesctruction.out" \

BIN_OUTPUTS += \
NewerFeedbackDesctruction.hex \

BIN_OUTPUTS__QUOTED += \
"NewerFeedbackDesctruction.hex" \


# All Target
all: NewerFeedbackDesctruction.out

# Tool invocations
NewerFeedbackDesctruction.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"c:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O3 -g --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 -z -m"NewerFeedbackDesctruction.map" --stack_size=0x200 --heap_size=0x400 -i"c:/ti/ccsv6/tools/compiler/c5500_4.4.1/lib" -i"C:/Users/Pomakov/Documents/GitHub/EECS452GitHub/CCS_Souldestruction/Tunable_IIR_Filter/TunableFilter" -i"c:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" -i"C:/Users/Pomakov/Documents/GitHub/EECS452GitHub/CCS_Souldestruction/C5515_Support_Files/452_Support" --reread_libs --warn_sections --xml_link_info="NewerFeedbackDesctruction_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "NewerFeedbackDesctruction.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

NewerFeedbackDesctruction.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C5500 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/hex55"  -o "NewerFeedbackDesctruction.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "AdaptiveNotch.pp" "C5515_eZdsp.pp" "FFT.pp" "LED.pp" "Spi.pp" "XVGA.pp" "graphics_main.pp" "noise_gate.pp" "tunable_filter.pp" "visuals.pp" 
	-$(RM) "AdaptiveNotch.obj" "C5515_eZdsp.obj" "FFT.obj" "LED.obj" "Spi.obj" "XVGA.obj" "graphics_main.obj" "noise_gate.obj" "tunable_filter.obj" "visuals.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

