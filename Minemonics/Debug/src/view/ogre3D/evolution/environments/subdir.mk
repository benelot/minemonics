################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/view/ogre3D/evolution/environments/OpenSeaO3D.cpp \
../src/view/ogre3D/evolution/environments/PlaneO3D.cpp 

OBJS += \
./src/view/ogre3D/evolution/environments/OpenSeaO3D.o \
./src/view/ogre3D/evolution/environments/PlaneO3D.o 

CPP_DEPS += \
./src/view/ogre3D/evolution/environments/OpenSeaO3D.d \
./src/view/ogre3D/evolution/environments/PlaneO3D.d 


# Each subdirectory must supply rules for building sources it contributes
src/view/ogre3D/evolution/environments/%.o: ../src/view/ogre3D/evolution/environments/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


