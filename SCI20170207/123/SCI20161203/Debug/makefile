################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c2000_6.1.3

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./SRC/USER_Spi.obj" \
"./SRC/USER_Sliding.obj" \
"./SRC/USER_Sensor.obj" \
"./SRC/USER_Sci.obj" \
"./SRC/USER_Pwm.obj" \
"./SRC/USER_Motion.obj" \
"./SRC/USER_Distance.obj" \
"./SRC/USER_Common.obj" \
"./SRC/SCI.obj" \
"./SRC/DSP2833x_usDelay.obj" \
"./SRC/DSP2833x_Xintf.obj" \
"./SRC/DSP2833x_SysCtrl.obj" \
"./SRC/DSP2833x_Spi.obj" \
"./SRC/DSP2833x_Sci.obj" \
"./SRC/DSP2833x_PieVect.obj" \
"./SRC/DSP2833x_PieCtrl.obj" \
"./SRC/DSP2833x_MemCopy.obj" \
"./SRC/DSP2833x_GlobalVariableDefs.obj" \
"./SRC/DSP2833x_DefaultIsr.obj" \
"./SRC/DSP2833x_CpuTimers.obj" \
"./SRC/DSP2833x_CodeStartBranch.obj" \
"./SRC/DSP2833x_ADC_cal.obj" \
-l"libc.a" \
"../DSP2833x_Headers_nonBIOS.cmd" \
"../F28335.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include SRC/subdir_vars.mk
-include subdir_rules.mk
-include SRC/subdir_rules.mk
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
all: SCI_test.out

# Tool invocations
SCI_test.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number --diag_wrap=off -z --stack_size=0x300 -m"SCI_test.map" --warn_sections -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/lib" -i"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="SCI_test_linkInfo.xml" --rom_model -o "SCI_test.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QUOTED) "SCI_test.out"
	-$(RM) "SRC\DSP2833x_CpuTimers.pp" "SRC\DSP2833x_DefaultIsr.pp" "SRC\DSP2833x_GlobalVariableDefs.pp" "SRC\DSP2833x_MemCopy.pp" "SRC\DSP2833x_PieCtrl.pp" "SRC\DSP2833x_PieVect.pp" "SRC\DSP2833x_Sci.pp" "SRC\DSP2833x_Spi.pp" "SRC\DSP2833x_SysCtrl.pp" "SRC\DSP2833x_Xintf.pp" "SRC\SCI.pp" "SRC\USER_Common.pp" "SRC\USER_Distance.pp" "SRC\USER_Motion.pp" "SRC\USER_Pwm.pp" "SRC\USER_Sci.pp" "SRC\USER_Sensor.pp" "SRC\USER_Sliding.pp" "SRC\USER_Spi.pp" 
	-$(RM) "SRC\DSP2833x_ADC_cal.obj" "SRC\DSP2833x_CodeStartBranch.obj" "SRC\DSP2833x_CpuTimers.obj" "SRC\DSP2833x_DefaultIsr.obj" "SRC\DSP2833x_GlobalVariableDefs.obj" "SRC\DSP2833x_MemCopy.obj" "SRC\DSP2833x_PieCtrl.obj" "SRC\DSP2833x_PieVect.obj" "SRC\DSP2833x_Sci.obj" "SRC\DSP2833x_Spi.obj" "SRC\DSP2833x_SysCtrl.obj" "SRC\DSP2833x_Xintf.obj" "SRC\DSP2833x_usDelay.obj" "SRC\SCI.obj" "SRC\USER_Common.obj" "SRC\USER_Distance.obj" "SRC\USER_Motion.obj" "SRC\USER_Pwm.obj" "SRC\USER_Sci.obj" "SRC\USER_Sensor.obj" "SRC\USER_Sliding.obj" "SRC\USER_Spi.obj" 
	-$(RM) "SRC\DSP2833x_ADC_cal.pp" "SRC\DSP2833x_CodeStartBranch.pp" "SRC\DSP2833x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
