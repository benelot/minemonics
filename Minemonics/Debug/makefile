################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/view/ogre3D/evolution/population/creature/phenome/morphology/sensor/exeroceptor/vision/subdir.mk
-include src/view/ogre3D/evolution/population/creature/phenome/morphology/muscle/subdir.mk
-include src/view/ogre3D/evolution/population/creature/subdir.mk
-include src/view/ogre3D/evolution/environments/subdir.mk
-include src/view/general/evolution/environments/subdir.mk
-include src/test/settings/subdir.mk
-include src/test/subdir.mk
-include src/prototype/TestingOgre/build/CMakeFiles/OgreApp.dir/subdir.mk
-include src/prototype/TestingOgre/build/CMakeFiles/2.8.12.2/CompilerIdCXX/subdir.mk
-include src/prototype/TestingOgre/build/CMakeFiles/2.8.12.2/CompilerIdC/subdir.mk
-include src/prototype/TestingOgre/subdir.mk
-include src/prototype/BulletOgre/build/CMakeFiles/OgreApp.dir/subdir.mk
-include src/prototype/BulletOgre/build/CMakeFiles/2.8.12.2/CompilerIdCXX/subdir.mk
-include src/prototype/BulletOgre/build/CMakeFiles/2.8.12.2/CompilerIdC/subdir.mk
-include src/prototype/BulletOgre/subdir.mk
-include src/model/settings/subdir.mk
-include src/model/evolution/population/creature/phenome/morphology/sensor/exteroceptor/vision/subdir.mk
-include src/model/evolution/population/creature/phenome/morphology/muscle/subdir.mk
-include src/model/evolution/population/creature/phenome/morphology/joint/subdir.mk
-include src/model/evolution/population/creature/phenome/morphology/subdir.mk
-include src/model/evolution/population/creature/genome/genetics/variation/mutation/subdir.mk
-include src/model/evolution/population/creature/genome/genetics/subdir.mk
-include src/model/evolution/population/creature/genome/subdir.mk
-include src/model/evolution/population/creature/subdir.mk
-include src/model/evolution/population/subdir.mk
-include src/controller/physics/subdir.mk
-include src/controller/misc/utils/subdir.mk
-include src/controller/configuration/subdir.mk
-include src/controller/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Minemonics

# Tool invocations
Minemonics: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "Minemonics" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Minemonics
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
