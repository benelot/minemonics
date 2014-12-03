################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/view/ogre3D/evolution/population/creature/phenome/morphology/sensor/exeroceptor/vision/PhotoReceptorO3D.cpp 

OBJS += \
./src/view/ogre3D/evolution/population/creature/phenome/morphology/sensor/exeroceptor/vision/PhotoReceptorO3D.o 

CPP_DEPS += \
./src/view/ogre3D/evolution/population/creature/phenome/morphology/sensor/exeroceptor/vision/PhotoReceptorO3D.d 


# Each subdirectory must supply rules for building sources it contributes
src/view/ogre3D/evolution/population/creature/phenome/morphology/sensor/exeroceptor/vision/%.o: ../src/view/ogre3D/evolution/population/creature/phenome/morphology/sensor/exeroceptor/vision/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


