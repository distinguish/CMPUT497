################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./CC3220SF_LAUNCHXL.obj" \
"./fatsd.obj" \
"./main_freertos.obj" \
"../CC3220SF_LAUNCHXL_FREERTOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"/Users/colton/ti/simplelink_cc32xx_sdk_1_30_01_03/source/ti/display/lib/display.aem4" \
-l"/Users/colton/ti/simplelink_cc32xx_sdk_1_30_01_03/source/ti/drivers/lib/drivers_cc32xx.aem4" \
-l"/Users/colton/ti/simplelink_cc32xx_sdk_1_30_01_03/source/third_party/fatfs/lib/fatfs.aem4" \
-l"/Users/colton/workspace_v72/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib" \
-l"/Users/colton/ti/simplelink_cc32xx_sdk_1_30_01_03/source/ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.out \

EXE_OUTPUTS__QUOTED += \
"sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.out" \

BIN_OUTPUTS += \
sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.bin \

BIN_OUTPUTS__QUOTED += \
"sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.out"

dependents:
	-cd /Users/colton/workspace_v72/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug && $(MAKE) clean all

# Tool invocations
sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) /Users/colton/workspace_v72/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.map" -i"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/lib" -i"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --reread_libs --diag_suppress=10063 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs_linkInfo.xml" --rom_model -o "sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.bin: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armhex"  -o "sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "CC3220SF_LAUNCHXL.obj" "fatsd.obj" "main_freertos.obj" 
	-$(RM) "CC3220SF_LAUNCHXL.d" "fatsd.d" "main_freertos.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-/Applications/ti/ccsv7/utils/tiobj2bin/tiobj2bin sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.out sdfatfs_CC3220SF_LAUNCHXL_freertos_ccs.bin /Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armofd /Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armhex /Applications/ti/ccsv7/utils/tiobj2bin/mkhex4bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/colton/workspace_v72/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib:

-include ../makefile.targets

