################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/controller/physics/GroundController.cpp \
../src/controller/physics/LocomotionController.cpp \
../src/controller/physics/OpenSeaController.cpp 

OBJS += \
./src/controller/physics/GroundController.o \
./src/controller/physics/LocomotionController.o \
./src/controller/physics/OpenSeaController.o 

CPP_DEPS += \
./src/controller/physics/GroundController.d \
./src/controller/physics/LocomotionController.d \
./src/controller/physics/OpenSeaController.d 


# Each subdirectory must supply rules for building sources it contributes
src/controller/physics/%.o: ../src/controller/physics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


